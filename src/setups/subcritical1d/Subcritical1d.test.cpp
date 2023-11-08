/**Subcritical1d
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Tests the subcritical setup.
 **/
#include <catch2/catch.hpp>
#include "Subcritical1d.h"

TEST_CASE("Test the one-dimensional subcritical setup.", "[Subcritical1d]")
{
  tsunami_lab::setups::Subcritical1d l_subcritical;

  // x = 2
  REQUIRE(l_subcritical.getHeight(2, 0) == 2);

  REQUIRE(l_subcritical.getMomentumX(2, 0) == 4.42f);

  REQUIRE(l_subcritical.getMomentumY(2, 0) == 0);

  REQUIRE(l_subcritical.getBathymetry(2, 0) == -2);

  // x element of 8-12
  REQUIRE(l_subcritical.getHeight(10, 0) == 1.8f);

  REQUIRE(l_subcritical.getMomentumX(10, 0) == 4.42f);

  REQUIRE(l_subcritical.getMomentumY(4, 0) == 0);

  REQUIRE(l_subcritical.getBathymetry(10, 0) == -1.8f);

  // x element over 25

  REQUIRE(l_subcritical.getHeight(30, 0) == 0);

  REQUIRE(l_subcritical.getMomentumX(30, 0) == 0);

  REQUIRE(l_subcritical.getMomentumY(30, 0) == 0);

  REQUIRE(l_subcritical.getBathymetry(30, 0) == -2);
}