/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * One-dimensional rare-rare problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_RARE_RARE_1D_H
#define TSUNAMI_LAB_SETUPS_RARE_RARE_1D_H

#include "Setup.h"

namespace tsunami_lab {
  namespace setups {
    class RareRare1d;
  }
}

/**
 * 1d rare-rare setup.
 **/
class tsunami_lab::setups::RareRare1d: public Setup {
  private:
    //! height on both sides 
    t_real m_h = 0;

    //! momentum on both sides
    t_real m_hu= 0;

    //! location of the smash position
    t_real m_dis = 0;

  public:
    /**
     * Constructor.
     *
     * @param i_h water height on both sides of the smash position.
     * @param i_hu momentum on both sides of the smash position.
     * @param i_dis location (x-coordinate) of the smash position.
     **/
    RareRare1d( t_real i_h,
                t_real i_hu,
                t_real i_dis );

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