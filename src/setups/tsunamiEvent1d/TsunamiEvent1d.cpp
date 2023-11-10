/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional tsunamiEvent problem.
 **/
#include "TsunamiEvent1d.h"

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getHeight(t_real i_x,
                                                                    t_real) const
{
  int bin = getBathymetryBin(i_x);
  if(bin < 0){
    return std::min(-bin, 20);
  }
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumX(t_real,
                                                                       t_real) const
{
  return 0; 
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumY(t_real,
                                                                       t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetry(t_real i_x,
                                                                        t_real) const
{
  int bin = getBathymetryBin(i_x);
  if(bin < 0){
    return std::min(bin, -20) + getDisplacement(i_x);
  }
  return std::max(bin, 20) + getDisplacement(i_x);
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getDisplacement(t_real i_x)const{
  if(17500 < i_x && i_x < 22500){
    return 10*std::sin(M_PI*(i_x-17500)/37500 + M_PI);
  }else{
    return 0;
  }
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetryBin(t_real i_x)const{
  return io::Csv::readLine(this->doc, i_x);
}