/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional artificial-tsunami problem.
 **/
#include "ArtificialTsunami2d.h"

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getHeight(t_real,
                                                                        t_real) const
{
  return 100;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getMomentumX(t_real,
                                                                           t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getMomentumY(t_real,
                                                                           t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getBathymetry(t_real i_x,
                                                                            t_real i_y) const
{
  return -100 + getDisplacement(i_x, i_y);
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getDisplacement(t_real i_x,
                                                                              t_real i_y) const
{
  if (i_x >= -500 && i_x <= 500 && i_y >= -500 && i_y <= 500)
  {
    return 5 * f(i_x, i_y) * g(i_x, i_y);
  }
  return 0;
}
