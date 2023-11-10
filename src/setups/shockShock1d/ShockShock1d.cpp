/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional shock shock problem.
 **/
#include "ShockShock1d.h"

tsunami_lab::setups::ShockShock1d::ShockShock1d(t_real i_height,
                                                t_real i_momentum,
                                                t_real i_middlePoint)
{
  m_height = i_height;
  m_momentum = i_momentum;
  m_middlePoint = i_middlePoint;
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getHeight(t_real,
                                                                 t_real) const
{
  return m_height;
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getMomentumX(t_real i_x,
                                                                    t_real) const
{
  if (i_x < m_middlePoint)
  {
    return m_momentum;
  }
  else
  {
    return -m_momentum;
  }
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getMomentumY(t_real,
                                                                    t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getBathymetry(t_real,
                                                                     t_real) const
{
  return 0;
}