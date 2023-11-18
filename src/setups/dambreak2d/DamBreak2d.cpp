/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional dam break problem.
 **/
#include "DamBreak2d.h"

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getHeight(t_real i_x,
                                                               t_real i_y) const
{
  // move circle by amount
  t_real x_offset = i_x - 50;
  t_real y_offset = i_y - 50;
  if (getBathymetry(x_offset, y_offset) > 0)
  {
    return 0;
  }
  if (std::sqrt(x_offset * x_offset + y_offset * y_offset) < 10)
  {
    return 10;
  }
  else
  {
    return 5;
  }
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getMomentumX(t_real,
                                                                  t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getMomentumY(t_real,
                                                                  t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getBathymetry(t_real i_x,
                                                                   t_real i_y) const
{
  // move circle by amount
  t_real x_offset = i_x - 10;
  t_real y_offset = i_y - 25;
  if (std::sqrt(x_offset * x_offset + y_offset * y_offset) < 3)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}