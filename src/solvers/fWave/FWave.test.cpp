/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests of the F-Wave solver.
 **/
#include <catch2/catch.hpp>
#define private public
#include "FWave.h"
#undef public

TEST_CASE("Test the derivation of the FWave speeds.", "[FWaveSpeeds]")
{
  /*
   * Test case:
   *  h: 10 | 9
   *  u: -3 | 3
   *  b:  0 | 0
   *
   * FWave height: 9.5
   * FWave velocity: (sqrt(10) * -3 + 3 * 3) / ( sqrt(10) + sqrt(9) )
   *               = -0.0790021169691720
   * FWave speeds: s1 = -0.079002116969172024 - sqrt(9.80665 * 9.5) = -9.7311093998375095
   *             s2 = -0.079002116969172024 + sqrt(9.80665 * 9.5) =  9.5731051658991654
   */
  float l_waveSpeedL = 0;
  float l_waveSpeedR = 0;
  tsunami_lab::solvers::FWave::waveSpeeds(10,
                                          9,
                                          -3,
                                          3,
                                          l_waveSpeedL,
                                          l_waveSpeedR);

  REQUIRE(l_waveSpeedL == Approx(-9.7311093998375095));
  REQUIRE(l_waveSpeedR == Approx(9.5731051658991654));
}

TEST_CASE("Test the derivation of the FWave wave strength.", "[FWaveStrengths]")
{
  /*
   * Test case:
   *  h:   10 | 9
   *  u:   -3 | 3
   *  hu: -30 | 27
   *  b:    0 | 0
   *
   * The derivation of the FWave speeds (s1, s2) is given above.
   *
   *  Matrix of right eigenvectors:
   *
   *      | 1   1 |
   *  R = |       |
   *      | s1 s2 |
   *
   * Inversion yields:
   *
   * wolframalpha.com query: invert {{1, 1}, {-9.7311093998375095, 9.5731051658991654}}
   *
   *        | 0.49590751974393229 -0.051802159398648326 |
   * Rinv = |                                           |
   *        | 0.50409248025606771  0.051802159398648326 |
   *
   *
   * Multiplicaton with the jump in fluxes gives the wave strengths:
   *
   * wolframalpha.com query: {{0.49590751974393229, -0.051802159398648326}, {0.50409248025606771, 0.051802159398648326}} * {27--30, 9*3^2+1/2*9.80665*9^2-(10*(-3)^2+1/2*9.80665*10^2)}
   *
   *        | 27 - -30                                         |   | 33.559              |
   * Rinv * |                                                  | = |                     |
   *        | 9*3^2+1/2*9.80665*9^2-(10*-3^2+1/2*9.80665*10^2) |   | 23.441              |
   */
  float l_strengthL = 0;
  float l_strengthR = 0;

  tsunami_lab::solvers::FWave::waveStrengths(10,
                                             9,
                                             -30,
                                             27,
                                             0,
                                             0,
                                             -9.7311093998375095,
                                             9.5731051658991654,
                                             l_strengthL,
                                             l_strengthR);

  REQUIRE(l_strengthL == Approx(33.559));
  REQUIRE(l_strengthR == Approx(23.441));
}

