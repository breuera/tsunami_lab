/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional supercritical problem.
 **/
#include <catch2/catch.hpp>
#include "Supercritical1d.h"

TEST_CASE("Test the one-dimensional Supercritical1d setup.", "[Supercritical1d]")
{
  tsunami_lab::setups::Supercritical1d l_supercritical_1d;

  // x in [8,12]
  REQUIRE(l_supercritical_1d.getHeight(10, 0) == 1.8f);

  REQUIRE(l_supercritical_1d.getMomentumX(10, 0) == 4.42f);

  REQUIRE(l_supercritical_1d.getMomentumY(10, 0) == 0);

  REQUIRE(l_supercritical_1d.getBathymetry(10, 0) == -1.8f);

  // x in [0,25] AND x notin [8,12]
  REQUIRE(l_supercritical_1d.getHeight(4, 0) == 2);

  REQUIRE(l_supercritical_1d.getMomentumX(4, 0) == 4.42f);

  REQUIRE(l_supercritical_1d.getMomentumY(4, 0) == 0);

  REQUIRE(l_supercritical_1d.getBathymetry(4, 0) == -2);

  // x > 25 (same for x < 0)
  REQUIRE(l_supercritical_1d.getHeight(30, 0) == 0);

  REQUIRE(l_supercritical_1d.getMomentumX(30, 0) == 0);

  REQUIRE(l_supercritical_1d.getMomentumY(30, 0) == 0);

  REQUIRE(l_supercritical_1d.getBathymetry(30, 0) == -2);
}