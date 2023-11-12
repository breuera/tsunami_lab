/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional supercritical problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_SUPERCRITICAL_1D_H
#define TSUNAMI_LAB_SETUPS_SUPERCRITICAL_1D_H

#include "./../Setup.h"

namespace tsunami_lab
{
  namespace setups
  {
    class Supercritical1d;
  }
}

/**
 * 1d subcritical setup.
 **/
class tsunami_lab::setups::Supercritical1d : public Setup
{

public:
  /**
   * Constructor.
   *
   **/
  Supercritical1d();

  /**
   * Gets the water height.
   *
   * @param i_x x-coordinate of the queried point.
   * @return height of water.
   **/
  t_real getHeight(t_real i_x,
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
   *
   * @param i_x x-coordinate of the queried point.
   * @return bathymetry value
   */
  t_real getBathymetry(t_real i_x,
                       t_real) const;
};

#endif