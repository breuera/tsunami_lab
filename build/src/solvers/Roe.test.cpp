/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests of the Roe Riemann solver.
 **/
#include <catch2/catch.hpp>
#define private public
#include "Roe.h"
#undef public

TEST_CASE( "Test the derivation of the Roe speeds.", "[RoeSpeeds]" ) {
   /*
    * Test case:
    *  h: 10 | 9
    *  u: -3 | 3
    *
    * roe height: 9.5
    * roe velocity: (sqrt(10) * -3 + 3 * 3) / ( sqrt(10) + sqrt(9) )
    *               = -0.0790021169691720
    * roe speeds: s1 = -0.079002116969172024 - sqrt(9.80665 * 9.5) = -9.7311093998375095
    *             s2 = -0.079002116969172024 + sqrt(9.80665 * 9.5) =  9.5731051658991654
    */
  float l_waveSpeedL = 0;
  float l_waveSpeedR = 0;
  tsunami_lab::solvers::Roe::waveSpeeds( 10,
                                         9,
                                         -3,
                                         3,
                                         l_waveSpeedL,
                                         l_waveSpeedR );

  REQUIRE( l_waveSpeedL == Approx( -9.7311093998375095 ) );
  REQUIRE( l_waveSpeedR == Approx(  9.5731051658991654 ) );
}

TEST_CASE( "Test the derivation of the Roe wave speeds.", "[RoeStrengths]" ) {
  /*
   * Test case:
   *  h:   10 | 9
   *  u:   -3 | 3
   *  hu: -30 | 27
   *
   * The derivation of the Roe speeds (s1, s2) is given above.
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
   * Multiplicaton with the jump in quantities gives the wave strengths:
   *
   * wolframalpha.com query: {{0.49590751974393229, -0.051802159398648326}, {0.50409248025606771, 0.051802159398648326}} * {9-10, 27--30}
   *
   *        | 9 - 10   |   | -3.4486306054668869 |
   * Rinv * |          | = |                     |
   *        | 27 - -30 |   |  2.4486306054668869 |
   */
  float l_strengthL = 0;
  float l_strengthR = 0;

  tsunami_lab::solvers::Roe::waveStrengths( 10,
                                            9,
                                            -30,
                                            27,
                                            -9.7311093998375095,
                                            9.5731051658991654,
                                            l_strengthL,
                                            l_strengthR );

  REQUIRE( l_strengthL == Approx(-3.4486306054668869) );
  REQUIRE( l_strengthR == Approx( 2.4486306054668869) );
}

TEST_CASE( "Test the derivation of the Roe net-updates.", "[RoeUpdates]" ) {
  /*
   * Test case:
   *
   *      left | right
   *  h:    10 | 9
   *  u:    -3 | 3
   *  hu:  -30 | 27
   *
   * The derivation of the Roe speeds (s1, s2) and wave strengths (a1, a1) is given above.
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                      |  1 |   | 33.5590017014261447899292 |
   * update #1: s1 * a1 * |    | = |                           |
   *                      | s1 |   | -326.56631690591093200508 |
   *
   *                      |  1 |   | 23.4409982985738561366777 |
   * update #2: s2 * a2 * |    | = |                           |
   *                      | s2 |   | 224.403141905910928927533 |
   */
  float l_netUpdatesL[2] = { -5, 3 };
  float l_netUpdatesR[2] = {  4, 7 };

  tsunami_lab::solvers::Roe::netUpdates( 10,
                                         9,
                                         -30,
                                         27,
                                         l_netUpdatesL,
                                         l_netUpdatesR );

  REQUIRE( l_netUpdatesL[0] == Approx( 33.5590017014261447899292 ) );
  REQUIRE( l_netUpdatesL[1] == Approx( -326.56631690591093200508 ) );

  REQUIRE( l_netUpdatesR[0] == Approx( 23.4409982985738561366777 ) );
  REQUIRE( l_netUpdatesR[1] == Approx( 224.403141905910928927533 ) );

  /*
   * Test case (dam break):
   *
   *     left | right
   *   h:  10 | 8
   *   hu:  0 | 0
   *
   * Roe speeds are given as:
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
   *          | 0.5 -0.0532217 |
   *
   * Multiplicaton with the jump in quantities gives the wave strengths:
   *
   *        | 8 - 10 |   | -1 |   | a1 |
   * Rinv * |        | = |    | = |    |
   *        |  0 - 0 |   | -1 |   | a2 |
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                      |  1 |   |   9.394671362 |
   * update #1: s1 * a1 * |    | = |               |
   *                      | s1 |   | -88.25985     |
   *
   *                      |  1 |   |  -9.394671362 |
   * update #2: s2 * a2 * |    | = |               |
   *                      | s2 |   | -88.25985     |
   */
  tsunami_lab::solvers::Roe::netUpdates( 10,
                                         8,
                                         0,
                                         0,
                                         l_netUpdatesL,
                                         l_netUpdatesR ); 

  REQUIRE( l_netUpdatesL[0] ==  Approx(9.394671362) );
  REQUIRE( l_netUpdatesL[1] == -Approx(88.25985)    );

  REQUIRE( l_netUpdatesR[0] == -Approx(9.394671362) );
  REQUIRE( l_netUpdatesR[1] == -Approx(88.25985)    );

  /*
   * Test case (trivial steady state):
   *
   *     left | right
   *   h:  10 | 10
   *  hu:   0 |  0
   */
  tsunami_lab::solvers::Roe::netUpdates( 10,
                                         10,
                                         0,
                                         0,
                                         l_netUpdatesL,
                                         l_netUpdatesR );

  REQUIRE( l_netUpdatesL[0] == Approx(0) );
  REQUIRE( l_netUpdatesL[1] == Approx(0) );

  REQUIRE( l_netUpdatesR[0] == Approx(0) );
  REQUIRE( l_netUpdatesR[1] == Approx(0) );
}