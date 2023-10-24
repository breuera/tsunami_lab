#include <catch2/catch.hpp>
#define private public
#include "fwave.h"
#undef public

TEST_CASE( "Testing The Eigenvalues ", "[EigenValues]" ) {

  float eigenVal1 = 0;
  float eigenVal2 = 0;
  tsunami_lab::solvers::fwave::eigenwerte( 10,
                                         9,
                                         -3,
                                         3,
                                         eigenVal1,
                                         eigenVal2 );

  REQUIRE( eigenVal1 == Approx( -9.7311093998375095 ) );
  REQUIRE( eigenVal2 == Approx(  9.5731051658991654 ) );
}