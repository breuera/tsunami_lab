/**ShockShock1d
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Tests the rarefaction rarefaction setup.
 **/
#include <catch2/catch.hpp>
#include "RareRare1d.h"

TEST_CASE("Test the one-dimensional rarefaction rarefaction wave setup.", "[RareRare1d]")
{
  tsunami_lab::setups::RareRare1d l_rareRare(25,
                                             55,
                                             3);

  // left side
  REQUIRE(l_rareRare.getHeight(2, 0) == 25);

  REQUIRE(l_rareRare.getMomentumX(2, 0) == -55);

  REQUIRE(l_rareRare.getMomentumY(2, 0) == 0);

  REQUIRE(l_rareRare.getBathymetry(2, 0) == 0);

  REQUIRE(l_rareRare.getHeight(2, 5) == 25);

  REQUIRE(l_rareRare.getMomentumX(2, 5) == -55);

  REQUIRE(l_rareRare.getMomentumY(2, 2) == 0);

  REQUIRE(l_rareRare.getBathymetry(2, 2) == 0);

  // right side
  REQUIRE(l_rareRare.getHeight(4, 0) == 25);

  REQUIRE(l_rareRare.getMomentumX(4, 0) == 55);

  REQUIRE(l_rareRare.getMomentumY(4, 0) == 0);

  REQUIRE(l_rareRare.getBathymetry(4, 0) == 0);

  REQUIRE(l_rareRare.getHeight(4, 5) == 25);

  REQUIRE(l_rareRare.getMomentumX(4, 5) == 55);

  REQUIRE(l_rareRare.getMomentumY(4, 2) == 0);

  REQUIRE(l_rareRare.getBathymetry(4, 2) == 0);
}