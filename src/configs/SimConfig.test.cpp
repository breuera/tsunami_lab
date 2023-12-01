/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Unit-tests for SimConfig object.
 **/
#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>

#include "../constants.h"
#define private public
#include "SimConfig.h"
#undef public

TEST_CASE("Test the SimConfig data-structure.", "[SimConfig]") {
    tsunami_lab::t_idx l_dimension = 2;
    tsunami_lab::t_idx l_nx = 575;
    tsunami_lab::t_idx l_ny = 540;
    tsunami_lab::t_real l_xLen = tsunami_lab::t_real(1200);
    tsunami_lab::t_real l_yLen = tsunami_lab::t_real(2400);
    tsunami_lab::t_real l_simTime = tsunami_lab::t_real(200.0);
    tsunami_lab::e_boundary l_boundaryCondition[2] = {tsunami_lab::OUTFLOW, tsunami_lab::REFLECTING};
    bool l_isRoeSolver = true;

    tsunami_lab::configs::SimConfig l_config = tsunami_lab::configs::SimConfig(l_dimension,
                                                                               l_nx,
                                                                               l_ny,
                                                                               l_xLen,
                                                                               l_yLen,
                                                                               l_simTime,
                                                                               l_boundaryCondition,
                                                                               l_isRoeSolver);

    REQUIRE(l_dimension == l_config.getDimension());
    REQUIRE(l_nx == l_config.getXCells());
    REQUIRE(l_ny == l_config.getYCells());
    REQUIRE(l_xLen == l_config.getXLength());
    REQUIRE(l_yLen == l_config.getYLength());
    REQUIRE(l_simTime == l_config.getSimTime());
    REQUIRE(l_boundaryCondition == l_config.getBoundaryCondition());
    REQUIRE(l_isRoeSolver == l_config.isRoeSolver());
}