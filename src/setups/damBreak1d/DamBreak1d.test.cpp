/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Tests the dam break setup.
 **/
#include <catch2/catch.hpp>
#include "DamBreak1d.h"

TEST_CASE( "Test the one-dimensional dam break setup.", "[DamBreak1d]" ) {
  tsunami_lab::setups::DamBreak1d l_damBreak( 25,
                                              55,
                                               3 );

  // left side
  REQUIRE( l_damBreak.getHeight( 2, 0 ) == 25 );

  REQUIRE( l_damBreak.getMomentumX( 2, 0 ) == 0 );

  REQUIRE( l_damBreak.getMomentumY( 2, 0 ) == 0 );

  REQUIRE( l_damBreak.getHeight( 2, 5 ) == 25 );

  REQUIRE( l_damBreak.getMomentumX( 2, 5 ) == 0 );

  REQUIRE( l_damBreak.getMomentumY( 2, 2 ) == 0 );

  // right side
  REQUIRE( l_damBreak.getHeight( 4, 0 ) == 55 );

  REQUIRE( l_damBreak.getMomentumX( 4, 0 ) == 0 );

  REQUIRE( l_damBreak.getMomentumY( 4, 0 ) == 0 );

  REQUIRE( l_damBreak.getHeight( 4, 5 ) == 55 );

  REQUIRE( l_damBreak.getMomentumX( 4, 5 ) == 0 );

  REQUIRE( l_damBreak.getMomentumY( 4, 2 ) == 0 );  
}