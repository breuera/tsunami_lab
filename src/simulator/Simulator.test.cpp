/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Unit-tests for Simulator.
 **/
#include <catch2/catch.hpp>
#include <iostream>

#include "../constants.h"
#include "../setups/DamBreak1d/DamBreak1d.h"
#define private public
#include "Simulator.h"
#undef public

TEST_CASE("Test the simulation running method.", "[Simulator]") {
    std::cout << "starting simulation running test" << std::endl;
    tsunami_lab::configs::SimConfig l_config = tsunami_lab::configs::SimConfig(1,
                                                                               50,
                                                                               1,
                                                                               10,
                                                                               1,
                                                                               5,
                                                                               1,
                                                                               1.25,
                                                                               "-oo",
                                                                               1,
                                                                               false);
    tsunami_lab::setups::Setup *l_setup = new tsunami_lab::setups::DamBreak1d(10, 5, 5);

    tsunami_lab::simulator::runSimulation(l_setup, -1, l_config);

    delete l_setup;
}