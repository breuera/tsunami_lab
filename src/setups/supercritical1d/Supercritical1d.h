/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional supercritical problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_SHOCK_SHOCK_1D_H
#define TSUNAMI_LAB_SETUPS_SHOCK_SHOCK_1D_H

#include "../Setup.h"

namespace tsunami_lab {
  namespace setups {
    class Supercritical1d;
  }
}

/**
 * 1d supercritical setup.
 **/
class tsunami_lab::setups::Supercritical1d: public Setup {
  private:
    //! height 
    t_real m_height = 0;
    
    //! momentum on the left side (and right side)
    t_real m_momentum = 0;

    //! location of the middle
    t_real m_middlePoint = 0;

  public:
    /**
     * Constructor.
     *
     * @param i_height water height.
     * @param i_momentum water momentum.
     * @param i_middlePoint location (x-coordinate) of the middlepoint.
     **/
    Supercritical1d( t_real i_height,
                t_real i_momentum,
                t_real i_middlePoint );

    /**
     * Gets the water height at a given point.
     *
     * @return height at the given point.
     **/
    t_real getHeight( t_real,
                      t_real      ) const;

    /**
     * Gets the momentum in x-direction.
     *
     * @param i_x x-coordinate of the queried point.
     * @return momentum in x-direction.
     **/
    t_real getMomentumX( t_real i_x,
                         t_real ) const;

    /**
     * Gets the momentum in y-direction.
     *
     * @return momentum in y-direction.
     **/
    t_real getMomentumY( t_real,
                         t_real ) const;

    /**
     * @brief Gets the bathymetry
     *
     * @return bathymetry
     */
    t_real getBathymetry(t_real i_x,
                       t_real) const;

};

#endif