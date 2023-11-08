/**Custom1d
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Tests the custom setup.
 **/
#include <catch2/catch.hpp>
#include "Custom1d.h"

TEST_CASE("Test the one-dimensional custom wave setup.", "[Custom1d]")
{
    tsunami_lab::setups::Custom1d l_custom(25,
                                           55,
                                           3,
                                           4,
                                           3);

    // left side
    REQUIRE(l_custom.getHeight(2, 0) == 25);

    REQUIRE(l_custom.getMomentumX(2, 0) == 3);

    REQUIRE(l_custom.getMomentumY(2, 0) == 0);

    REQUIRE(l_custom.getBathymetry(2, 0) == 0);

    REQUIRE(l_custom.getHeight(2, 5) == 25);

    REQUIRE(l_custom.getMomentumX(2, 5) == 3);

    REQUIRE(l_custom.getMomentumY(2, 2) == 0);

    REQUIRE(l_custom.getBathymetry(2, 2) == 0);

    // right side
    REQUIRE(l_custom.getHeight(4, 0) == 55);

    REQUIRE(l_custom.getMomentumX(4, 0) == 4);

    REQUIRE(l_custom.getMomentumY(4, 0) == 0);

    REQUIRE(l_custom.getBathymetry(4, 0) == 0);

    REQUIRE(l_custom.getHeight(4, 5) == 55);

    REQUIRE(l_custom.getMomentumX(4, 5) == 4);

    REQUIRE(l_custom.getMomentumY(4, 2) == 0);

    REQUIRE(l_custom.getBathymetry(4, 2) == 0);
}