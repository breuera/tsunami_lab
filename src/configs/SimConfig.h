/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Configuration that holds all information for one simulation.
 **/
#ifndef TSUNAMI_LAB_CONFIGS_SIM_CONFIG
#define TSUNAMI_LAB_CONFIGS_SIM_CONFIG

#include <cstdlib>
#include <string>

#include "../constants.h"

namespace tsunami_lab {
    namespace configs {
        class SimConfig;
    }
}  // namespace tsunami_lab

class tsunami_lab::configs::SimConfig {
   private:
    //! dimension of the simulation.
    tsunami_lab::t_idx m_dimension = 1;

    //! number of cells in x-direction
    tsunami_lab::t_idx m_nx = 1;

    //! number of cells in y-direction
    tsunami_lab::t_idx m_ny = 1;

    //! length of the simulation in x-direction
    tsunami_lab::t_real m_xLen = tsunami_lab::t_real(10.0);

    //! length of the simulation in y-direction
    tsunami_lab::t_real m_yLen = tsunami_lab::t_real(10.0);

    //! location of the middle location in x-direction (where for example the dam is located)
    tsunami_lab::t_real m_thresholdX = tsunami_lab::t_real(5.0);

    //! location of the middle location in y-direction (where for example the dam is located)
    tsunami_lab::t_real m_thresholdY = tsunami_lab::t_real(5.0);

    //! time of the simulation.
    tsunami_lab::t_real m_simTime = tsunami_lab::t_real(1.25);

    //! list of which boundary condition to use.
    e_boundary *m_boundaryCondition;

    //! boolean that shows if the Roe Solver is to be used.
    bool m_isRoeSolver = false;

   public:
    /**
     * Default constructor;
     */
    SimConfig();

    /**
     * Constructs a simulation configuration object.
     *
     * @param i_dimension dimension of the simulation.
     * @param i_nx number of cells in x-direction.
     * @param i_ny number of cells in y-direction.
     * @param i_xLen length of the simulation in x-direction in meters.
     * @param i_yLen length of the simulation in y-direction in meters.
     * @param i_thresholdX position of the point in x-direction, where the conditions change.
     * @param i_thresholdY position of the point in y-direction, where the conditions change.
     * @param i_simTime time of the simulation in seconds.
     * @param i_boundaryCondition list that determines the chosen boundary conditions.
     * @param i_isRoeSolver boolean that shows if the roe solver is to be used (false -> f-wave solver).
     */
    SimConfig(tsunami_lab::t_idx i_dimension,
              tsunami_lab::t_idx i_nx,
              tsunami_lab::t_idx i_ny,
              tsunami_lab::t_real i_xLen,
              tsunami_lab::t_real i_yLen,
              tsunami_lab::t_real i_thresholdX,
              tsunami_lab::t_real i_thresholdY,
              tsunami_lab::t_real i_simTime,
              e_boundary *i_boundaryCondition,
              bool i_isRoeSolver);
    /**
     * Destructor which frees all allocated memory.
     **/
    ~SimConfig();

    /**
     * Gets dimension of the simulation.
     *
     * @return dimension of the simulation.
     */
    tsunami_lab::t_idx getDimension() {
        return m_dimension;
    }

    /**
     * Gets number of cells in x-direction.
     *
     * @return number of cells in x-direction.
     */
    tsunami_lab::t_idx getXCells() {
        return m_nx;
    }

    /**
     * Gets number of cells in y-direction.
     *
     * @return number of cells in y-direction.
     */
    tsunami_lab::t_idx getYCells() {
        return m_ny;
    }

    /**
     * Gets length of simulation in x-direction in meters.
     *
     * @return length of simulation in x-direction in meters.
     */
    tsunami_lab::t_real getXLength() {
        return m_xLen;
    }

    /**
     * Gets length of simulation in y-direction in meters.
     *
     * @return length of simulation in y-direction in meters.
     */
    tsunami_lab::t_real getYLength() {
        return m_yLen;
    }

    /**
     * Gets the threshold in x-direction.
     *
     * @return threshold.
     */
    tsunami_lab::t_real getThresholdX() {
        return m_thresholdX;
    }

    /**
     * Gets the threshold in y-direction.
     *
     * @return threshold.
     */
    tsunami_lab::t_real getThresholdY() {
        return m_thresholdY;
    }

    /**
     * Gets the time length of the simulation in seconds.
     *
     * @return time length of the simulation in seconds.
     */
    tsunami_lab::t_real getSimTime() {
        return m_simTime;
    }

    /**
     * Gets list holding the boundary conditions.
     *
     * @return list holding the boundary conditions.
     */
    e_boundary *getBoundaryCondition() {
        return m_boundaryCondition;
    }

    /**
     * Gets boolean value, that shows if the roe solver is to be used.
     *
     * @return number of setups to be calculated.
     */
    bool isRoeSolver() {
        return m_isRoeSolver;
    }
};

#endif