/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Entry-point for simulations.
 **/
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>

#include "configs/SimConfig.h"
#include "io/Csv/Csv.h"
#include "patches/WavePropagation1d.h"
#include "setups/CustomSetup1d/CustomSetup1d.h"
#include "setups/DamBreak1d/DamBreak1d.h"
#include "setups/RareRare1d/RareRare1d.h"
#include "setups/ShockShock1d/ShockShock1d.h"
#include "setups/SubcriticalFlow1d/SubcriticalFlow1d.h"
#include "setups/SupercriticalFlow1d/SupercriticalFlow1d.h"
#include "setups/TsunamiEvent1d/TsunamiEvent1d.h"
#include "simulator/Simulator.h"

int main() {
    /*
// number of cells in x- and y-direction
tsunami_lab::t_idx l_nx = 0;
tsunami_lab::t_idx l_ny = 1;

// set cell size
tsunami_lab::t_real l_dxy = 1;

// set solver
bool l_use_roe_solver = false;
std::string l_scenario = "DamBreak";
std::string l_boundary_conditions = "-oo";*/

    std::cout << "####################################" << std::endl;
    std::cout << "### Tsunami Lab                  ###" << std::endl;
    std::cout << "###                              ###" << std::endl;
    std::cout << "### https://scalable.uni-jena.de ###" << std::endl;
    std::cout << "####################################" << std::endl;

    tsunami_lab::setups::Setup *l_setups = nullptr;
    tsunami_lab::t_real *l_hStar = nullptr;
    tsunami_lab::configs::SimConfig l_simConfig = tsunami_lab::configs::SimConfig();

    // load parameters from runtimeConfig.json
    // tsunami_lab::io::JsonParameterReader::loadConfig(l_setups, l_hStar, l_simConfig);

    // start simulation from config
    /*for (tsunami_lab::t_idx i = 0; i < l_simConfig.getSetupCount(); i++) {
        if (l_hStar != nullptr) {
            // run sanitization tests
            tsunami_lab::simulator::runSimulation(&l_setups[i], l_hStar[i], l_simConfig);
        } else {
            // run any other setup
            tsunami_lab::simulator::runSimulation(&l_setups[i], -1, l_simConfig);
        }
    }*/

    delete[] l_setups;
    if (l_hStar != nullptr) {
        delete[] l_hStar;
    } else {
        delete l_hStar;
    }

    std::cout << "finished, exiting" << std::endl;
    return EXIT_SUCCESS;

    /*if (i_argc == 3) {
        l_scenario = i_argv[1];
        l_nx = atoi(i_argv[2]);
        if (l_nx < 1) {
            std::cerr << "invalid number of cells" << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "solver defaults to f-wave solver" << std::endl;
        l_dxy = 25.0 / l_nx;
    } else if (i_argc == 4) {
        l_scenario = i_argv[1];
        l_nx = atoi(i_argv[2]);
        if (l_nx < 1) {
            std::cerr << "invalid number of cells" << std::endl;
            return EXIT_FAILURE;
        }
        l_dxy = 25.0 / l_nx;

        if (!(strcmp(i_argv[3], "-f") == 0 || strcmp(i_argv[3], "-r") == 0)) {
            std::cerr << "invalid third argument(needs to be '-r' or '-f')" << std::endl;
            return EXIT_FAILURE;
        }

        l_use_roe_solver = (strcmp(i_argv[3], "-r") == 0);
        if (l_use_roe_solver) {
            std::cout << "solver was set to the roe solver" << std::endl;
        } else {
            std::cout << "solver was set to the f-wave solver" << std::endl;
        }
    } else if (i_argc == 5) {
        l_scenario = i_argv[1];
        l_nx = atoi(i_argv[2]);
        if (l_nx < 1) {
            std::cerr << "invalid number of cells" << std::endl;
            return EXIT_FAILURE;
        }
        l_dxy = 440500 / l_nx;

        if (!(strcmp(i_argv[3], "-f") == 0 || strcmp(i_argv[3], "-r") == 0)) {
            std::cerr << "invalid third argument(needs to be '-r' or '-f')" << std::endl;
            return EXIT_FAILURE;
        }

        l_boundary_conditions = i_argv[4];
        if (!(strcmp(i_argv[4], "-oo") == 0 || strcmp(i_argv[4], "-rr") || strcmp(i_argv[4], "-or") || strcmp(i_argv[4], "-ro") == 0)) {
            std::cerr << "invalid fourth argument(needs to be '-rr', '-oo', '-or' or '-ro')" << std::endl;
            return EXIT_FAILURE;
        }
        if (strcmp(i_argv[4], "-rr") == 0) {
            std::cout << "Boundery condition of both ghost cells were set to reflecting condition" << std::endl;
        } else if (strcmp(i_argv[4], "-oo") == 0) {
            std::cout << "Boundery condition of both ghost cells were set to outflow condition" << std::endl;
        } else if (strcmp(i_argv[4], "-or") == 0) {
            std::cout << "Left boundery condition was set to outflow condition and right boundery condition to reflecting condition" << std::endl;
        } else if (strcmp(i_argv[4], "-ro") == 0) {
            std::cout << "Right boundery condition was set to outflow condition and left boundery condition to reflecting condition" << std::endl;
        }
        l_use_roe_solver = (strcmp(i_argv[3], "-r") == 0);
        if (l_use_roe_solver) {
            std::cout << "solver was set to the roe solver" << std::endl;
        } else {
            std::cout << "solver was set to the f-wave solver" << std::endl;
        }
    } else {
        std::cerr << "invalid number of arguments, usage:" << std::endl;
        std::cerr << "  ./build/tsunami_lab SCENARIO_MODE N_CELLS_X BOOL_USE_ROE_SOLVER" << std::endl;
        std::cerr << "where SCENARIO_MODE is the string, that decides the setup of the riemann problem. Options: DamBreak, Sanitize1d(test on middle states)" << std::endl;
        std::cerr << "where N_CELLS_X is the number of cells in x-direction." << std::endl;
        std::cerr << "where BOOL_USE_ROE_SOLVER is the flag, that decide, which solver is used. Use '-f' for f-wave or '-r' for roe" << std::endl;
        std::cerr << "BOOL_USE_ROE_SOLVER defaults to -f." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "runtime configuration" << std::endl;
    std::cout << "  number of cells in x-direction: " << l_nx << std::endl;
    std::cout << "  number of cells in y-direction: " << l_ny << std::endl;
    std::cout << "  cell size:                      " << l_dxy << std::endl;

    float *l_hL;
    float *l_huL;
    float *l_hR;
    float *l_huR;
    float *l_hStar;
    float *l_distance;
    float *l_bathymetry;
    float *l_x;
    float *l_y;

    tsunami_lab::t_idx l_scenarioCount = 0;
    tsunami_lab::t_real l_locMiddle = 220250;

    if (l_scenario == "DamBreak") {
        // initialize dam break scenario
        l_scenarioCount = 1;
        l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));

        l_hL[0] = 10;
        l_hR[0] = 5;
        l_huL[0] = 0;
        l_huR[0] = 0;
        l_hStar[0] = 0;
    } else if (l_scenario == "ShockShock") {
        // initialize dam break scenario
        l_scenarioCount = 1;
        l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));

        l_hL[0] = 10;
        l_hR[0] = 10;
        l_huL[0] = 18;
        l_huR[0] = 18;
        l_hStar[0] = 0;
    } else if (l_scenario == "RareRare") {
        l_scenarioCount = 1;
        l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));

        l_hL[0] = 10;
        l_hR[0] = 3;
        l_huL[0] = 0;
        l_huR[0] = 3;
        l_hStar[0] = 0;
    } else if (l_scenario == "CustomSetup") {
        l_scenarioCount = 1;
        l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));

        l_locMiddle = tsunami_lab::t_real(0.004);
        l_hL[0] = tsunami_lab::t_real(10);
        l_hR[0] = tsunami_lab::t_real(10);
        l_huL[0] = 10;
        l_huR[0] = 10;
        l_hStar[0] = 0;
    } else if (l_scenario == "Sanitize1d") {
        // initialize middle state sanitization
        l_scenarioCount = 1000000;

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
            l_scenarioCount = 10;
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
    } else if (l_scenario == "TsunamiEvent1d") {
        // initialize middle state sanitization
        l_scenarioCount = 100000;
        std::string filePath = "./res/dem.csv";

        std::ifstream l_stream;
        // try to read middle states original file
        std::cout << "reading /res/dem.csv ..." << std::endl;
        l_stream.open(filePath, std::fstream::in);

        if (l_stream.fail()) {
            std::cout << "failed to read /res/dem.csv" << std::endl;
            l_stream.clear();

            // try to read dummy middle states file
            std::cout << "reading /res/dummy_middle_states.csv ..." << std::endl;
            l_stream.open("./res/dummy_middle_states.csv", std::fstream::in);
            l_scenarioCount = 10;
            if (l_stream.fail()) {
                std::cerr << "failed to read /res/dummy_middle_states.csv" << std::endl;
                return EXIT_FAILURE;
            }
            std::cout << "finished reading /res/dummy_middle_states.csv" << std::endl;
        } else {
            std::cout << "finished reading /res/dem.csv" << std::endl;
        }

        l_distance = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
        l_bathymetry = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
        l_x = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
        l_y = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));

        tsunami_lab::io::Csv::read_gmt_states(l_stream,
                                              l_bathymetry,
                                              l_x,
                                              l_y,
                                              l_distance);
    } else if (l_scenario == "SubcriticalFlow1d") {
        // initialize subcritical flow scenario
        l_scenarioCount = 1;
        l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));

        l_hL[0] = 0;
        l_hR[0] = 0;
        l_huL[0] = tsunami_lab::t_real(4.42);
        l_huR[0] = tsunami_lab::t_real(4.42);
        l_hStar[0] = 0;
    } else if (l_scenario == "SupercriticalFlow1d") {
        l_scenarioCount = 1;
        l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));
        l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(tsunami_lab::t_real));

        l_hL[0] = 0;
        l_hR[0] = 0;
        l_huL[0] = tsunami_lab::t_real(0.18);
        l_huR[0] = tsunami_lab::t_real(0.18);
        l_hStar[0] = 0;
    } else {
        std::cerr << "entered SCENARIO_MODE is unknown" << std::endl;
        return EXIT_FAILURE;
    }

    for (tsunami_lab::t_idx l_idx = 0; l_idx < l_scenarioCount; l_idx++) {
        std::cout << "enter scenario: " << l_idx << std::endl;
        tsunami_lab::setups::Setup *l_setup;
        if (l_scenario == "DamBreak") {
            l_setup = new tsunami_lab::setups::DamBreak1d(l_hL[l_idx],
                                                          l_hR[l_idx],
                                                          l_locMiddle);
        } else if (l_scenario == "ShockShock") {
            l_setup = new tsunami_lab::setups::ShockShock1d(l_hL[l_idx],
                                                            l_huL[l_idx],
                                                            l_locMiddle);
        } else if (l_scenario == "RareRare") {
            l_setup = new tsunami_lab::setups::RareRare1d(l_hR[l_idx],
                                                          l_huR[l_idx],
                                                          l_locMiddle);
        } else if (l_scenario == "CustomSetup") {
            l_setup = new tsunami_lab::setups::CustomSetup1d(l_hL[l_idx],
                                                             l_hR[l_idx],
                                                             l_huL[l_idx],
                                                             l_huR[l_idx],
                                                             l_locMiddle);
        } else if (l_scenario == "Sanitize1d") {
            l_setup = new tsunami_lab::setups::CustomSetup1d(l_hL[l_idx],
                                                             l_hR[l_idx],
                                                             l_huL[l_idx],
                                                             l_huR[l_idx],
                                                             l_locMiddle);
        } else if (l_scenario == "TsunamiEvent1d") {
            l_setup = new tsunami_lab::setups::TsunamiEvent1d(l_bathymetry);
        } else if (l_scenario == "SubcriticalFlow1d") {
            l_setup = new tsunami_lab::setups::SubcriticalFlow1d(tsunami_lab::t_real(4.42));
        } else if (l_scenario == "SupercriticalFlow1d") {
            l_setup = new tsunami_lab::setups::SupercriticalFlow1d(tsunami_lab::t_real(0.18));
        } else {
            std::cerr << "entered SCENARIO_MODE is unknown" << std::endl;
            return EXIT_FAILURE;
        }
    }
    // free memory off scenario data

    free(l_hL);
    free(l_huL);
    free(l_hR);
    free(l_huR);
    free(l_hStar);
*/
}
