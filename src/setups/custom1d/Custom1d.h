/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custom wave problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_CUSTOM_1D_H
#define TSUNAMI_LAB_SETUPS_CUSTOM_1D_H

#include "../Setup.h"

namespace tsunami_lab
{
    namespace setups
    {
        class Custom1d;
    }
}

class tsunami_lab::setups::Custom1d : public Setup
{
private:
    //! height on the left side
    t_real m_heightLeft = 0;

    //! height on the right side
    t_real m_heightRight = 0;

    //! momentum on the left side
    t_real m_momentumLeft = 0;

    //! momentum on the right side
    t_real m_momentumRight = 0;

    //! middlepoint
    t_real m_middlePoint = 0;

public:
    /**
     * @brief Constructor.
     *
     * @param i_heightLeft water height on the left side of the dam.
     * @param i_heightRight water height on the right side of the dam.
     * @param i_momentumLeft momentum on the left side of the dam.
     * @param i_momentumRight momentum on the right side of the dam.
     * @param i_middle location (x-coordinate) of the middle.
     */
    Custom1d(t_real i_heightLeft,
             t_real i_heightRight,
             t_real i_momentumLeft,
             t_real i_momentumRight,
             t_real i_middle);

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getHeight(t_real i_x,
                     t_real) const;

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
     * @brief Gets the bathymetry
     *
     * @return bathymetry
     */
    t_real getBathymetry(t_real,
                         t_real) const;
};

#endif