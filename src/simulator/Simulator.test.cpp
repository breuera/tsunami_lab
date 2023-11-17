/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Unit-tests for Simulator.
 **/
#include <catch2/catch.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

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

    std::ifstream l_file;
    l_file.open("./out/solution_4.csv");

    REQUIRE(!l_file.fail());
    std::string l_line;
    tsunami_lab::t_real l_xPos = 0;
    tsunami_lab::t_real l_height;
    std::stringstream l_lineStream;

    // skip header
    std::getline(l_file, l_line);

    while (l_xPos < 5) {
        std::getline(l_file, l_line);
        l_lineStream << l_line;
        std::string l_cell;
        std::getline(l_lineStream, l_cell, ',');
        l_xPos = std::stof(l_cell);

        // skip y
        std::getline(l_lineStream, l_cell, ',');
        std::getline(l_lineStream, l_cell, ',');
        l_height = std::stof(l_cell);

        // skip momentumX, bathymetry and final_height
        std::getline(l_lineStream, l_cell, ',');
        std::getline(l_lineStream, l_cell, ',');
        std::getline(l_lineStream, l_cell, ',');

        l_lineStream.clear();
    }

    // delete output files
    bool l_deletedAll = true;

    for (tsunami_lab::t_idx l_idx = 0; l_idx < 5; l_idx++) {
        std::string path = "./out/solution_" + std::to_string(l_idx) + ".csv";
        tsunami_lab::t_idx err = remove(path.c_str());
        if (err == -1) l_deletedAll = false;
    }
    REQUIRE(l_deletedAll);

    // check middle state
    REQUIRE(l_height == Approx(7.2627));
    delete l_setup;
}