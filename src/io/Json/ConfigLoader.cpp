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
#include "../../io/NetCDF/NetCDF.h"

// include setup classes
#include "../../setups/ArtificialTsunami2d/ArtificialTsunami2d.h"
#include "../../setups/CheckPoint/CheckPoint.h"
#include "../../setups/CustomSetup1d/CustomSetup1d.h"
#include "../../setups/DamBreak1d/DamBreak1d.h"
#include "../../setups/DamBreak2d/DamBreak2d.h"
#include "../../setups/RareRare1d/RareRare1d.h"
#include "../../setups/ShockShock1d/ShockShock1d.h"
#include "../../setups/SubcriticalFlow1d/SubcriticalFlow1d.h"
#include "../../setups/SupercriticalFlow1d/SupercriticalFlow1d.h"
#include "../../setups/TsunamiEvent1d/TsunamiEvent1d.h"
#include "../../setups/TsunamiEvent2d/TsunamiEvent2d.h"
using json = nlohmann::json;

tsunami_lab::t_idx tsunami_lab::io::ConfigLoader::loadConfig(std::string i_configName,
                                                             bool i_useCheckpoint,
                                                             tsunami_lab::setups::Setup *&o_setup,
                                                             tsunami_lab::t_real &o_hStar,
                                                             tsunami_lab::configs::SimConfig &o_simConfig) {
    std::string l_path = "./res/configs/" + i_configName;

    std::ifstream l_file(l_path);
    if (l_file.fail()) {
        std::cerr << "failed to read " << l_path << std::endl;
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

    // offset of the epicenter to the 0-point in x-direction
    tsunami_lab::t_real l_epicenterOffsetX;
    if (l_configFile.contains("epicenterOffsetX")) {
        l_epicenterOffsetX = l_configFile.at("epicenterOffsetX");
    } else {
        std::cout << "epicenterOffsetX takes on default value" << std::endl;
        l_epicenterOffsetX = -(l_xLen / 2);
    }

    // offset of the epicenter to the 0-point in x-direction
    tsunami_lab::t_real l_epicenterOffsetY;
    if (l_configFile.contains("epicenterOffsetY")) {
        l_epicenterOffsetY = l_configFile.at("epicenterOffsetY");
    } else {
        std::cout << "epicenterOffsetY takes on default value" << std::endl;
        l_epicenterOffsetY = -(l_yLen / 2);
    }

    // set time of simulation
    tsunami_lab::t_real l_endSimTime;
    if (l_configFile.contains("simTime")) {
        l_endSimTime = l_configFile.at("simTime");
    } else {
        std::cout << "simTime takes on default value" << std::endl;
        l_endSimTime = 1.25;
    }

    // set start time of simulation
    tsunami_lab::t_real l_startSimTime = 0;

    // set boundary condition
    e_boundary l_boundaryCond[4] = {OUTFLOW, OUTFLOW, OUTFLOW, OUTFLOW};
    if (l_configFile.contains("boundaryCond")) {
        std::string l_boundary = l_configFile.at("boundaryCond");
        for (t_idx l_i = 0; l_i < l_boundary.length(); l_i++) {
            if (l_boundary[l_i] == 'R') {
                l_boundaryCond[l_i] = REFLECTING;
            } else {
                l_boundaryCond[l_i] = OUTFLOW;
            }
        }
    } else {
        std::cout << "boundaryCond takes on default value" << std::endl;
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

    // factor for coarse output
    tsunami_lab::t_idx l_coarseFactor;
    if (l_configFile.contains("coarseFactor")) {
        l_coarseFactor = l_configFile.at("coarseFactor");

        if (l_coarseFactor < 1) {
            std::cout << "factor for coarse input can't be smaller than 1" << std::endl;
            return 0;
        }
    } else {
        std::cout << "coarseFactor takes on default value" << std::endl;
        l_coarseFactor = 1;
    }

    // set bathymetry and displacements file names
    std::string l_bathymetryFileName, l_displacementsFileName;
    if (l_configFile.contains("bathymetryFileName")) {
        l_bathymetryFileName = l_configFile.at("bathymetryFileName");
    } else {
        std::cout << "bathymetryFileName takes on default value" << std::endl;
        l_bathymetryFileName = "dummy_bathymetry.nc";
    }

    if (l_configFile.contains("displacementsFileName")) {
        l_displacementsFileName = l_configFile.at("displacementsFileName");
    } else {
        std::cout << "displacementsFileName takes on default value" << std::endl;
        l_displacementsFileName = "dummy_disp.nc";
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

    // check if checkpoint exists
    std::string l_configName = i_configName.substr(0, i_configName.find_last_of("."));
    std::string l_checkPointPath = "out/" + l_configName + "_checkpoint.nc";
    std::ifstream f(l_checkPointPath.c_str());
    t_idx l_startFrame = 0;
    if (i_useCheckpoint && f.good()) {
        std::cout << "Reading out/" + l_configName + "_checkpoint.nc" << std::endl;
        t_real *l_height;
        t_real *l_momentumX;
        t_real *l_momentumY;
        t_real *l_bathymetry;
        t_real *l_time;
        t_real l_endSimTime;
        tsunami_lab::io::NetCDF::readCheckpoint(l_checkPointPath,
                                                l_height,
                                                l_momentumX,
                                                l_momentumY,
                                                l_bathymetry,
                                                l_time,
                                                &l_startFrame,
                                                &l_endSimTime,
                                                &l_startSimTime);

        o_setup = new tsunami_lab::setups::CheckPoint(l_xLen,
                                                      l_yLen,
                                                      l_nx,
                                                      l_ny,
                                                      l_startFrame,
                                                      l_height,
                                                      l_momentumX,
                                                      l_momentumY,
                                                      l_bathymetry,
                                                      l_time);
    } else if (l_setupName.compare("DamBreak") == 0) {
        if (l_dimension == 1) {
            o_setup = new tsunami_lab::setups::DamBreak1d(10, 5, 5);
        } else {
            o_setup = new tsunami_lab::setups::DamBreak2d(10, 5, l_xLen, l_yLen, 10);
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
    } else if (l_setupName.compare("ArtificialTsunamiEvent") == 0) {
        if (l_dimension == 2) {
            o_setup = new tsunami_lab::setups::ArtificialTsunami2d(l_xLen, l_yLen);
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
            o_setup = new tsunami_lab::setups::TsunamiEvent1d(l_bathymetry);

            delete[] l_distance;
            delete[] l_x;
            delete[] l_y;
        } else if (l_dimension == 2) {
            tsunami_lab::t_idx l_bathymetryDimX, l_bathymetryDimY, l_dispDimX, l_dispDimY;
            tsunami_lab::t_real *l_bathymetry;
            tsunami_lab::t_real *l_bathymetryPosX;
            tsunami_lab::t_real *l_bathymetryPosY;
            tsunami_lab::t_real *l_displacements;
            tsunami_lab::t_real *l_dispPosX;
            tsunami_lab::t_real *l_dispPosY;

            int l_err = tsunami_lab::io::NetCDF::read(l_bathymetryFileName,
                                                      l_displacementsFileName,
                                                      &l_bathymetryDimX,
                                                      &l_bathymetryDimY,
                                                      l_bathymetryPosX,
                                                      l_bathymetryPosY,
                                                      l_bathymetry,
                                                      &l_dispDimX,
                                                      &l_dispDimY,
                                                      l_dispPosX,
                                                      l_dispPosY,
                                                      l_displacements);

            if (l_err != 0) {
                std::cout << "Failed to read the betCDF files" << std::endl;
                return EXIT_FAILURE;
            }

            o_setup = new tsunami_lab::setups::TsunamiEvent2d(l_xLen,
                                                              l_yLen,
                                                              l_bathymetryDimX,
                                                              l_bathymetryDimY,
                                                              l_bathymetryPosX,
                                                              l_bathymetryPosY,
                                                              l_bathymetry,
                                                              l_dispDimX,
                                                              l_dispDimY,
                                                              l_dispPosX,
                                                              l_dispPosY,
                                                              l_displacements,
                                                              l_epicenterOffsetX,
                                                              l_epicenterOffsetY);
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

            o_setup = new tsunami_lab::setups::CustomSetup1d(l_hL[l_idx], l_hR[l_idx], l_huL[l_idx], l_huR[l_idx], 5.0);
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
                                                  l_configName,
																  i_useCheckpoint,
                                                  l_nx,
                                                  l_ny,
                                                  l_xLen,
                                                  l_yLen,
                                                  l_endSimTime,
                                                  l_startSimTime,
                                                  l_startFrame,
																  l_coarseFactor,
                                                  l_boundaryCond,
                                                  l_useRoeSolver);
    return 1;
}