TEST_CASE("Test the derivation of the FWave net-updates.", "[FWaveUpdates]")
{
  /*
   * Test case:
   *
   *      left | right
   *  h:    10 | 9
   *  u:    -3 | 3
   *  hu:  -30 | 27
   *  b:     0 | 0
   *
   * The derivation of the FWave speeds (s1, s2) and wave strengths (a1, a1) is given above.
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                      |  1 |   | 33.559                    |
   * update #1:      a1 * |    | = |                           |
   *                      | s1 |   | -326.5663003491469813105  |
   *
   *                      |  1 |   | 23.441                    |
   * update #2:      a2 * |    | = |                           |
   *                      | s2 |   | 224.4031581938423361414   |
   */
  float l_netUpdatesL[2] = {-5, 3};
  float l_netUpdatesR[2] = {4, 7};

  tsunami_lab::solvers::FWave::netUpdates(10,
                                          9,
                                          -30,
                                          27,
                                          0,
                                          0,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == Approx(33.559));
  REQUIRE(l_netUpdatesL[1] == Approx(-326.5663003491469813105));

  REQUIRE(l_netUpdatesR[0] == Approx(23.441));
  REQUIRE(l_netUpdatesR[1] == Approx(224.4031581938423361414));

  /*
   * Test case (dam break):
   *
   *     left | right
   *   h:  10 | 8
   *   hu:  0 | 0
   *   b:   0 | 0
   *
   * FWave speeds are given as:
   *
   *   s1 = -sqrt(9.80665 * 9)
   *   s2 =  sqrt(9.80665 * 9)
   *
   * Inversion of the matrix of right Eigenvectors:
   *
   *   wolframalpha.com query: invert {{1, 1}, {-sqrt(9.80665 * 9), sqrt(9.80665 * 9)}}
   *
   *          | 0.5 -0.0532217 |
   *   Rinv = |                |
   *          | 0.5 0.0532217 |
   *
   * Multiplicaton with the jump in fluxes gives the wave strengths:
   *
   *        |  0 - 0                           |   |  9.39468 |   | a1 |
   * Rinv * |                                  | = |          | = |    |
   *        | 1/2*9.80665*8^2-1/2*9.80665*10^2 |   | -9.39468 |   | a2 |
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                      |  1 |   | 9.39468       |
   * update #1:      a1 * |    | = |               |
   *                      | s1 |   | -88.2599      |
   *
   *                      |  1 |   | -9.39468      |
   * update #2:      a2 * |    | = |               |
   *                      | s2 |   | -88.2599      |
   */
  tsunami_lab::solvers::FWave::netUpdates(10,
                                          8,
                                          0,
                                          0,
                                          0,
                                          0,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == Approx(9.39468));
  REQUIRE(l_netUpdatesL[1] == Approx(-88.2599));

  REQUIRE(l_netUpdatesR[0] == Approx(-9.39468));
  REQUIRE(l_netUpdatesR[1] == Approx(-88.2599));

  /*
   * Test case (dam break with bathymetry):
   *
   *     left | right
   *   h:  10 | 8
   *   hu:  0 | 0
   *   b: -15 | -8
   *
   * FWave speeds are given as:
   *
   *   s1 = -sqrt(9.80665 * 9)
   *   s2 =  sqrt(9.80665 * 9)
   *
   * Inversion of the matrix of right Eigenvectors:
   *
   *   wolframalpha.com query: invert {{1, 1}, {-sqrt(9.80665 * 9), sqrt(9.80665 * 9)}}
   *
   *          | 0.5 -0.0532217 |
   *   Rinv = |                |
   *          | 0.5 0.0532217  |
   *
   * Multiplicaton with the jump in fluxes gives the wave strengths:
   *
   *        |  0 - 0                                                     |   | -23.4867 |   | a1 |
   * Rinv * |                                                            | = |          | = |    |
   *        | 1/2*9.80665*8^2-1/2*9.80665*10^2 +9.80665*(-8+15)*(10+8)/2 |   |  23.4867 |   | a2 |
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                      |  1 |   | -23.4867      |
   * update #1:      a1 * |    | = |               |
   *                      | s1 |   | 220.650       |
   *
   *                      |  1 |   |  23.4867      |
   * update #2:      a2 * |    | = |               |
   *                      | s2 |   | 220.650       |
   */
  tsunami_lab::solvers::FWave::netUpdates(10,
                                          8,
                                          0,
                                          0,
                                          -15,
                                          -8,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == Approx(-23.4867));
  REQUIRE(l_netUpdatesL[1] == Approx(220.650));

  REQUIRE(l_netUpdatesR[0] == Approx(23.4867));
  REQUIRE(l_netUpdatesR[1] == Approx(220.650));

  /*
   * Test case (trivial steady state):
   *
   *     left | right
   *   h:  10 | 10
   *  hu:   0 |  0
   */
  tsunami_lab::solvers::FWave::netUpdates(10,
                                          10,
                                          0,
                                          0,
                                          0,
                                          0,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == Approx(0));
  REQUIRE(l_netUpdatesL[1] == Approx(0));

  REQUIRE(l_netUpdatesR[0] == Approx(0));
  REQUIRE(l_netUpdatesR[1] == Approx(0));

  /**
   * Test case supersonic problem
   *
   *      left | right
   *  h:   1   | 1
   *  u:   100 | 10
   *  hu:  100 | 10
   *  b:   0   | 0
   *
   *  FWave speeds are given as:
   *
   *  s1 = 55 - sqrt(9.80665 * 1) = 51.868443
   *  s2 = 55 + sqrt(9.80665 * 1) = 58.131557
   *
   *  Inversion of the matrix of right Eigenvectors:
   *
   *   wolframalpha.com query: invert {{1, 1}, {55 - sqrt(9.80665 * 1), 55 + sqrt(9.80665 * 1)}}
   *
   *          | 9.28157  -0.159665  |
   *   Rinv = |                     |
   *          | -8.28157  0.159665  |
   *
   * Multiplicaton with the jump in fluxes gives the wave strengths:
   *
   *        | 10 - 100                                       |   |  745.342 |   | a1 |
   * Rinv * |                                                | = |          | = |    |
   *        |1*10^2+1/2*9.80665*1^2-(1*100^2+1/2*9.80665*1^2)|   | -835.342 |   | a2 |
   *
   * The net-updates are given through the scaled eigenvectors added for #2 and 0 for #1 because both are greater than 0:
   *
   * update #1:     0
   *
   *                     |  1 |         |  1 |    | -90              |
   * update #2:     a1 * |    | +  a2 * |    |  = |                  |
   *                     | s1 |         | s2 |    | -9900.002044988  |
   */

  tsunami_lab::solvers::FWave::netUpdates(1,
                                          1,
                                          100,
                                          10,
                                          0,
                                          0,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == Approx(0));
  REQUIRE(l_netUpdatesL[1] == Approx(0));

  REQUIRE(l_netUpdatesR[0] == Approx(-90));
  REQUIRE(l_netUpdatesR[1] == Approx(-9900.002044988));
}

