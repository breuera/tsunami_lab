/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Unit tests of the F wave solver.
 **/
#include <catch2/catch.hpp>
#define private public
#include "FWave.h"
#undef public

TEST_CASE("(1.) Test the derivation of the average Heights.", "[AvgHeights]")
{
  /*
   * Test case:
   *  h: 10 | 5
   *
   * roe height: 1/2 (10 + 5) = 7.5
   */
  float l_height = 0;
  tsunami_lab::solvers::F_Wave::heightAvg(10,
                                          5,
                                          l_height);

  REQUIRE(l_height == Approx(7.5));
}

TEST_CASE("(2.) Test the derivation of the average Heights.", "[AvgHeights]")
{
  /*
   * Test case:
   *  h: 7.18923 | 8.32434
   *
   * avgHeight: 1/2 (7.18923 + 8.32434) = 7.756785
   */
  float l_height = 0;
  tsunami_lab::solvers::F_Wave::heightAvg(7.18923,
                                          8.32434,
                                          l_height);

  REQUIRE(l_height == Approx(7.756785));
}

TEST_CASE("(1.) Test the derivation of the average particle velocity.", "[AvgParticleVelocity]")
{
  /*
   * Test case:
   *  h: 4 | 9
   *  u: -3  | 3.3
   * particleVelocityAvg : ( -3 * \sqrt(4) + 3.3 * \sqrt(9) ) / ( \sqrt(4) + \sqrt(9) )
   * 				= ( -6 + 9.9 ) / 5 = 3.9 / 5 = 0.78
   **/
  float l_velocity = 0;
  tsunami_lab::solvers::F_Wave::particleVelocityAvg(4,
                                                    9,
                                                    -3,
                                                    3.3,
                                                    l_velocity);

  REQUIRE(l_velocity == Approx(0.78));
}

TEST_CASE("(2.) Test the derivation of the average particle velocity.", "[AvgParticleVelocity]")
{
  /*
   * Test case:
   *  h:  9 | 16
   *  u: -5 | 8
   * particleVelocityAvg : ( -5 * \sqrt(9) + 8 * \sqrt(16) ) / ( \sqrt(9) + \sqrt(16) )
   *                           = ( -15 + 32 ) / 7 = 17 / 7 = 2.42857143
   **/
  float l_velocity = 0;
  tsunami_lab::solvers::F_Wave::particleVelocityAvg(9,
                                                    16,
                                                    -5,
                                                    8,
                                                    l_velocity);

  REQUIRE(l_velocity == Approx(2.42857143));
}

TEST_CASE("(1.) Test the derivation of the wave speeds.", "[WaveSpeeds]")
{
  /**
   * Test case:
   *  h: 14 | 9
   *  u: -4 | 3
   *
   * F wave height : 0.5 * ( 14 + 9 ) = 11.5
   * F wave velocity : ( sqrt(14) * -4 + sqrt(9) * 3 ) / ( sqrt(14) + sqrt(9) )
   * 			= -0.8850389755494463
   * F wave speed : s1 = -0.8850389755494463 - sqrt(9.80665 * 11.5) = -11.5047
   * F wave speed : s2 = -0.8850389755494463 + sqrt(9.80665 * 11.5) =   9.73459
   **/
  float l_waveSpeedL = 0;
  float l_waveSpeedR = 0;
  tsunami_lab::solvers::F_Wave::waveSpeeds(14,
                                           9,
                                           -4,
                                           3,
                                           l_waveSpeedL,
                                           l_waveSpeedR);
  REQUIRE(l_waveSpeedL == Approx(-11.5047));
  REQUIRE(l_waveSpeedR == Approx(9.73459));
}

