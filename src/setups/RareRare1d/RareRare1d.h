/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional Rare-Rare problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_RARE_RARE_1D_H
#define TSUNAMI_LAB_SETUPS_RARE_RARE_1D_H

#include "./../Setup.h"

namespace tsunami_lab
{
  namespace setups
  {
    class RareRare1d;
  }
}

/**
 * 1d rare-rare setup.
 **/
class tsunami_lab::setups::RareRare1d : public Setup
{
private:
  // height of the water
  t_real m_height = 0;

  // momentum in x-direction
  t_real m_momentum = 0;

  // location of the centerpoint
  t_real m_locationCenter = 0;

public:
  /**
   * Constructor.
   *
   * @param i_height water height.
   * @param i_momentum water momentum.
   * @param i_locationCenter location (x-coordinate) of the centerpoint.
   **/
  RareRare1d(t_real i_height,
             t_real i_momentum,
             t_real i_locationCenter);

  /**
   * Gets the water height.
   *
   * @return height of water.
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
};

#endif