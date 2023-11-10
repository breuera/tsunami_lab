/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/
#include <catch2/catch.hpp>
#include "CustomSetup1d.h"

TEST_CASE( "Test the one-dimensional custom setup.", "[CustomSetup1d]" ) {
    tsunami_lab::setups::CustomSetup1d l_custom_setup(  10, 
                                                        8, 
                                                        -6, 
                                                        4, 
                                                        5);

    // left side
  REQUIRE( l_custom_setup.getHeight( 2, 0 ) == 10 );
  REQUIRE( l_custom_setup.getMomentumX( 2, 0 ) == -6 );
  REQUIRE( l_custom_setup.getMomentumY( 2, 0 ) == 0 );
  REQUIRE( l_custom_setup.getBathymetry( 2, 0 ) == 0 );

  REQUIRE( l_custom_setup.getHeight( 2, 5 ) == 10 );
  REQUIRE( l_custom_setup.getMomentumX( 2, 5 ) == -6 );
  REQUIRE( l_custom_setup.getMomentumY( 2, 2 ) == 0 );
  REQUIRE( l_custom_setup.getBathymetry( 2, 2 ) == 0 );

  // right side
  REQUIRE( l_custom_setup.getHeight( 6, 0 ) == 8 );
  REQUIRE( l_custom_setup.getMomentumX( 6, 0 ) == 4 );
  REQUIRE( l_custom_setup.getMomentumY( 6, 0 ) == 0 );
  REQUIRE( l_custom_setup.getBathymetry( 6, 0 ) == 0 );

  REQUIRE( l_custom_setup.getHeight( 6, 5 ) == 8 );
  REQUIRE( l_custom_setup.getMomentumX( 6, 5 ) == 4 );
  REQUIRE( l_custom_setup.getMomentumY( 6, 2 ) == 0 );
  REQUIRE( l_custom_setup.getBathymetry( 6, 0 ) == 0 );
}