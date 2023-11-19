/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Unit tests for the two-dimensional wave propagation patch.
 **/

#include "WavePropagation2d.h"

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("Test the 2d wave propagation solver.", "[WaveProp2d]") {
    /*
     * Test case:
     *   Given a 2d field of cells.
     *
     *   Single dam break problem between the 49. and 50. cell in each row.
     *     left | right
     *       10 | 8
     *        0 | 0
     *        0 | 0
     *
     *   Elsewhere steady state.
     *
     * The net-updates at the respective edge are given as
     * (see derivation in f-wave solver):
     *    left             | right
     *     9.39475         | -9.39475
     *    -88.25991835     | -88.25991835
     */

    // construct solver (F_Wave) and setup a dambreak problem
    tsunami_lab::patches::WavePropagation2d l_waveProp(10, 10);

    for (std::size_t l_ceY = 0; l_ceY < 10; l_ceY++) {
        for (std::size_t l_ceX = 0; l_ceX < 5; l_ceX++) {
            l_waveProp.setHeight(l_ceX,
                                 l_ceY,
                                 10);
            l_waveProp.setMomentumX(l_ceX,
                                    l_ceY,
                                    0);
            l_waveProp.setMomentumY(l_ceX,
                                    l_ceY,
                                    0);
        }

        for (std::size_t l_ceX = 5; l_ceX < 10; l_ceX++) {
            l_waveProp.setHeight(l_ceX,
                                 l_ceY,
                                 8);
            l_waveProp.setMomentumX(l_ceX,
                                    l_ceY,
                                    0);
            l_waveProp.setMomentumY(l_ceX,
                                    l_ceY,
                                    0);
        }
    }

    // set outflow boundary condition
    l_waveProp.setGhostCells("OO");

    // perform a time step
    l_waveProp.timeStep(0.1, 0.1);

    for (std::size_t l_ceY = 1; l_ceY < 11; l_ceY++) {
        // steady state
        for (std::size_t l_ceX = 1; l_ceX < 5; l_ceX++) {
            REQUIRE(l_waveProp.getHeight()[l_ceY * 12 + l_ceX] == Approx(10));
            REQUIRE(l_waveProp.getMomentumX()[l_ceY * 12 + l_ceX] == Approx(0));
            REQUIRE(l_waveProp.getMomentumY()[l_ceY * 12 + l_ceX] == Approx(0));
        }

        // dam-break
        REQUIRE(l_waveProp.getHeight()[l_ceY * 12 + 5] == Approx(10 - 0.1 * 9.394671362));
        REQUIRE(l_waveProp.getMomentumX()[l_ceY * 12 + 5] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(l_waveProp.getMomentumY()[l_ceY * 12 + 5] == Approx(0));

        REQUIRE(l_waveProp.getHeight()[l_ceY * 12 + 6] == Approx(8 + 0.1 * 9.394671362));
        REQUIRE(l_waveProp.getMomentumX()[l_ceY * 12 + 6] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(l_waveProp.getMomentumY()[l_ceY * 12 + 6] == Approx(0));

        // steady state
        for (std::size_t l_ceX = 7; l_ceX < 11; l_ceX++) {
            REQUIRE(l_waveProp.getHeight()[l_ceY * 12 + l_ceX] == Approx(8));
            REQUIRE(l_waveProp.getMomentumX()[l_ceY * 12 + l_ceX] == Approx(0));
            REQUIRE(l_waveProp.getMomentumY()[l_ceY * 12 + l_ceX] == Approx(0));
        }
    }
}