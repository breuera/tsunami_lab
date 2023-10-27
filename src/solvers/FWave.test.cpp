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

TEST_CASE( "Test 1 the derivation of the average Heights.", "[AvgHights]" ) {
   /*
    * Test case:
    *  h: 10 | 5
    *
    * roe height: 1/2 (10 + 5) = 7.5
    */
  float l_height= 0;
  tsunami_lab::solvers::F_Wave::heightAvg( 	10,
                                         	  5,
                                         	  l_height );

  REQUIRE( l_height == Approx( 7.5 ) );
}

TEST_CASE( "Test 2 the derivation of the average Heights.", "[AvgHights]" ) {
   /*
    * Test case:
    *  h: 7.18923 | 8.32434
    *
    * avgHeight: 1/2 (7.18923 + 8.32434) = 7.756785
    */
  float l_height= 0;
  tsunami_lab::solvers::F_Wave::heightAvg(  7.18923,
                                            8.32434,
                                            l_height );

  REQUIRE( l_height == Approx( 7.756785 ) );
}

TEST_CASE( "Test 1 the derivation of the average particle velocity.", "[AvgParticleVelocity]" ) {
   /*
    * Test case:
    *  h: 4 | 9
    *  u: -3  | 3.3
    * particleVelocityAvg : ( -3 * \sqrt(4) + 3.3 * \sqrt(9) ) / ( \sqrt(4) + \sqrt(9) )
    * 				= ( -6 + 9.9 ) / 5 = 3.9 / 5 = 0.78
   **/
  float l_velocity= 0;
  tsunami_lab::solvers::F_Wave::particleVelocityAvg(  4,
                                                	    9,
							                                        -3,
							                                        3.3,
                                                	    l_velocity );

  REQUIRE( l_velocity == Approx( 0.78 ) );
}

TEST_CASE( "Test 2 the derivation of the average particle velocity.", "[AvgParticleVelocity]" ) {
   /*
    * Test case:
    *  h:  9 | 16
    *  u: -5 | 8
    * particleVelocityAvg : ( -5 * \sqrt(9) + 8 * \sqrt(16) ) / ( \sqrt(9) + \sqrt(16) )
    *                           = ( -15 + 32 ) / 7 = 17 / 7 = 2.42857143
   **/
  float l_velocity= 0;
  tsunami_lab::solvers::F_Wave::particleVelocityAvg(  9,
                                                      16,
                                                      -5,
                                                      8,
                                                      l_velocity );

  REQUIRE( l_velocity == Approx( 2.42857143 ) );
}

TEST_CASE( "Test 1 the derivation of the F wave speeds.", "[FWaveSpeeds]" ) {
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
  tsunami_lab::solvers::F_Wave::waveSpeeds( 	14,
						9,
		                                -4,
		                               	3,
		                               	l_waveSpeedL,
		      				l_waveSpeedR  );
  REQUIRE( l_waveSpeedL == Approx( -11.5047 ) );
  REQUIRE( l_waveSpeedR == Approx( 9.73459 ) );
}

TEST_CASE( "Test 2 the derivation of the F wave speeds.", "[FWaveSpeeds]" ) {
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
  tsunami_lab::solvers::F_Wave::waveSpeeds( 25,
                                            36,
                                            -8,
                                            9,
                                            l_waveSpeedL,
                                            l_waveSpeedR  );
  REQUIRE( l_waveSpeedL == Approx( -16.0219 ) );
  REQUIRE( l_waveSpeedR == Approx(  18.5673 ) );
}

TEST_CASE( "Test the derivation of the F wave speeds.", "[FWaveStrength]" ) {
  /*
   * Test case:
   *  h:  16  | 9
   *  u:  -3  | 5
   *  hu: -48 | 45
   *
   * The derivation of the Roe speeds (s1, s2) is given above.
   * Matrix of right eigenvectors:
   *
   *     | 1   1  |
   * R = |        |
   *     | s1  s2 |
   *
   * Inversion yields:
   * F wave height :  12.5
   * F wave velocity : 0.4285714285714285
   * F wave speed : s1 = 0.4285714285714285 - sqrt(9.80665 * 12.5) = -10.6432
   * F wave speed : s2 = 0.4285714285714285 + sqrt(9.80665 * 12.5) = 11.5002
   * wolframalpha.com query: invert {{1, 1}, {-10.6432, 11.5002}}
   *
   *           |0.519351  -0.0451602|
   * Rinv =    |                    |
   *           |0.480649  0.0451602 |
   *
   * Multiplication with the jump in quantities gives the wave strength:
   *
   * wolframalpha.com query: {{0.519351, -0.0451602}, {0.480649, 0.0451602}} * {9-16, 45--48}
   *
   *           |0.519353  -0.04516|     | 9-16  |     |-7.83536  |
   *           |                  |  *  |       |  =  |          |
   *           |0.480647  0.04516 |     |45--48 |     |0.835356 |
   */
  float l_strengthL = 0;
  float l_strengthR = 0;

  float l_waveSpeedL = -10.6432;
  float l_waveSpeedR = 11.5003;
  tsunami_lab::solvers::F_Wave::waveStrengths(	16,
                                                9,
                                                -48,
                                                45,
                                                l_waveSpeedL,
                                                l_waveSpeedR,
                                                l_strengthL,
                                                l_strengthR	);
  REQUIRE( l_strengthL == Approx(-7.83536 ) );
  REQUIRE( l_strengthR == Approx(0.835356) );
}