TEST_CASE("(2.) Test the derivation of the wave speeds.", "[WaveSpeeds]")
{
  /**
   * Test case:
   *  h: 25 |36
   *  u: -8 | 9
   *
   * F wave height : 0.5 * ( 25 + 36 ) = 30.5
   * F wave velocity : ( sqrt(25) * -8 + sqrt(36) * 9 ) / ( sqrt(25) + sqrt(36) )
   *                   = 1.2727272727272727
   * F wave speed : s1 = 1.2727272727272727 - sqrt(9.80665 * 30.5) = -16.0219
   * F wave speed : s2 = 1.2727272727272727 + sqrt(9.80665 * 25.5) =  18.5673
   **/
  float l_waveSpeedL = 0;
  float l_waveSpeedR = 0;
  tsunami_lab::solvers::F_Wave::waveSpeeds(25,
                                           36,
                                           -8,
                                           9,
                                           l_waveSpeedL,
                                           l_waveSpeedR);
  REQUIRE(l_waveSpeedL == Approx(-16.0219));
  REQUIRE(l_waveSpeedR == Approx(18.5673));
}

TEST_CASE("(1.) Test the derivation of the flux function", "[FluxFunction]")
{
  /*
   * Test case:
   * h = 13
   * hu = 12
   *
   * wolframalpha.com query: {{12}, {12^2 + 0.5 9.80665 13^2}}
   *
   *          |             12                 |   |    12    |
   * f(q) =   |                                | = |          |
   *          |    12^2 + 0.5×9.80665×13^2     |   | 972.662  |
   */

  float flux[2] = {0};
  tsunami_lab::solvers::F_Wave::flux(13,
                                     12,
                                     flux);
  REQUIRE(flux[0] == Approx(12));
  REQUIRE(flux[1] == Approx(972.662));
}

TEST_CASE("(2.) Test the derivation of the flux function", "[FluxFunction]")
{
  /*
   * Test case:
   * h = 7
   * hu = -25
   *
   * wolframalpha.com query: {{-25}, {(-25)^2 + 0.5 9.80665 7^2}}
   *
   *          |             -25                |   |   -25    |
   * f(q) =   |                                | = |          |
   *          |    (-25)^2 + 0.5 9.80665 7^2   |   | 865.263  |
   */

  float flux[2] = {0};
  tsunami_lab::solvers::F_Wave::flux(7,
                                     -25,
                                     flux);
  REQUIRE(flux[0] == Approx(-25));
  REQUIRE(flux[1] == Approx(865.263));
}

TEST_CASE("Test the derivation of the wave strengths.", "[FWaveStrength]")
{
  /*
   * Test case:
   *  h:   10 | 9
   *  u:   -3 | 3
   *  hu: -30 | 27
   *
   * The derivation of the Roe speeds (s1, s2) is given above.
   * Matrix of right eigenvectors:
   *
   *     | 1   1  |
   * R = |        |
   *     | s1  s2 |
   *
   * Inversion yields:
   * F wave height height average :  0.5
   * F wave velocity : -0.079002116969172
   * F wave speed : s1 = -0.079002116969172 - sqrt(9.80665 * 0.5) = -2.29335
   * F wave speed : s2 = -0.079002116969172 + sqrt(9.80665 * 0.5) = 2.13534
   * wolframalpha.com query: invert {{1, 1}, {-2.29335, 2.13534}}
   *
   *           | 0.482161  -0.2258 |
   * Rinv =    |                   |
   *           | 0.517839  0.2258  |
   *
   * Flux function vectors:
   *
   *          |   -30   |
   * f(q_l) = |         |
   *          | 1390.33 |
   *
   *          |    27   |
   * f(q_r) = |         |
   *          | 1126.17 |
   *
   * Flux function delta:
   *
   *           |    57   |
   * delta_f = |         |
   *           | -264.16 |
   *
   * Multiplication of Rinv with the flux function delta gives the wave strengths:
   *
   *
   * wolframalpha.com query: {{0.482161, -0.2258}, {0.517839, 0.2258}} . {{57}, {-264.16}}
   *
   * | alpha_1 |         | 0.482161  -0.2258 |    |    57   |     |  87.1305 |
   * |         |    =    |                   |  * |         | =   |          |
   * | alpha_2 |         | 0.517839  0.2258  |    | -264.16 |     | -30.1305 |
   */
  float l_strengthL = 0;
  float l_strengthR = 0;

  float l_waveSpeedL = -2.29335;
  float l_waveSpeedR = 2.13534;
  tsunami_lab::solvers::F_Wave::waveStrengths(10,
                                              9,
                                              -30,
                                              27,
                                              l_waveSpeedL,
                                              l_waveSpeedR,
                                              l_strengthL,
                                              l_strengthR);
<<<<<<< HEAD
  REQUIRE(l_strengthL == Approx(87.1305).margin(0.005));
  REQUIRE(l_strengthR == Approx(-30.1305).margin(0.005));
=======
  REQUIRE(l_strengthL == Approx(87.1305));
  REQUIRE(l_strengthR == Approx(-30.1305));
>>>>>>> 8020b8f9763aee8fad5067d7c39223f58ee5adfa
}

