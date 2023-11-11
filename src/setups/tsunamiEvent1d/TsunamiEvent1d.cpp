/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional tsunamiEvent problem.
 **/
#include "TsunamiEvent1d.h"

tsunami_lab::setups::TsunamiEvent1d::TsunamiEvent1d(rapidcsv::Document i_doc, size_t i_rowCount)
{
  m_doc = i_doc;
  m_rowCount = i_rowCount;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getHeight(t_real i_x,
                                                                   t_real) const
{
  t_real l_bin = getBathymetryBin(i_x);
  if (l_bin < 0)
  {
    // max(-bin, delta)
    if (-l_bin > m_delta)
      return -l_bin;
    else
      return m_delta;
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
  t_real l_bin = getBathymetryBin(i_x);
  if (l_bin < 0)
  {
    // min(bin, -delta) + d
    if (l_bin < -m_delta)
      return l_bin + getDisplacement(i_x);
    else
      return -m_delta + getDisplacement(i_x);
  }
  // max(bin, delta) + d
  if (l_bin > m_delta)
    return l_bin + getDisplacement(i_x);
  else
    return m_delta + getDisplacement(i_x);
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getDisplacement(t_real i_x) const
{
  if (175000 < i_x && i_x < 250000)
  {
    return 10 * std::sin(M_PI * ((i_x - 175000) / 37500) + M_PI);
  }
  else
  {
    return 0;
  }
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetryBin(t_real i_x) const
{
  // convert i_x to cell index (assuming 250m cells)
  int l_row = i_x / 250;
  return io::Csv::readLine(m_doc, l_row);
}