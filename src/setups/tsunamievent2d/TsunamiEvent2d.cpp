/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional tsunamievent problem.
 **/
#include "TsunamiEvent2d.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "../../io/csv/Csv.h"

tsunami_lab::setups::TsunamiEvent2d::TsunamiEvent2d(std::vector<t_real> i_b_in)
{
  m_b_in = i_b_in;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getHeight(t_real i_x,
                                                                   t_real i_y) const
{
  t_real l_b_in = getBathymetryFromCSV(i_x, i_y);
  if (l_b_in < 0)
  {
    return std::max(-l_b_in, m_delta);
  }
  else
  {
    return 0;
  }
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getMomentumX(t_real,
                                                                      t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getMomentumY(t_real,
                                                                      t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getBathymetry(t_real i_x,
                                                                       t_real i_y) const
{
  t_real l_b_in = getBathymetryFromCSV(i_x, i_y);

  if (l_b_in < 0)
  {
    return std::min(l_b_in, -m_delta) + getDisplacement(i_x, i_y);
  }
  else
  {
    return std::max(l_b_in, m_delta) + getDisplacement(i_x, i_y);
  }
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getDisplacement(t_real i_x,
                                                                         t_real i_y) const
{
  // TODO: implement netcdf-reader and finish this
  return i_x + i_y;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getBathymetryFromCSV(t_real i_x,
                                                                              t_real i_y) const
{
  // TODO: implement netcdf-reader and finish this
  return i_x + i_y;
}