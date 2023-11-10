/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Test rare-rare setup.
 **/
#include "SupercriticalFlow1d.h"

#include <catch2/catch.hpp>

TEST_CASE("Test the one-dimensional supercritical flow setup.", "[SupercriticalFlow1d]") {
    tsunami_lab::setups::SupercriticalFlow1d l_supercriticalFlow(tsunami_lab::t_real(0.18));

    // test getHeight
    REQUIRE(l_supercriticalFlow.getHeight(1, 0) == tsunami_lab::t_real(0.33));
    REQUIRE(l_supercriticalFlow.getHeight(8, 0) == tsunami_lab::t_real(0.33));
    REQUIRE(l_supercriticalFlow.getHeight(10, 0) == tsunami_lab::t_real(0.13));
    REQUIRE(l_supercriticalFlow.getHeight(12, 0) == tsunami_lab::t_real(0.33));
    REQUIRE(l_supercriticalFlow.getHeight(25, 0) == tsunami_lab::t_real(0.33));

    REQUIRE(l_supercriticalFlow.getHeight(1, 3) == tsunami_lab::t_real(0.33));
    REQUIRE(l_supercriticalFlow.getHeight(8, 4) == tsunami_lab::t_real(0.33));
    REQUIRE(l_supercriticalFlow.getHeight(10, 5) == tsunami_lab::t_real(0.13));
    REQUIRE(l_supercriticalFlow.getHeight(12, 4) == tsunami_lab::t_real(0.33));
    REQUIRE(l_supercriticalFlow.getHeight(25, 3) == tsunami_lab::t_real(0.33));

    // test getMomentumX
    REQUIRE(l_supercriticalFlow.getMomentumX(1, 0) == tsunami_lab::t_real(0.18));
    REQUIRE(l_supercriticalFlow.getMomentumX(12.5, 0) == tsunami_lab::t_real(0.18));
    REQUIRE(l_supercriticalFlow.getMomentumX(25, 0) == tsunami_lab::t_real(0.18));

    REQUIRE(l_supercriticalFlow.getMomentumX(1, 3) == tsunami_lab::t_real(0.18));
    REQUIRE(l_supercriticalFlow.getMomentumX(12.5, 4) == tsunami_lab::t_real(0.18));
    REQUIRE(l_supercriticalFlow.getMomentumX(25, 3) == tsunami_lab::t_real(0.18));

    // test getMomentumY
    REQUIRE(l_supercriticalFlow.getMomentumY(1, 0) == 0);
    REQUIRE(l_supercriticalFlow.getMomentumY(12.5, 0) == 0);
    REQUIRE(l_supercriticalFlow.getMomentumY(25, 0) == 0);

    REQUIRE(l_supercriticalFlow.getMomentumY(1, 3) == 0);
    REQUIRE(l_supercriticalFlow.getMomentumY(12.5, 4) == 0);
    REQUIRE(l_supercriticalFlow.getMomentumY(25, 3) == 0);

    // test getBathymetry
    REQUIRE(l_supercriticalFlow.getBathymetry(1, 0) == tsunami_lab::t_real(-0.33));
    REQUIRE(l_supercriticalFlow.getBathymetry(8, 0) == tsunami_lab::t_real(-0.33));
    REQUIRE(l_supercriticalFlow.getBathymetry(10, 0) == tsunami_lab::t_real(-0.13));
    REQUIRE(l_supercriticalFlow.getBathymetry(12, 0) == tsunami_lab::t_real(-0.33));
    REQUIRE(l_supercriticalFlow.getBathymetry(25, 0) == tsunami_lab::t_real(-0.33));

    REQUIRE(l_supercriticalFlow.getBathymetry(1, 3) == tsunami_lab::t_real(-0.33));
    REQUIRE(l_supercriticalFlow.getBathymetry(8, 4) == tsunami_lab::t_real(-0.33));
    REQUIRE(l_supercriticalFlow.getBathymetry(10, 5) == tsunami_lab::t_real(-0.13));
    REQUIRE(l_supercriticalFlow.getBathymetry(12, 4) == tsunami_lab::t_real(-0.33));
    REQUIRE(l_supercriticalFlow.getBathymetry(25, 3) == tsunami_lab::t_real(-0.33));
}