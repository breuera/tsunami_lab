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
    //! height on the left side 
    t_real m_hL = 0;
    
    //! height on the right side
    t_real m_hR= 0;

    //! momentum on the left side
    t_real m_huL= 0;

    //! momentum on the right side
    t_real m_huR= 0;

    //! location of the smash position
    t_real m_dis = 0;

  public:
    /**
     * Constructor.
     *
     * @param i_hL water height on the left side of the smash position.
     * @param i_hR water height on the right side of the smash position.
     * @param i_huL momentum on the left side of the smash position.
     * @param i_huR momentum on the right side of the smash position.
     * @param i_dis location (x-coordinate) of the smash position.
     **/
    RareRare1d( t_real i_hL,
                t_real i_hR,
                t_real i_huL,
                t_real i_huR,
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