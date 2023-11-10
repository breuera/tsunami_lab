/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Test rare-rare setup.
 **/
#include "SubcriticalFlow1d.h"
#include <catch2/catch.hpp>

TEST_CASE( "Test the one-dimensional subcritical flow setup.", "[SubcriticalFlow1d]" ) {
    tsunami_lab::setups::SubcriticalFlow1d l_subcriticalFlow( tsunami_lab::t_real( 4.42 ) );

    // test getHeight
    REQUIRE( l_subcriticalFlow.getHeight( 1, 0 ) == 2 );
    REQUIRE( l_subcriticalFlow.getHeight( 8, 0 ) == 2 );
    REQUIRE( l_subcriticalFlow.getHeight( 10, 0 ) == tsunami_lab::t_real( 1.8 ) );
    REQUIRE( l_subcriticalFlow.getHeight( 12, 0 ) == 2 );
    REQUIRE( l_subcriticalFlow.getHeight( 25, 0 ) == 2 );

    REQUIRE( l_subcriticalFlow.getHeight( 1, 3 ) == 2 );
    REQUIRE( l_subcriticalFlow.getHeight( 8, 4 ) == 2 );
    REQUIRE( l_subcriticalFlow.getHeight( 10, 5 ) == tsunami_lab::t_real( 1.8 ) );
    REQUIRE( l_subcriticalFlow.getHeight( 12, 4 ) == 2 );
    REQUIRE( l_subcriticalFlow.getHeight( 25, 3 ) == 2 );

    //test getMomentumX
    REQUIRE( l_subcriticalFlow.getMomentumX( 1, 0 ) == tsunami_lab::t_real( 4.42 ) );
    REQUIRE( l_subcriticalFlow.getMomentumX( 12.5, 0 ) == tsunami_lab::t_real( 4.42 ) );
    REQUIRE( l_subcriticalFlow.getMomentumX( 25, 0 ) == tsunami_lab::t_real( 4.42 ) );

    REQUIRE( l_subcriticalFlow.getMomentumX( 1, 3 ) == tsunami_lab::t_real( 4.42 ) );
    REQUIRE( l_subcriticalFlow.getMomentumX( 12.5, 4 ) == tsunami_lab::t_real( 4.42 ) );
    REQUIRE( l_subcriticalFlow.getMomentumX( 25, 3 ) == tsunami_lab::t_real( 4.42 ) );

    //test getMomentumY
    REQUIRE( l_subcriticalFlow.getMomentumY( 1, 0 ) == 0 );
    REQUIRE( l_subcriticalFlow.getMomentumY( 12.5, 0 ) == 0 );
    REQUIRE( l_subcriticalFlow.getMomentumY( 25, 0 ) == 0 );

    REQUIRE( l_subcriticalFlow.getMomentumY( 1, 3 ) == 0 );
    REQUIRE( l_subcriticalFlow.getMomentumY( 12.5, 4 ) == 0 );
    REQUIRE( l_subcriticalFlow.getMomentumY( 25, 3 ) == 0 );

    //test getBathymetry
    REQUIRE( l_subcriticalFlow.getBathymetry( 1, 0 ) == -2 );
    REQUIRE( l_subcriticalFlow.getBathymetry( 8, 0 ) == -2 );
    REQUIRE( l_subcriticalFlow.getBathymetry( 10, 0 ) == tsunami_lab::t_real( -1.8 ) );
    REQUIRE( l_subcriticalFlow.getBathymetry( 12, 0 ) == -2 );
    REQUIRE( l_subcriticalFlow.getBathymetry( 25, 0 ) == -2 );

    REQUIRE( l_subcriticalFlow.getBathymetry( 1, 3 ) == -2 );
    REQUIRE( l_subcriticalFlow.getBathymetry( 8, 4 ) == -2 );
    REQUIRE( l_subcriticalFlow.getBathymetry( 10, 5 ) == tsunami_lab::t_real( -1.8 ) );
    REQUIRE( l_subcriticalFlow.getBathymetry( 12, 4 ) == -2 );
    REQUIRE( l_subcriticalFlow.getBathymetry( 25, 3 ) == -2 ); 
}