/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Two-dimensional dam break problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_DAM_BREAK_2D_H
#define TSUNAMI_LAB_SETUPS_DAM_BREAK_2D_H

#include "../Setup.h"

namespace tsunami_lab {
    namespace setups {
        class DamBreak2d;
    }
}  // namespace tsunami_lab

/**
 * 2d dam break setup.
 **/
class tsunami_lab::setups::DamBreak2d : public Setup {
   private:
    //! height inside of the circle
    t_real m_innerHeight = 0;

    //! height outside of the circle
    t_real m_outerHeight = 0;

    //! length of simulation in meters in x direction to put the dam in the middle
    t_real m_simLenX = 0;

    //! length of simulation in meters in y direction to put the dam in the middle
    t_real m_simLenY = 0;

    //! limit of the dam
    t_real m_damLimit = 0;

   public:
    /**
     * Constructor.
     *
     * @param i_innerHeight water height in the dam.
     * @param i_outerHeight water height outside of the dam.
     * @param i_simLenX length of simulation in x direction.
     * @param i_simLenY length of simulation in y direction.
     * @param i_damLimit limit of the dam.
     **/
    DamBreak2d(t_real i_innerHeight,
               t_real i_outerHeight,
               t_real i_simLenX,
               t_real i_simLenY,
               t_real i_damLimit);

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getHeight(t_real i_x,
                     t_real i_y) const;

    /**
     * Gets the momentum in x-direction.
     *
     * @return momentum in x-direction.
     **/
    t_real getMomentumX(t_real,
                        t_real) const;

    /**
     * Gets the momentum in y-direction.
     *
     * @return momentum in y-direction.
     **/
    t_real getMomentumY(t_real,
                        t_real) const;

    /**
     * Gets the bathymetry at given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return bathymetry.
     */
    t_real getBathymetry(t_real,
                         t_real) const;
};

#endif