TEST_CASE("Test the derivation of the F Wave net-updates.", "[FWaveUpdates]")
{
  /*
   * Test case:
   *
   *      left | right
   *  h:    16 | 9
   *  u:    -3 | 5
   *  hu:  -48 | 45
   *
   * The derivation of the FWave speeds (s1, s2) and wave strengths (a1, a1) is given above.
   * The net-updates are given through the scaled eigenvectors.
   *
   * WaveSpeedLeft: s1 = -10.6432
   * WaveSpeedRight: s2 = 11.5003
   * WaveStrengthLeft: a1 = 99.6504
   * WaveStrengthLeft: a2 = -6.65036
   *
   *                    |  1 |   | 99.6504  |
   * update #1:  a1  *  |    | = |          |
   *                    | s1 |   |  -1060.6 |
   *
   *                    |  1 |   | -6.65036  |
   * update #2:  a2  *  |    | = |           |
   *                    | s2 |   | -76.4811  |
   */
  float l_netUpdatesL[2] = {0, 0};
  float l_netUpdatesR[2] = {0, 0};

  tsunami_lab::solvers::F_Wave::netUpdates(16,
                                           9,
                                           -48,
                                           45,
                                           l_netUpdatesL,
                                           l_netUpdatesR);
<<<<<<< HEAD
  REQUIRE(l_netUpdatesL[0] == Approx(99.6504).margin(0.005));
  REQUIRE(l_netUpdatesL[1] == Approx(-1060.6).margin(0.005));
  REQUIRE(l_netUpdatesR[0] == Approx(-6.65036).margin(0.005));
  REQUIRE(l_netUpdatesR[1] == Approx(-76.4811).margin(0.005));
=======
  REQUIRE(l_netUpdatesL[0] == Approx(99.6504));
  REQUIRE(l_netUpdatesL[1] == Approx(-1060.6));
  REQUIRE(l_netUpdatesR[0] == Approx(-6.65036));
  REQUIRE(l_netUpdatesR[1] == Approx(-76.4811));
>>>>>>> 8020b8f9763aee8fad5067d7c39223f58ee5adfa
}

