/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Test loading the config files.
 **/
#include <catch2/catch.hpp>

#define private public
#include "ConfigLoader.h"
#undef public

TEST_CASE("Test reading a config JSON file.", "[ConfigLoader]") {
    std::string l_path = "./res/configs/demo_config.json";
    tsunami_lab::setups::Setup *l_setups = nullptr;
    tsunami_lab::t_real l_hStar = -1;
    tsunami_lab::configs::SimConfig l_simConfig = tsunami_lab::configs::SimConfig();

    tsunami_lab::t_idx err;
    err = tsunami_lab::io::ConfigLoader::loadConfig(l_path,
                                                    l_setups,
                                                    l_hStar,
                                                    l_simConfig);

    REQUIRE(err == 1);
    REQUIRE(l_simConfig.getDimension() == 2);
    REQUIRE(l_simConfig.getXCells() == 500);
    REQUIRE(l_simConfig.getYCells() == 500);
    REQUIRE(l_simConfig.getXLength() == 100.0);
    REQUIRE(l_simConfig.getYLength() == 500.0);
    REQUIRE(l_simConfig.getSimTime() == 5.0);
    REQUIRE(l_simConfig.getBoundaryCondition().compare("OR") == 0);
    REQUIRE(l_simConfig.isRoeSolver());
    REQUIRE(l_hStar == -1);
}