/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Test rare-rare setup.
 **/
#include "RareRare1d.h"
#include <catch2/catch.hpp>

TEST_CASE( "Test the one-dimensional rare-rare setup.", "[RareRare1d]" ) {
    tsunami_lab::setups::RareRare1d l_rareRare( 25,
                                                8,
                                                3 );

    // left side
    REQUIRE( l_rareRare.getHeight( 1, 0 ) == 25 );
    REQUIRE( l_rareRare.getHeight( 2.5, 0 ) == 25 );
    REQUIRE( l_rareRare.getHeight( 3, 0 ) == 25 );

    REQUIRE( l_rareRare.getMomentumX( 1, 0 ) == -8 );
    REQUIRE( l_rareRare.getMomentumX( 2.5, 0 ) == -8 );
    REQUIRE( l_rareRare.getMomentumX( 3, 0 ) == -8 );

    REQUIRE( l_rareRare.getMomentumY( 1, 0 ) == 0 );
    REQUIRE( l_rareRare.getMomentumY( 2.5, 0 ) == 0 );
    REQUIRE( l_rareRare.getMomentumY( 3, 0 ) == 0 );

    REQUIRE( l_rareRare.getBathymetry( 1, 0 ) == 0 );
    REQUIRE( l_rareRare.getBathymetry( 2.5, 0 ) == 0 );
    REQUIRE( l_rareRare.getBathymetry( 3, 0 ) == 0 );

  // right side
    REQUIRE( l_rareRare.getHeight( 4, 0 ) == 25 );
    REQUIRE( l_rareRare.getHeight( 7.5, 0 ) == 25 );
    REQUIRE( l_rareRare.getHeight( 10, 0 ) == 25 );

    REQUIRE( l_rareRare.getMomentumX( 4, 0 ) == 8 );
    REQUIRE( l_rareRare.getMomentumX( 8.5, 0 ) == 8 );
    REQUIRE( l_rareRare.getMomentumX( 13, 0 ) == 8 );

    REQUIRE( l_rareRare.getMomentumY( 12, 0 ) == 0 );
    REQUIRE( l_rareRare.getMomentumY( 12.5, 0 ) == 0 );
    REQUIRE( l_rareRare.getMomentumY( 23, 0 ) == 0 );  

    REQUIRE( l_rareRare.getBathymetry( 4, 0 ) == 0 );
    REQUIRE( l_rareRare.getBathymetry( 12.5, 0 ) == 0 );
    REQUIRE( l_rareRare.getBathymetry( 13, 0 ) == 0 );
}