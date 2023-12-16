/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Class loading the config.json file and initializing the simulation.
 **/

#ifndef TSUNAMI_LAB_IO_CONFIG_LOADER
#define TSUNAMI_LAB_IO_CONFIG_LOADER

#include <string>

#include "../../configs/SimConfig.h"
#include "../../constants.h"
#include "../../setups/Setup.h"

namespace tsunami_lab {
    namespace io {
        class ConfigLoader;
    }
}  // namespace tsunami_lab

class tsunami_lab::io::ConfigLoader {
   public:
    static tsunami_lab::t_idx loadConfig(std::string i_path,
                                         bool i_useCheckpoint,
                                         tsunami_lab::setups::Setup *&i_setup,
                                         tsunami_lab::t_real &i_hStar,
                                         tsunami_lab::configs::SimConfig &i_simConfig);
};

#endif
