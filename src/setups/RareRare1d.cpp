/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * One-dimensional rare-rare problem.
 **/
#include "RareRare1d.h"

tsunami_lab::setups::RareRare1d::RareRare1d( t_real i_hL,
                                             t_real i_hR,
                                             t_real i_huL,
                                             t_real i_huR,
                                             t_real i_dis ) {
  m_hL = i_hL;
  m_hR = i_hR;
  m_huL = i_huL;
  m_huR = i_huR;
  m_dis = i_dis;
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getHeight( t_real i_x,
                                                                t_real      ) const {
  if( i_x <= m_dis ) {
    return m_hL;
  }
  else {
    return m_hR;
  }
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getMomentumX( t_real i_x,
                                                                   t_real ) const {
  if( i_x <= m_dis ) {
    return m_huL;
  }
  else {
    return m_huR;
  }
}

tsunami_lab::t_real tsunami_lab::setups::RareRare1d::getMomentumY( t_real,
                                                                   t_real ) const {
  return 0;
}