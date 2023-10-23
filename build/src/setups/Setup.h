/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Simulation setup.
 **/
#ifndef TSUNAMI_LAB_SETUPS_SETUP_H
#define TSUNAMI_LAB_SETUPS_SETUP_H

#include "../constants.h"

namespace tsunami_lab {
  namespace setups {
    class Setup;
  }
}

/**
 * Base setup.
 **/
class tsunami_lab::setups::Setup {
  public:
    /**
     * Virtual destructor for base class.
     **/
    virtual ~Setup(){};

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return water height at the given point.
     **/
    virtual t_real getHeight( t_real i_x,
                              t_real i_y ) const = 0;

    /**
     * Gets the momentum in x-direction.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return momentum in x-direction.
     **/
    virtual t_real getMomentumX( t_real i_x,
                                 t_real i_y ) const = 0;

    /**
     * Gets the momentum in y-direction.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return momentum in y-direction.
     **/
    virtual t_real getMomentumY( t_real i_x,
                                 t_real i_y ) const = 0;
      
};

#endif