TEST_CASE( "Test the derivation of the F Wave net-updates.", "[RoeUpdates]" ) {
  /*
   * Test case:
   *
   *      left | right
   *  h:    16 | 9
   *  u:    -3 | 5
   *  hu:  -48 | 45
   *
   * The derivation of the FWave speeds (s1, s2) and wave strengths (a1, a1) is given above.
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                    |  1 |   | -3.99675  |
   * update #1:  a1  *  |    | = |           |
   *                    | s1 |   | -42.5382  |
   *
   *                    |  1 |   | -3.00325 |
   * update #2:  a2  *  |    | = |          |
   *                    | s2 |   | -34.5383 |
   */
   float l_netUpdatesL[2] = { 0, 0 };
   float l_netUpdatesR[2] = { 0, 0 };

   tsunami_lab::solvers::F_Wave::netUpdates(  16,
                                              9,
                                              -48,
                                              45,
                                              l_netUpdatesL,
                                              l_netUpdatesR );
   REQUIRE( l_netUpdatesL[0] == Approx( -7.83536  ) );
   REQUIRE( l_netUpdatesL[1] == Approx( 83.3933   ) );
   REQUIRE( l_netUpdatesR[0] == Approx(  0.835356 ) );
   REQUIRE( l_netUpdatesR[1] == Approx( -9.60676  ) );

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

   tsunami_lab::solvers::F_Wave::netUpdates(  10,
                                              10,
                                              0,
                                              0,
                                              l_netUpdatesL,
                                              l_netUpdatesR );
   REQUIRE( l_netUpdatesL[0] == Approx( 0 ) );
   REQUIRE( l_netUpdatesL[1] == Approx( 0 ) );
   REQUIRE( l_netUpdatesR[0] == Approx( 0 ) );
   REQUIRE( l_netUpdatesR[1] == Approx( 0 ) );

  /*
   * Test case (dam break):
   *
   *     left | right
   *   h:  16 | 9
   *   u:   3 | 5
   *   hu: 48 | 45
   *
   * The derivation of the Roe speeds (s1, s2) is given above.
   * Matrix of right eigenvectors:
   *
   *     | 1   1  |
   * R = |        |
   *     | s1  s2 |
   *
   * Inversion yields:
   * F wave height :  12.5
   * F wave velocity : 3.85714285714285
   * F wave speed : s1 = 3.85714285714285 - sqrt(9.909665 * 12.5) = -7.27528
   * F wave speed : s2 = 3.85714285714285 + sqrt(9.909665 * 12.5) = 14.9869
   * wolframalpha.com query: invert {{1, 1}, {-7.27582, 14.9869}}
   *
   *           |0.673184  -0.0449181|
   * Rinv =    |                    |
   *           |0.326816  0.0449181 |
   *
   * Multiplication with the jump in quantities gives the wave strength:
   *
   * wolframalpha.com query: {{0.673184,  -0.0449181}, {0.326816,  0.0449181 }} * {9-16, 45-48>
   *
   *           |0.673184  -0.0449181|     | 9-16 |     |-4.57753|
   *           |                    |  *  |      |  =  |        |
   *           |0.326816,  0.0449181|     | 45-48|     |-2.42247|
   *
   * The derivation of the FWave speeds (s1, s2) and wave strengths (a1, a1) is given above.
   *
   * The net-updates are given through the scaled eigenvectors.
   *
   *                          |     1     |   | -4.57753 |
   * update #1:  -4.57753  *  |           | = |          |
   *                          |  -7.27528 |   | 33.3028  |
   *
   *                          |     1     |   | -2.87165 |
   * update #2:  -2.42247  *  |           | = |          |
   *                          |  14.9869  |   | -36.3053 |
   */

   tsunami_lab::solvers::F_Wave::netUpdates(    16,
                                                9,
                                                48,
                                                45,
                                                l_netUpdatesL,
                                                l_netUpdatesR );
   REQUIRE( l_netUpdatesL[0] == Approx( -4.57753 ) );
   REQUIRE( l_netUpdatesL[1] == Approx( 33.3028  ) );
   REQUIRE( l_netUpdatesR[0] == Approx( -2.87165 ) );
   REQUIRE( l_netUpdatesR[1] == Approx( -36.3053 ) );
}
