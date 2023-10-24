#include <catch2/catch.hpp>
#define private public
#include "fwave.h"
#undef public

TEST_CASE( "Testing The InverseMatrix ", "[InverseMatrix]" ) {

  float o_inverse[4];
  tsunami_lab::solvers::fwave::inverseMatrix( 2,3,o_inverse);
  REQUIRE( o_inverse[0] == 3 );
  REQUIRE( o_inverse[1] == -1 );
  REQUIRE( o_inverse[2] == -2 );
  REQUIRE( o_inverse[3] == 1 );
}

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