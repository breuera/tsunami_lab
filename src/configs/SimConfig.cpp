/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Configuration that holds all information for one simulation.
 **/

#include "SimConfig.h"

tsunami_lab::configs::SimConfig::SimConfig() {
}

tsunami_lab::configs::SimConfig::SimConfig(tsunami_lab::t_idx i_dimension,
                                           tsunami_lab::t_idx i_nx,
                                           tsunami_lab::t_idx i_ny,
                                           tsunami_lab::t_real i_xLen,
                                           tsunami_lab::t_real i_yLen,
                                           tsunami_lab::t_real i_thresholdX,
                                           tsunami_lab::t_real i_thresholdY,
                                           tsunami_lab::t_real i_simTime,
                                           e_boundary *i_boundaryCondition,
                                           bool i_isRoeSolver) {
    m_dimension = i_dimension;
    m_nx = i_nx;
    m_ny = i_ny;
    m_xLen = i_xLen;
    m_yLen = i_yLen;
    m_thresholdX = i_thresholdX;
    m_thresholdY = i_thresholdY;
    m_simTime = i_simTime;
    m_boundaryCondition = i_boundaryCondition;
    m_isRoeSolver = i_isRoeSolver;
}

tsunami_lab::configs::SimConfig::~SimConfig() {}
