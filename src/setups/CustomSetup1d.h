/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/

#ifndef TSUNAMI_LAB_SETUPS_CUSTOM_SETUP_1D_H
#define TSUNAMI_LAB_SETUPS_CUSTOM_SETUP_1D_H

#include "Setup.h"

namespace tsunami_lab {
  namespace setups {
    class CustomSetup1d;
  }
}

/**
 * 1d custom setup.
 **/
class tsunami_lab::setups::CustomSetup1d: public Setup {
  private:
    //! height on the left side 
    t_real m_heightLeft = 0;

    //! momentum on the left side 
    t_real m_momentumLeft = 0;
    
    //! height on the right side
    t_real m_heightRight = 0;

    //! momentum on the right side 
    t_real m_momentumRight = 0;

    //! location of the middle
    t_real m_locationMiddle = 0;

  public:
    /**
     * Constructor.
     *
     * @param i_hL water height on the left side of the middle.
     * @param i_hR water height on the right side of the middle.
     * @param i_huL water momentum on the left side of the middle.
     * @param i_huR water momentum on the right side of the middle.
     * @param i_locationDam location (x-coordinate) of the middle.
     **/
    CustomSetup1d(  t_real i_hL,
                    t_real i_hR,
                    t_real i_huL,
                    t_real i_huR,
                    t_real i_locMiddle );

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getHeight( t_real i_x,
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

};

#endif