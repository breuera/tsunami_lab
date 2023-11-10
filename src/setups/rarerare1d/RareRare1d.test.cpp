/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional Rare-Rare problem.
 **/
#include <catch2/catch.hpp>
#include "RareRare1d.h"

TEST_CASE("Test the one-dimensional Rare-Rare setup.", "[RareRare1d]")
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