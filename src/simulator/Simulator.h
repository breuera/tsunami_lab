/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Simulator class that runs all simulations.
 **/
#ifndef TSUNAMI_LAB_SIMULATOR_SIMULATOR
#define TSUNAMI_LAB_SIMULATOR_SIMULATOR

#include <cstdlib>
#include <string>

#include "../configs/SimConfig.h"
#include "../constants.h"
#include "../setups/Setup.h"

namespace tsunami_lab {
    class simulator;
}

class tsunami_lab::simulator {
   public:
    static void runSimulation(tsunami_lab::setups::Setup *i_setup,
                              tsunami_lab::t_real i_hStar,
                              tsunami_lab::configs::SimConfig i_simConfig);
};

#endif