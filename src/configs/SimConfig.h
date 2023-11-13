/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Configuration that holds all information for one simulation.
 **/
#ifndef TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_1D
#define TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_1D

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

    //! time of the simulation.
    tsunami_lab::t_real m_simTime = tsunami_lab::t_real(1.25);

    //! boolean that shows which boundary condition is to be used.
    std::string m_boundaryCondition = "-oo";

    //! number of setups to be simulated.
    tsunami_lab::t_idx m_setupCount = 0;

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
     * @param i_simTime time of the simulation in seconds.
     * @param i_boundaryCondition string that determents the chosen boundary conditions.
     * @param i_setupCount number of setups chosen.
     * @param i_isRoeSolver boolean that shows if the roe solver is to be used (false -> f-wave solver).
     */
    SimConfig(tsunami_lab::t_idx i_dimension,
              tsunami_lab::t_idx i_nx,
              tsunami_lab::t_idx i_ny,
              tsunami_lab::t_real i_xLen,
              tsunami_lab::t_real i_yLen,
              tsunami_lab::t_real i_simTime,
              std::string i_boundaryCondition,
              tsunami_lab::t_idx i_setupCount,
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
     * Gets the time length of the simulation in seconds.
     *
     * @return time length of the simulation in seconds.
     */
    tsunami_lab::t_real getSimTime() {
        return m_simTime;
    }

    /**
     * Gets string holding the boundary conditions.
     *
     * @return string holding the boundary conditions.
     */
    std::string getBoundaryCondition() {
        return m_boundaryCondition;
    }

    /**
     * Gets the number of setups to be calculated.
     *
     * @return number of setups to be calculated.
     */
    tsunami_lab::t_idx getSetupCount() {
        return m_setupCount;
    }

    bool isRoeSolver() {
        return m_isRoeSolver;
    }
};

#endif