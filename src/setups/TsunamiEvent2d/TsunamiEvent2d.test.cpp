/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional Tsunami Event test.
 **/
#include "TsunamiEvent2d.h"

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("Test the two-dimensional tsunami setup data.", "[TsunamiSetup2d]") {
    tsunami_lab::t_real l_simLenX = 3.5;
    tsunami_lab::t_real l_simLenY = 3.5;
    tsunami_lab::t_idx l_bathymetryDimX = 4;
    tsunami_lab::t_idx l_bathymetryDimY = 4;
    tsunami_lab::t_real l_bathymetryPosX[4] = {-3.0, -2.0, -1.0, 1};
    tsunami_lab::t_real *l_bathymetryPosX_ptr = new tsunami_lab::t_real[4];
    tsunami_lab::t_real l_bathymetryPosY[4] = {-3.0, -2.0, -1.0, 1};
    tsunami_lab::t_real *l_bathymetryPosY_ptr = new tsunami_lab::t_real[4];
    for (tsunami_lab::t_idx l_i = 0; l_i < 4; l_i++) {
        l_bathymetryPosX_ptr[l_i] = l_bathymetryPosX[l_i];
        l_bathymetryPosY_ptr[l_i] = l_bathymetryPosY[l_i];
    }
    tsunami_lab::t_real l_bathymetry[16] = {-8000.0, -7826.086956521738, -7652.173913043477, -7478.260869565216,
                                            -7130.434782608695, -6956.521739130435, -6782.608695652175, -6608.695652173914,
                                            -3478.2608695652175, -3304.3478260869565, -3130.4347826086955, -2956.521739130435,
                                            -521.7391304347826, -173.91304347826087, 0.0, 50.0};
    tsunami_lab::t_real *l_bathymetry_ptr = new tsunami_lab::t_real[16];
    for (tsunami_lab::t_idx l_i = 0; l_i < 16; l_i++) {
        l_bathymetry_ptr[l_i] = l_bathymetry[l_i];
    }
    tsunami_lab::t_idx l_displacementsDimX = 4;
    tsunami_lab::t_idx l_displacementsDimY = 4;
    tsunami_lab::t_real l_displacementsPosX[4] = {-3.0, -2.0, -1.0, 1};
    tsunami_lab::t_real *l_displacementsPosX_ptr = new tsunami_lab::t_real[4];
    tsunami_lab::t_real l_displacementsPosY[4] = {-3.0, -2.0, -1.0, 1};
    tsunami_lab::t_real *l_displacementsPosY_ptr = new tsunami_lab::t_real[4];
    for (tsunami_lab::t_idx l_i = 0; l_i < 4; l_i++) {
        l_displacementsPosX_ptr[l_i] = l_displacementsPosX[l_i];
        l_displacementsPosY_ptr[l_i] = l_displacementsPosY[l_i];
    }
    tsunami_lab::t_real l_displacements[16] = {0, 0, 0, 0,
                                               0, -3.0, -2.0, 0,
                                               0, -1.0, -4.0, 0,
                                               0, 0, 0, 0};
    tsunami_lab::t_real *l_displacements_ptr = new tsunami_lab::t_real[16];
    for (tsunami_lab::t_idx l_i = 0; l_i < 16; l_i++) {
        l_displacements_ptr[l_i] = l_displacements[l_i];
    }
    tsunami_lab::t_real l_epicenterOffsetX = -3;
    tsunami_lab::t_real l_epicenterOffsetY = -3;

    tsunami_lab::setups::TsunamiEvent2d l_setup = tsunami_lab::setups::TsunamiEvent2d(l_simLenX,
                                                                                      l_simLenY,
                                                                                      l_bathymetryDimX,
                                                                                      l_bathymetryDimY,
                                                                                      l_bathymetryPosX_ptr,
                                                                                      l_bathymetryPosY_ptr,
                                                                                      l_bathymetry_ptr,
                                                                                      l_displacementsDimX,
                                                                                      l_displacementsDimY,
                                                                                      l_displacementsPosX_ptr,
                                                                                      l_displacementsPosY_ptr,
                                                                                      l_displacements_ptr,
                                                                                      l_epicenterOffsetX,
                                                                                      l_epicenterOffsetY);

    for (tsunami_lab::t_real l_ceY = 0; l_ceY < 4; l_ceY += 0.5) {
        for (tsunami_lab::t_real l_ceX = 0; l_ceX < 4; l_ceX += 0.5) {
            tsunami_lab::t_real l_momentumX_val = l_setup.getMomentumX(l_ceX, l_ceY);
            tsunami_lab::t_real l_momentumY_val = l_setup.getMomentumY(l_ceX, l_ceY);

            REQUIRE(l_momentumX_val == 0);
            REQUIRE(l_momentumY_val == 0);
        }
    }

    REQUIRE(l_setup.getHeight(0.0, 0.0) == Approx(8000.0));
    REQUIRE(l_setup.getHeight(0.0, 4.0) == Approx(521.7391304347826));
    REQUIRE(l_setup.getHeight(4.0, 0.0) == Approx(7478.260869565216));
    REQUIRE(l_setup.getHeight(4.0, 4.0) == Approx(0));
    REQUIRE(l_setup.getHeight(2.0, 2.0) == Approx(3130.4347826086955));
    REQUIRE(l_setup.getHeight(1.4, 1.4) == Approx(6956.521739130435));

    REQUIRE(l_setup.getBathymetry(0.0, 0.0) == Approx(-8000.0));
    REQUIRE(l_setup.getBathymetry(0.0, 4.0) == Approx(-521.7391304347826));
    REQUIRE(l_setup.getBathymetry(4.0, 0.0) == Approx(-7478.260869565216));
    REQUIRE(l_setup.getBathymetry(4.0, 4.0) == Approx(50));
    REQUIRE(l_setup.getBathymetry(2.0, 2.0) == Approx(-3134.43481));
    REQUIRE(l_setup.getBathymetry(1.4, 1.4) == Approx(-6959.52197));
}