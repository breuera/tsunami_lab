/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional supercritical problem.
 **/
#include "Supercritical1d.h"

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getHeight(t_real i_x,
                                                                    t_real) const
{
  if (0 <= i_x && i_x <= 25)
  {
    return -getBathymetry(i_x, 0);
  }
  else
  {
    return 0;
  }
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getMomentumX(t_real i_x,
                                                                       t_real) const
{
  if (0 <= i_x && i_x <= 25)
  {
    return 0.18;
  }
  else
  {
    return 0;
  }
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getMomentumY(t_real,
                                                                       t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getBathymetry(t_real i_x,
                                                                        t_real) const
{
  if (8 < i_x && i_x < 12)
  {
    return -0.13 - 0.05 * (i_x - 10) * (i_x - 10);
  }
  else
  {
    return -0.33;
  }
}