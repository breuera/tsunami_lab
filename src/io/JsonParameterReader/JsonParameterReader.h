/**
 * @author Bohdan Babii
 *
 * @section DESCRIPTION
 * IO-routine for reading config parameters.
 **/
#ifndef JSON_PARAMETER_READER_H
#define JSON_PARAMETER_READER_H

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "../../configs/SimConfig.h"
#include "../../constants.h"

namespace tsunami_lab {
    namespace io {
        class JsonParameterReader;
    }
}  // namespace tsunami_lab

class tsunami_lab::io::JsonParameterReader {
   private:
    tsunami_lab::t_real *m_setups;
    tsunami_lab::t_real *m_hstar;
    tsunami_lab::configs::SimConfig *m_simConfig;

   public:
    const std::string i_filename;
    /**
     * Reads the configurations from the config.json.
     *
     * @param i_filename directory of the config.json file.
     * @param i_setups array for different setups.
     * @param i_hStar middle states from file middle states.
     * @param i_SimConfig pointer on the SimConfig object.
     **/
    std::unordered_map<std::string, std::string> readParameters(tsunami_lab::t_real *i_setups,
                                                                tsunami_lab::t_real *i_hstar,
                                                                tsunami_lab::configs::SimConfig *i_simConfig);
};

#endif  // JSON_PARAMETER_READER_H
