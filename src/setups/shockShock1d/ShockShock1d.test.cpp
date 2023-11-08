/**ShockShock1d
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Tests the shock shock setup.
 **/
#include <catch2/catch.hpp>
#include "ShockShock1d.h"

TEST_CASE("Test the one-dimensional shock shock setup.", "[ShockShock1d]")
{
  tsunami_lab::setups::ShockShock1d l_shockShock(25,
                                                 55,
                                                 3);

  // left side
  REQUIRE(l_shockShock.getHeight(2, 0) == 25);

  REQUIRE(l_shockShock.getMomentumX(2, 0) == 55);

  REQUIRE(l_shockShock.getMomentumY(2, 0) == 0);

  REQUIRE(l_shockShock.getBathymetry(2, 0) == 0);

  REQUIRE(l_shockShock.getHeight(2, 5) == 25);

  REQUIRE(l_shockShock.getMomentumX(2, 5) == 55);

  REQUIRE(l_shockShock.getMomentumY(2, 2) == 0);

  REQUIRE(l_shockShock.getBathymetry(2, 2) == 0);

  // right side
  REQUIRE(l_shockShock.getHeight(4, 0) == 25);

  REQUIRE(l_shockShock.getMomentumX(4, 0) == -55);

  REQUIRE(l_shockShock.getMomentumY(4, 0) == 0);

  REQUIRE(l_shockShock.getBathymetry(4, 0) == 0);

  REQUIRE(l_shockShock.getHeight(4, 5) == 25);

  REQUIRE(l_shockShock.getMomentumX(4, 5) == -55);

  REQUIRE(l_shockShock.getMomentumY(4, 2) == 0);

  REQUIRE(l_shockShock.getBathymetry(4, 2) == 0);
}