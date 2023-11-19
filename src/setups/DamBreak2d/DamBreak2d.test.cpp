/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Tests the dam break setup.
 **/
#include "DamBreak2d.h"

#include <catch2/catch.hpp>

TEST_CASE("Test the two-dimensional dam break setup.", "[DamBreak2d]") {
    tsunami_lab::setups::DamBreak2d l_damBreak(10,
                                               5,
                                               5,
                                               5,
                                               10);

    // inner part
    REQUIRE(l_damBreak.getHeight(2, 2) == 20);
    REQUIRE(l_damBreak.getMomentumX(2, 2) == 0);
    REQUIRE(l_damBreak.getMomentumY(2, 2) == 0);
    REQUIRE(l_damBreak.getBathymetry(2, 2) == -10);

    REQUIRE(l_damBreak.getHeight(2, 5) == 20);
    REQUIRE(l_damBreak.getMomentumX(2, 5) == 0);
    REQUIRE(l_damBreak.getMomentumY(2, 2) == 0);
    REQUIRE(l_damBreak.getBathymetry(2, 2) == -10);

    // outer part
    REQUIRE(l_damBreak.getHeight(8, 8) == 20);
    REQUIRE(l_damBreak.getMomentumX(8, 8) == 0);
    REQUIRE(l_damBreak.getMomentumY(8, 8) == 0);
    REQUIRE(l_damBreak.getBathymetry(8, 8) == -10);

    REQUIRE(l_damBreak.getHeight(-8, -8) == 15);
    REQUIRE(l_damBreak.getMomentumX(-8, -8) == 0);
    REQUIRE(l_damBreak.getMomentumY(-8, -8) == 0);
    REQUIRE(l_damBreak.getBathymetry(-8, -8) == -10);
}