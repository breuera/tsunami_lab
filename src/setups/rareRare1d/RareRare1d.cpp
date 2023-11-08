/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional rare rare problem.
 **/
#include "RareRare1d.h"

tsunami_lab::setups::RareRare1d::RareRare1d(t_real i_height,
                                            t_real i_momentum,
                                            t_real i_middlePoint)
{
  m_height = i_height;
  m_momentum = i_momentum;
  m_middlePoint = i_middlePoint;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getHeight(t_real,
                                                               t_real) const
{
  return m_height;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getMomentumX(t_real i_x,
                                                                  t_real) const
{
  if (i_x < m_middlePoint)
  {
    return -(m_momentum);
  }
  else
  {
    return m_momentum;
  }

  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getMomentumY(t_real,
                                                                  t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getBathymetry(t_real,
                                                                   t_real) const
{
  return 0;
}