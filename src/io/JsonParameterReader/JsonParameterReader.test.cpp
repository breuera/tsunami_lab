/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for the CSV-interface.
 **/
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>

#include "../../constants.h"
#define private public
#include "JsonParameterReader.h"
#undef public

TEST_CASE("Test the JsonParameterReader for reading the config file.", "[JsonParameterReader]") {
    tsunami_lab::io::JsonParameterReader jsonReader;
    tsunami_lab::t_real *i_setups = nullptr;
    tsunami_lab::t_real *i_hstar = nullptr;
    tsunami_lab::configs::SimConfig *i_simConfig = nullptr;

    std::unordered_map<std::string, std::string> parameters = jsonReader.readParameters(i_setups, i_hstar, i_simConfig);

    REQUIRE(stoi(parameters["l_nx"]) == 500);
    REQUIRE(stoi(parameters["l_ny"]) == 500);
}
