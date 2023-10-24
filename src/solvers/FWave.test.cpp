/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Unit tests of the F wave solver.
 **/
#include <catch2/catch.hpp>
#define private public
#include "F_wafe.h"
#undef public

TEST_CASE( "Test the derivation of the average Hights.", "[AvgHights]" ) {
   /*
    * Test case:
    *  h: 10 | 5
    *
    * roe height: 1/2 (10 + 5) = 7.5
    */
  float l_height= 0;
  tsunami_lab::solvers::F_wave::heightAvg( 	10,
                                         	5,
                                         	l_hight );

  REQUIRE( l_hight == Approx( 7.5 ) );
}

TEST_CASE( "Test the derivation of the average Hights.", "[AvgHights]" ) {
   /*
    * Test case:
    *  h: 7.18923 | 8.32434
    *
    * avgHeight: 1/2 (7.18923 + 8.32434) = 7.756785
    */
  float l_height= 0;
  tsunami_lab::solvers::F_wave::heightAvg(     7.18923,
                                                8.32434,
                                                l_hight );

  REQUIRE( l_hight == Approx( 7.756785 ) );
}

TEST_CASE( "Test the derivation of the average particle velocity.", "[AvgParticleVelocity]" ) {
   /*
    * Test case:
    *  h: 4 | 9
    *  u: -3  | 3.3
    * particleVelocityAvg : ( -3 * \sqrt(4) + 3.3 * \sqrt(9) ) / ( \sqrt(4) + \sqrt(9) )
    * 				= ( -6 + 9.9 ) / 5 = 3.9 / 5 = 0.78
   **/
  float l_velocity= 0;
  tsunami_lab::solvers::F_wave::particleVelocityAvg(    4,
                                                	9,
							-3,
							3.3,
                                                	l_velocity );

  REQUIRE( l_velocity == Approx( 0.78 ) );
}

TEST_CASE( "Test the derivation of the average particle velocity.", "[AvgParticleVelocity]>
   /*
    * Test case:
    *  h:  9 | 16
    *  u: -5 | 8
    * particleVelocityAvg : ( -5 * \sqrt(9) + 8 * \sqrt(16) ) / ( \sqrt(9) + \sqrt(16) )
    *                           = ( -15 + 32 ) / 7 = 17 / 7 = 2.42857143
   **/
  float l_velocity= 0;
  tsunami_lab::solvers::F_wave::particleVelocityAvg(    9,
                                                        16,
                                                        -5,
                                                        8,
                                                        l_velocity );

  REQUIRE( l_velocity == Approx( 2.42857143 ) );
}

TEST_CASE( "Test the derivation of the F wave speeds.", "[FWaveSpeeds]" ) {
   /**
    * Test case:
    *  h: 14 | 9
    *  u: -4 | 3
    *
    * F wave height : 0.5 * ( 14 + 9 ) = 11.5
    * F wave velocity : ( sqrt(14) * -4 + sqrt(9) * 3 ) / ( sqrt(14) + sqrt(9) )
    * 			= -0.8850389755494463
    * F wave speed : s1 = -0.8850389755494463 - sqrt(9.909665 * 11.5) = -11.5603
    * F wave speed : s2 = -0.8850389755494463 + sqrt(9.909665 * 11.5) =   9.79022
   **/
  float l_waveSpeedL = 0;
  float l_waveSpeedR = 0;
  tsunami_lab::solvers::F_wave::waveSpeeds(	14,
						-4,
						9,
						3,
						l_waveSpeedL,
						l_waveSpeedR	);
 REQUIRE( l_waveSpeedL == Approx( -11.5603 ) );
 REQUIRE( l_waveSpeedR == Approx( 9.79022 ) );
}

TEST_CASE( "Test the derivation of the F wave speeds.", "[FWaveSpeeds]" ) {
   /**
    * Test case:
    *  h: 25 |36
    *  u: -8 | 9
    *
    * F wave height : 0.5 * ( 25 + 36 ) = 25.5
    * F wave velocity : ( sqrt(25) * -8 + sqrt(36) * 9 ) / ( sqrt(25) + sqrt(36) )
    *                   = 1.2727272727272727
    * F wave speed : s1 = 1.2727272727272727 - sqrt(9.909665 * 25.5) = -14.6237
    * F wave speed : s2 = 1.2727272727272727 + sqrt(9.909665 * 25.5) =  17.1692
   **/
  float l_waveSpeedL = 0;
  float l_waveSpeedR = 0;
  tsunami_lab::solvers::F_wave::waveSpeeds(     25,
                                                36,
                                                -8,
                                                9,
                                                l_waveSpeedL,
                                                l_waveSpeedR    );
 REQUIRE( l_waveSpeedL == Approx( -14.6237 ) );
 REQUIRE( l_waveSpeedR == Approx( 17.1692 ) );
}

TEST_CASE( "Test the derivation of the F wave speeds.", "[FWaveStrength]" ) {
  /*
   * Test case:
   *  h:  16 | 9
   *  u:  -3 | 4
   *  hu: 
  */
}