TEST_CASE("Test the derivation of the FWave net-updates with dry Cells.", "[FWaveUpdatesDryCells]")
{
  /*
   * Test case (dry dry interface):
   *
   *     left | right
   *   h:   0 | 0
   *  hu:   0 | 0
   *   b:  14 | 3
   *
   *  expecting no change
   */
  float l_netUpdatesL[2] = {-5, 3};
  float l_netUpdatesR[2] = {4, 7};

  tsunami_lab::solvers::FWave::netUpdates(0,
                                          0,
                                          0,
                                          0,
                                          14,
                                          3,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == 0);
  REQUIRE(l_netUpdatesL[1] == 0);

  REQUIRE(l_netUpdatesR[0] == 0);
  REQUIRE(l_netUpdatesR[1] == 0);

  /*
   * Test case (dry wet interface):
   *
   *     left | right
   *   h:   0 |  10
   *  hu:   0 | -10
   *   b:  10 |  -10
   *
   *  expecting reflecting condition:
   *
   *  left:  h = 10, hu = 10, b = -10
   */
  float l_netUpdatesL2[2] = {-5, 3};
  float l_netUpdatesR2[2] = {4, 7};

  tsunami_lab::solvers::FWave::netUpdates(0,
                                          10,
                                          0,
                                          -10,
                                          10,
                                          -10,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  tsunami_lab::solvers::FWave::netUpdates(10,
                                          10,
                                          10,
                                          -10,
                                          -10,
                                          -10,
                                          l_netUpdatesL2,
                                          l_netUpdatesR2);

  REQUIRE(l_netUpdatesL[0] == 0);
  REQUIRE(l_netUpdatesL[1] == 0);

  REQUIRE(l_netUpdatesR[0] == Approx(l_netUpdatesR2[0]));
  REQUIRE(l_netUpdatesR[1] == Approx(l_netUpdatesR2[1]));
}