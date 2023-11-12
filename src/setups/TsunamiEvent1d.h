/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/

#ifndef TSUNAMI_LAB_SETUPS_TSUNAMI_EVENT_1D_H
#define TSUNAMI_LAB_SETUPS_TSUNAMI_EVENT_1D_H

#include "Setup.h"

namespace tsunami_lab {
  namespace setups {
    class TsunamiEvent1d;
  }

}
/**
 * 1d custom setup.
 **/
class tsunami_lab::setups::TsunamiEvent1d: public Setup {
  private:
    //! bathymetry on the left side 
    t_real m_bathymetry;

    //! momentum on the left side 
    t_real m_x = 0;
    
    //! height on the right side
    t_real m_y = 0;

    //! momentum on the right side 
    t_real m_distance = 0;

    //! location of the middle
    t_real m_locattionMis = 0;

    //! height on a given loaction
    t_real m_height = 0;

  public:
    /**
     * Constructor.
     *
     * @param i_bathymetry bathymetry on location i_x.
     * @param i_distance distance from the coast.
     * @param i_locationMid location (x-coordinate) of the middle.
     **/
    TsunamiEvent1d( t_real i_bathymetry,
                    t_real i_distance,
                    t_real i_loacationMid);


    /**
     * Gets the momentum in x-direction.
     *
     * @param i_x x-coordinate of the queried point.
     * @return momentum in x-direction.
     **/
    t_real getHeight( t_real i_x,
                      t_real     ) const;

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
     * Gets the bathymetry at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getBathymetry( t_real i_x,
                          t_real        ) const;

};

#endif