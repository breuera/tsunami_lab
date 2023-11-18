/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional dam break problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_DAM_BREAK_2D_H
#define TSUNAMI_LAB_SETUPS_DAM_BREAK_2D_H

#include <cmath>
#include "../Setup.h"

namespace tsunami_lab
{
  namespace setups
  {
    class DamBreak2d;
  }
}

/**
 * 2d dam break setup.
 **/
class tsunami_lab::setups::DamBreak2d : public Setup
{

public:
  /**
   * Gets the water height at a given point.
   *
   * @param i_x x-coordinate of the queried point.
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
   * @brief Gets the bathymetry
   *
   * @return bathymetry value
   */
  t_real getBathymetry(t_real i_x,
                       t_real i_y) const;
};

#endif