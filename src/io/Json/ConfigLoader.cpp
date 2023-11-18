/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Class loading the config.json file and initializing the simulation.
 **/

#include "ConfigLoader.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>

#include "../../io/Csv/Csv.h"

// include setup classes
#include "../../setups/CustomSetup1d/CustomSetup1d.h"
#include "../../setups/DamBreak1d/DamBreak1d.h"
#include "../../setups/RareRare1d/RareRare1d.h"
#include "../../setups/ShockShock1d/ShockShock1d.h"
#include "../../setups/SubcriticalFlow1d/SubcriticalFlow1d.h"
#include "../../setups/SupercriticalFlow1d/SupercriticalFlow1d.h"
#include "../../setups/TsunamiEvent1d/TsunamiEvent1d.h"
using json = nlohmann::json;

tsunami_lab::t_idx tsunami_lab::io::ConfigLoader::loadConfig(std::string i_path,
                                                             tsunami_lab::setups::Setup *&o_setup,
                                                             tsunami_lab::t_real &o_hStar,
                                                             tsunami_lab::configs::SimConfig &o_simConfig) {
    std::ifstream l_file(i_path);
    if (l_file.fail()) {
        std::cerr << "failed to read " << i_path << std::endl;
        return 0;
    }

    // read JSON config file
    json l_configFile = json::parse(l_file);

    // set simulation dimension
    tsunami_lab::t_idx l_dimension;
    if (l_configFile.contains("dimension")) {
        l_dimension = l_configFile.at("dimension");
    } else {
        std::cout << "dimension takes on default value" << std::endl;
        l_dimension = 1;
    }

    // set number of cells in x-direction
    tsunami_lab::t_idx l_nx;
    if (l_configFile.contains("nx")) {
        l_nx = l_configFile.at("nx");
    } else {
        std::cout << "nx takes on default value" << std::endl;
        l_nx = 50;
    }

    // set number of cells in y-direction
    tsunami_lab::t_idx l_ny;
    if (l_configFile.contains("ny")) {
        l_ny = l_configFile.at("ny");
    } else {
        std::cout << "ny takes on default value" << std::endl;
        l_ny = 50;
    }

    // set length of simulation x-direction
    tsunami_lab::t_real l_xLen;
    if (l_configFile.contains("xLen")) {
        l_xLen = l_configFile.at("xLen");
    } else {
        std::cout << "xLen takes on default value" << std::endl;
        l_xLen = 10.0;
    }

    // set length of simulation y-direction
    tsunami_lab::t_real l_yLen;
    if (l_configFile.contains("yLen")) {
        l_yLen = l_configFile.at("yLen");
    } else {
        std::cout << "yLen takes on default value" << std::endl;
        l_yLen = 10.0;
    }

    // threshold of simulation x-direction
    tsunami_lab::t_real l_thresholdX;
    if (l_configFile.contains("thresholdX")) {
        l_thresholdX = l_configFile.at("thresholdX");
    } else {
        std::cout << "thresholdX takes on default value" << std::endl;
        l_thresholdX = l_xLen / 2;
    }

    // threshold of simulation y-direction
    tsunami_lab::t_real l_thresholdY;
    if (l_configFile.contains("thresholdY")) {
        l_thresholdY = l_configFile.at("thresholdY");
    } else {
        std::cout << "thresholdY takes on default value" << std::endl;
        l_thresholdY = l_yLen / 2;
    }

    // set time of simulation
    tsunami_lab::t_real l_simTime;
    if (l_configFile.contains("simTime")) {
        l_simTime = l_configFile.at("simTime");
    } else {
        std::cout << "simTime takes on default value" << std::endl;
        l_simTime = 1.25;
    }

    // set boundary condition
    std::string l_boundaryCond;
    if (l_configFile.contains("boundaryCond")) {
        l_boundaryCond = l_configFile.at("boundaryCond");
    } else {
        std::cout << "boundaryCond takes on default value" << std::endl;
        l_boundaryCond = "OO";
    }

    // set solver
    bool l_useRoeSolver;
    if (l_configFile.contains("solver")) {
        std::string solver = l_configFile.at("solver");
        if (solver.compare("Roe") == 0) {
            l_useRoeSolver = true;
        } else if (solver.compare("F-Wave") == 0) {
            l_useRoeSolver = false;
        } else {
            std::cout << "unknown solver was entered" << std::endl;
            return 0;
        }

    } else {
        std::cout << "solver takes on default value" << std::endl;
        l_useRoeSolver = false;
    }

    // set setup configuration
    std::string l_setupName;
    if (l_configFile.contains("setup")) {
        l_setupName = l_configFile.at("setup");
    } else {
        std::cout << "setup takes on default value" << std::endl;
        l_setupName = "DamBreak";
    }
    std::cout << "simulation setup was set to: " << l_setupName << std::endl;

    if (l_setupName.compare("DamBreak") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::DamBreak1d(10, 5, 5);
        }
    } else if (l_setupName.compare("RareRare") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::RareRare1d(10, 5, 5);
        }
    } else if (l_setupName.compare("ShockShock") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::ShockShock1d(10, 5, 5);
        }
    } else if (l_setupName.compare("SubcriticalFlow") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::SubcriticalFlow1d(4.42);
        }
    } else if (l_setupName.compare("SupercriticalFlow") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::SupercriticalFlow1d(0.13);
        }
    } else if (l_setupName.compare("CustomSetup") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::CustomSetup1d(10, 10, -5, -5, 5);
        }
    } else if (l_setupName.compare("TsunamiEvent") == 0) {
        if (l_dimension == 1) {
            // set bathymetry file path
            std::string l_filePath = "./res/dem.csv";
            tsunami_lab::t_idx l_sampleCount = 1763;

            std::ifstream l_stream;
            // try to read bathymetry file
            std::cout << "reading /res/dem.csv ..." << std::endl;
            l_stream.open(l_filePath, std::fstream::in);

            if (l_stream.fail()) {
                std::cout << "failed to read /res/dem.csv" << std::endl;
                return 0;
            } else {
                std::cout << "finished reading /res/dem.csv" << std::endl;
            }

            tsunami_lab::t_real *l_distance = new tsunami_lab::t_real[l_sampleCount];
            tsunami_lab::t_real *l_bathymetry = new tsunami_lab::t_real[l_sampleCount];
            tsunami_lab::t_real *l_x = new tsunami_lab::t_real[l_sampleCount];
            tsunami_lab::t_real *l_y = new tsunami_lab::t_real[l_sampleCount];

            tsunami_lab::io::Csv::read_gmt_states(l_stream,
                                                  l_bathymetry,
                                                  l_x,
                                                  l_y,
                                                  l_distance);
            std::cout << l_bathymetry[551] << std::endl;

            o_setup = new tsunami_lab::setups::TsunamiEvent1d(l_bathymetry);

            delete[] l_distance;
            // delete[] l_bathymetry;
            delete[] l_x;
            delete[] l_y;
        }
    } else if (l_setupName.compare("Sanitize") == 0) {
        if (l_dimension == 1) {
            // initialize middle state sanitization
            tsunami_lab::t_idx l_middleStateCount = 1000000;
            auto l_hL = new tsunami_lab::t_real[l_middleStateCount];
            auto l_hR = new tsunami_lab::t_real[l_middleStateCount];
            auto l_huL = new tsunami_lab::t_real[l_middleStateCount];
            auto l_huR = new tsunami_lab::t_real[l_middleStateCount];
            auto l_hStar = new tsunami_lab::t_real[l_middleStateCount];

            std::ifstream l_stream;
            // try to read middle states original file
            std::cout << "reading /res/middle_states.csv ..." << std::endl;
            l_stream.open("./res/middle_states.csv", std::fstream::in);

            if (l_stream.fail()) {
                std::cout << "failed to read /res/middle_states.csv" << std::endl;
                l_stream.clear();

                // try to read dummy middle states file
                std::cout << "reading /res/dummy_middle_states.csv ..." << std::endl;
                l_stream.open("./res/dummy_middle_states.csv", std::fstream::in);
                l_middleStateCount = 10;
                if (l_stream.fail()) {
                    std::cerr << "failed to read /res/dummy_middle_states.csv" << std::endl;
                    return EXIT_FAILURE;
                }
                std::cout << "finished reading /res/dummy_middle_states.csv" << std::endl;
            } else {
                std::cout << "finished reading /res/middle_states.csv" << std::endl;
            }

            tsunami_lab::io::Csv::read_middle_states(l_stream,
                                                     l_hL,
                                                     l_huL,
                                                     l_hR,
                                                     l_huR,
                                                     l_hStar);

            // choose random middle state
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(0, l_middleStateCount - 1);
            tsunami_lab::t_idx l_idx = distr(gen);

            o_setup = new tsunami_lab::setups::CustomSetup1d(l_hL[l_idx], l_hR[l_idx], l_huL[l_idx], l_huR[l_idx], l_thresholdX);
            o_hStar = l_hStar[l_idx];

            delete[] l_hL;
            delete[] l_hR;
            delete[] l_huL;
            delete[] l_huR;
            delete[] l_hStar;
        }
    } else {
        std::cout << "unknown setup was entered" << std::endl;
        return 0;
    }

    o_simConfig = tsunami_lab::configs::SimConfig(l_dimension,
                                                  l_nx,
                                                  l_ny,
                                                  l_xLen,
                                                  l_yLen,
                                                  l_thresholdX,
                                                  l_thresholdY,
                                                  l_simTime,
                                                  l_boundaryCond,
                                                  l_useRoeSolver);
    return 1;
}