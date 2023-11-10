/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional subcritical problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_SUBCRITICAL_1D_H
#define TSUNAMI_LAB_SETUPS_SUBCRITICAL_1D_H

#include "../Setup.h"

namespace tsunami_lab
{
  namespace setups
  {
    class Subcritical1d;
  }
}

/**
 * 1d subcritical setup.
 **/
class tsunami_lab::setups::Subcritical1d : public Setup
{
public:
  /**
   * Gets the water height at a given point.
   *
   * @return height at the given point.
   **/
  t_real getHeight(t_real,
                   t_real) const;

  /**
   * Gets the momentum in x-direction.
   *
   * @param i_x x-coordinate of the queried point.
   * @return momentum in x-direction.
   **/
  t_real getMomentumX(t_real i_x,
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
   * @param i_x x-coordinate of the queried point.
   * @return bathymetry
   */
  t_real getBathymetry(t_real i_x,
                       t_real) const;
};

#endif