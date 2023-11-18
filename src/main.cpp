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
#include "io/Json/ConfigLoader.h"
#include "simulator/Simulator.h"

int main() {
    std::cout << "####################################" << std::endl;
    std::cout << "### Tsunami Lab                  ###" << std::endl;
    std::cout << "###                              ###" << std::endl;
    std::cout << "### https://scalable.uni-jena.de ###" << std::endl;
    std::cout << "####################################" << std::endl;

    tsunami_lab::setups::Setup *l_setups = nullptr;
    tsunami_lab::t_real l_hStar = -1;
    tsunami_lab::configs::SimConfig l_simConfig = tsunami_lab::configs::SimConfig();

    std::string l_path = "./res/tsunami_config.json";

    // load parameters from runtimeConfig.json
    tsunami_lab::t_idx err = tsunami_lab::io::ConfigLoader::loadConfig(l_path,
                                                                       l_setups,
                                                                       l_hStar,
                                                                       l_simConfig);

    if (err == 0) {
        std::cout << "failed to read: " << l_path << std::endl;
        return EXIT_FAILURE;
    }

    // start simulation from config
    tsunami_lab::simulator::runSimulation(l_setups, l_hStar, l_simConfig);

    std::cout << "finished, exiting" << std::endl;
    return EXIT_SUCCESS;
}
