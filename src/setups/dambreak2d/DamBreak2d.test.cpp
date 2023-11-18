/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional dam break problem.
 **/
#include <catch2/catch.hpp>
#include "DamBreak2d.h"
#include <iostream>

TEST_CASE("Test the two-dimensional dam break setup.", "[DamBreak2d]")
{
  tsunami_lab::setups::DamBreak2d l_damBreak;

  // outside dam-circle
  REQUIRE(l_damBreak.getHeight(0, 0) == 5);

  REQUIRE(l_damBreak.getMomentumX(0, 0) == 0);

  REQUIRE(l_damBreak.getMomentumY(0, 0) == 0);

  REQUIRE(l_damBreak.getBathymetry(0, 0) == 0);

  // inside dam-circle
  REQUIRE(l_damBreak.getHeight(50, 50) == 10);

  REQUIRE(l_damBreak.getMomentumX(50, 50) == 0);

  REQUIRE(l_damBreak.getMomentumY(50, 50) == 0);

  REQUIRE(l_damBreak.getBathymetry(50, 50) == 0);

  // on batometry-cylinder
  // REQUIRE(l_damBreak.getBathymetry(10, 25) == 10);
}