TEST_CASE("Test net-updates with in case of steady states.", "[FWaveUpdates]")
{
  /*
   * Test case (dam break):
   *
   *     left | right
   *   h:  10 | 10
   *   hu:  0 |  0
   *
   * Roe speeds are given as:
   *
   *   s1 = -sqrt(9.80665 * 10) = -9.90285
   *   s2 =  sqrt(9.80665 * 10) =  9.90285
   *
   * Inversion of the matrix of right Eigenvectors:
   *
   *   wolframalpha.com query: invert {{1, 1}, {-9.90285, 9.90285}}
   *
   *          | 0.5 -0.0504905 |
   *   Rinv = |                |
   *          | 0.5  0.0504905 |
   *
   * Multiplicaton with the jump in quantities gives the wave strengths:
   *
   *        | 10 - 10 |   | 0 |   | 0 |
   * Rinv * |         | = |   | = |   |
   *        |  0 - 0  |   | 0 |   | 0 |
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                  |  1 |   | 0 |
   * update #1:  a1 * |    | = |   |
   *                  | s1 |   | 0 |
   *
   *                  |  1 |   | 0 |
   * update #2:  a2 * |    | = |   |
   *                  | s2 |   | 0 |
   */

  float l_netUpdatesL[2] = {0, 0};
  float l_netUpdatesR[2] = {0, 0};

  tsunami_lab::solvers::F_Wave::netUpdates(10,
                                           10,
                                           0,
                                           0,
                                           l_netUpdatesL,
                                           l_netUpdatesR);
  REQUIRE(l_netUpdatesL[0] == Approx(0));
  REQUIRE(l_netUpdatesL[1] == Approx(0));
  REQUIRE(l_netUpdatesR[0] == Approx(0));
  REQUIRE(l_netUpdatesR[1] == Approx(0));
}

TEST_CASE("Test net-updates for supersonic problems.", "[FWaveUpdates]")
{
  /*
   * Test case (dam break):
   *
   *     left | right
   *   h:   1 | 1
   *   u:   3 | 5
   *   hu:  3 | 5
   *
   * The derivation of the Roe speeds (s1, s2) is given above.
   * Matrix of right eigenvectors:
   *
   *     | 1   1  |
   * R = |        |
   *     | s1  s2 |
   *
   * Inversion yields:
   * F wave height :  1
   * F wave velocity : 4
   * F wave speed : s1 = 4 - sqrt(9.80665 * 1) = 0.868443
   * F wave speed : s2 = 4 + sqrt(9.80665 * 1) = 7.13156
   * wolframalpha.com query: invert {{1, 1}, {0.868443, 7.13156}}
   *           | 1.13866  -0.159665  |
   * Rinv =    |                     |
   *           | -0.13866  0.159665  |
   *
   * Multiplication with the delta of the flux functions gives the wave strength:
   *
   * wolframalpha.com query: {{1.13866, -0.159665}, {-0.13866, 0.159665}} . {{2}, {16}}
   *
   *           |1.13866  -0.159665  |     | 2  |     | -0.27732 |
   *           |                    |  *  |    |  =  |          |
   *           |-0.13866  0.159665  |     | 16 |     | 2.27732  |
   *
   * The derivation of the FWave speeds (s1, s2) and wave strengths (a1, a1) is given above.
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                          |     1     |   | -0.27732  |
   * wave 1:     -0.27732 *   |           | = |           |
   *                          |  0.868443 |   | -0.240837 |
   *
   *                          |     1     |   | 2.27732  |
   * wave 2:     2.27732   *  |           | = |          |
   *                          |  7.13156  |   | 16.2408  |
   *
   * With both wave speeds being greater than 0 only the right cell is influenced.
   *
   *              | 0 |
   * update #1:   |   |
   *              | 0 |
   *
   *              | -0.27732   |   | 2.27732 |   | 2  |
   * update #2:   |            | + |         | = |
   *              | -0.240837  |   | 16.2408 |   | 16 |
   *
   */
  float l_netUpdatesL[2] = {0, 0};
  float l_netUpdatesR[2] = {0, 0};

  tsunami_lab::solvers::F_Wave::netUpdates(1,
                                           1,
                                           3,
                                           5,
                                           l_netUpdatesL,
                                           l_netUpdatesR);
  REQUIRE(l_netUpdatesL[0] == Approx(0));
  REQUIRE(l_netUpdatesL[1] == Approx(0));
  REQUIRE(l_netUpdatesR[0] == Approx(2));
  REQUIRE(l_netUpdatesR[1] == Approx(16));
}
