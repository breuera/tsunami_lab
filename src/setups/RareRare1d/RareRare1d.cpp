/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * One-dimensional rare-rare problem.
 **/
#include "RareRare1d.h"

tsunami_lab::setups::RareRare1d::RareRare1d( t_real i_h,
                                             t_real i_hu,
                                             t_real i_dis ) {
  m_h = i_h;
  m_hu = i_hu;
  m_dis = i_dis;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getHeight( t_real,
                                                                t_real  ) const {
  return m_h;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getMomentumX( t_real i_x,
                                                                   t_real ) const {
  if( i_x <= m_dis ) {
    return -m_hu;
  }
  else {
    return m_hu;
  }
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getMomentumY( t_real,
                                                                   t_real ) const {
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getBathymetry( t_real,
                                                                    t_real ) const {
  return 0;                                                                    
}