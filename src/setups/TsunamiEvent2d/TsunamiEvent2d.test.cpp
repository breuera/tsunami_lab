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
    tsunami_lab::t_idx l_bathymetryDimX = 5;
    tsunami_lab::t_idx l_bathymetryDimY = 5;
    tsunami_lab::t_real l_bathymetryPosX[5] = {-3.0, -2.0, -1.0, -0.5, -0.1};
    tsunami_lab::t_real *l_bathymetryPosX_ptr = new tsunami_lab::t_real[5];
    tsunami_lab::t_real l_bathymetryPosY[5] = {-3.0, -2.0, -1.0, -0.5, -0.1};
    tsunami_lab::t_real *l_bathymetryPosY_ptr = new tsunami_lab::t_real[5];
    for (tsunami_lab::t_idx l_i = 0; l_i < 5; l_i++) {
        l_bathymetryPosX_ptr[l_i] = l_bathymetryPosX[l_i];
        l_bathymetryPosY_ptr[l_i] = l_bathymetryPosY[l_i];
    }
    tsunami_lab::t_real l_bathymetry[25] = {-8000.0, -7826.086956521738, -7652.173913043477, -7478.260869565216, -7304.3478260869565,
                                            -7130.434782608695, -6956.521739130435, -6782.608695652175, -6608.695652173914, -6434.782608695653,
                                            -6260.869565217391, -6086.95652173913, -5913.0434782608695, -5739.130434782609, -5565.217391304348,
                                            -3478.2608695652175, -3304.3478260869565, -3130.4347826086955, -2956.521739130435, -2782.608695652174,
                                            -521.7391304347826, -347.82608695652175, -173.91304347826087, 0.0, 50.0};
    tsunami_lab::t_real *l_bathymetry_ptr = new tsunami_lab::t_real[25];
    for (tsunami_lab::t_idx l_i = 0; l_i < 25; l_i++) {
        l_bathymetry_ptr[l_i] = l_bathymetry[l_i];
    }
    tsunami_lab::t_idx l_displacementsDimX = 2;
    tsunami_lab::t_idx l_displacementsDimY = 2;
    tsunami_lab::t_real l_displacementsPosX[2] = {-1.6, -0};
    tsunami_lab::t_real *l_displacementsPosX_ptr = new tsunami_lab::t_real[2];
    tsunami_lab::t_real l_displacementsPosY[2] = {-1.25, -0.25};
    tsunami_lab::t_real *l_displacementsPosY_ptr = new tsunami_lab::t_real[2];
    for (tsunami_lab::t_idx l_i = 0; l_i < 2; l_i++) {
        l_displacementsPosX_ptr[l_i] = l_displacementsPosX[l_i];
        l_displacementsPosY_ptr[l_i] = l_displacementsPosY[l_i];
    }
    tsunami_lab::t_real l_displacements[4] = {-3.0, -2.0, -1.0, 0.0};
    tsunami_lab::t_real *l_displacements_ptr = new tsunami_lab::t_real[4];
    for (tsunami_lab::t_idx l_i = 0; l_i < 4; l_i++) {
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
    std::cout << "bathymetry values: " << std::endl;

    for (tsunami_lab::t_real l_ceY = 0; l_ceY < 5; l_ceY += 0.5) {
        for (tsunami_lab::t_real l_ceX = 0; l_ceX < 5; l_ceX += 0.5) {
            // tsunami_lab::t_real l_height_val = l_setup.getHeight(l_ceX, l_ceY);
            // tsunami_lab::t_real l_bathymetry_val = l_setup.getBathymetry(l_ceX, l_ceY);
            tsunami_lab::t_real l_momentumX_val = l_setup.getMomentumX(l_ceX, l_ceY);
            tsunami_lab::t_real l_momentumY_val = l_setup.getMomentumY(l_ceX, l_ceY);

            REQUIRE(l_momentumX_val == 0);
            REQUIRE(l_momentumY_val == 0);

            // tsunami_lab::t_real l_offsetCeX = l_ceX + l_epicenterOffsetX;
            // tsunami_lab::t_real l_offsetCeY = l_ceY + l_epicenterOffsetY;
        }
        std::cout << "new line" << std::endl;
    }
}