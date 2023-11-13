/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional tsunamievent problem.
 **/
#include "TsunamiEvent1d.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "../../io/csv/Csv.h"

tsunami_lab::setups::TsunamiEvent1d::TsunamiEvent1d(std::vector<t_real> i_b_in)
{
  m_b_in = i_b_in;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getHeight(t_real i_x,
                                                                   t_real) const
{
  t_real l_b_in = getBathymetryFromCSV(i_x);
  if (l_b_in < 0)
  {
    return std::max(-l_b_in, m_delta);
  }
  else
  {
    return 0;
  }
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
  t_real l_b_in = getBathymetryFromCSV(i_x);

  if (l_b_in < 0)
  {
    return std::min(l_b_in, -m_delta) + getDisplacement(i_x);
  }
  else
  {
    return std::max(l_b_in, m_delta) + getDisplacement(i_x);
  }
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getDisplacement(t_real i_x) const
{
  if (250000 > i_x && i_x > 175000)
  {
    return 10 * sin(((i_x - 175000) / 37500) * M_PI + M_PI);
  }
  else
  {
    return 0;
  }
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetryFromCSV(t_real i_x) const
{
  int index = i_x / 250; // 250m steps

  return m_b_in[index];
}