/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * One-dimensional shock-shock problem.
 **/
#include "ShockShock1d.h"

tsunami_lab::setups::ShockShock1d::ShockShock1d(t_real i_h,
                                                t_real i_hu,
                                                t_real i_dis ) {
  m_h = i_h;
  m_hu = i_hu;
  m_dis = i_dis;
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getHeight(   t_real,
                                                                    t_real  ) const {
    return m_h;
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getMomentumX(t_real i_x,
                                                                    t_real ) const {
  if( i_x <= m_dis ) {
    return m_hu;
  }
  else {
    return -m_hu;
  }
}

tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getMomentumY(t_real,
                                                                    t_real ) const {
  return 0;
}