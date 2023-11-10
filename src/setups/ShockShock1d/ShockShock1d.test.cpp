/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Test shock-shock setup.
 **/
#include "ShockShock1d.h"
#include <catch2/catch.hpp>

TEST_CASE( "Test the one-dimensional shock-shock setup.", "[ShockShock1d]" ) {
    tsunami_lab::setups::ShockShock1d l_shockShock( 10,
                                                    8,
                                                    3 );

    // left side
    REQUIRE( l_shockShock.getHeight( 1, 0 ) == 10 );
    REQUIRE( l_shockShock.getHeight( 2.5, 0 ) == 10 );
    REQUIRE( l_shockShock.getHeight( 3, 0 ) == 10 );

    REQUIRE( l_shockShock.getMomentumX( 1, 0 ) == 8 );
    REQUIRE( l_shockShock.getMomentumX( 2.5, 0 ) == 8 );
    REQUIRE( l_shockShock.getMomentumX( 3, 0 ) == 8 );

    REQUIRE( l_shockShock.getMomentumY( 1, 0 ) == 0 );
    REQUIRE( l_shockShock.getMomentumY( 2.5, 0 ) == 0 );
    REQUIRE( l_shockShock.getMomentumY( 3, 0 ) == 0 );

    REQUIRE( l_shockShock.getBathymetry( 1, 0 ) == 0);
    REQUIRE( l_shockShock.getBathymetry( 1.25, 0 ) == 0);
    REQUIRE( l_shockShock.getBathymetry( 3, 0 ) == 0);

  // right side
    REQUIRE( l_shockShock.getHeight( 4, 0 ) == 10 );
    REQUIRE( l_shockShock.getHeight( 7.5, 0 ) == 10 );
    REQUIRE( l_shockShock.getHeight( 10, 0 ) == 10 );

    REQUIRE( l_shockShock.getMomentumX( 4, 0 ) == -8 );
    REQUIRE( l_shockShock.getMomentumX( 8.5, 0 ) == -8 );
    REQUIRE( l_shockShock.getMomentumX( 13, 0 ) == -8 );

    REQUIRE( l_shockShock.getMomentumY( 12, 0 ) == 0 );
    REQUIRE( l_shockShock.getMomentumY( 12.5, 0 ) == 0 );
    REQUIRE( l_shockShock.getMomentumY( 23, 0 ) == 0 ); 

    REQUIRE( l_shockShock.getBathymetry( 4, 0 ) == 0);
    REQUIRE( l_shockShock.getBathymetry( 7.5, 0 ) == 0);
    REQUIRE( l_shockShock.getBathymetry( 13, 0 ) == 0); 
}