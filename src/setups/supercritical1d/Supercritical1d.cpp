/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional supercritical problem.
 **/
#include "Supercritical1d.h"

tsunami_lab::setups::Supercritical1d::Supercritical1d(t_real i_height,
                                                t_real i_momentum,
                                                t_real i_middlePoint)
{
  m_height = i_height;
  m_momentum = i_momentum;
  m_middlePoint = i_middlePoint;
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getHeight(t_real i_x,
                                                                 t_real) const
{
  if(0 <= i_x && i_x <= 25)
  {
    return -getBathymetry(i_x, 0);
  }  
  return m_height;
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getMomentumX(t_real i_x,
                                                                    t_real) const
{
    if(0 <= i_x && i_x <= 25)
  {
    return 0.18;
  }  
  return m_momentum;
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getMomentumY(t_real,
                                                                    t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getBathymetry(t_real i_x,
                                                                    t_real) const
{
  if( 8 <= i_x  && i_x <= 12)
  {
    return -0.13 - 0.05 * (i_x - 10) * (i_x - 10);
  } 
  else 
  {
    return -0.33;
  }
}