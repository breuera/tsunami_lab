/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional Shock-Shock problem.
 **/
#include <catch2/catch.hpp>
#include "ShockShock1d.h"

TEST_CASE("Test the one-dimensional Shock-Shock setup.", "[ShockShock1d]")
{
  tsunami_lab::setups::ShockShock1d l_shockShock(25,
                                                 55,
                                                 3);

  // left side
  REQUIRE(l_shockShock.getHeight(2, 0) == 25);

  REQUIRE(l_shockShock.getMomentumX(2, 0) == 55);

  REQUIRE(l_shockShock.getMomentumY(2, 0) == 0);

  REQUIRE(l_shockShock.getBathymetry(2, 0) == 5);

  REQUIRE(l_shockShock.getHeight(2, 5) == 25);

  REQUIRE(l_shockShock.getMomentumX(2, 5) == 55);

  REQUIRE(l_shockShock.getMomentumY(2, 2) == 0);

  REQUIRE(l_shockShock.getBathymetry(2, 2) == 5);

  // right side
  REQUIRE(l_shockShock.getHeight(4, 0) == 25);

  REQUIRE(l_shockShock.getMomentumX(4, 0) == -55);

  REQUIRE(l_shockShock.getMomentumY(4, 0) == 0);

  REQUIRE(l_shockShock.getBathymetry(4, 0) == 5);

  REQUIRE(l_shockShock.getHeight(4, 5) == 25);

  REQUIRE(l_shockShock.getMomentumX(4, 5) == -55);

  REQUIRE(l_shockShock.getMomentumY(4, 2) == 0);

  REQUIRE(l_shockShock.getBathymetry(4, 2) == 5);
}