/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional tsunamievent problem.
 **/
#include "TsunamiEvent2d.h"
#include "../../io/netCDF/NetCDF.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "../../io/csv/Csv.h"

tsunami_lab::setups::TsunamiEvent2d::TsunamiEvent2d()
{
  tsunami_lab::io::NetCdf *netCDF = nullptr;

  netCDF = new tsunami_lab::io::NetCdf();

  std::cout << "Entering TsunamiEvent2d" << std::endl;

  std::string bat_path = "data/artificialtsunami/artificialtsunami_bathymetry_1000.nc";
  std::string dis_path = "data/artificialtsunami/artificialtsunami_displ_1000.nc";

  netCDF->read(m_bathymetry_length_x,
               m_bathymetry_length_y,
               &m_bathymetry_values_x,
               &m_bathymetry_values_y,
               &m_bathymetry,
               bat_path);

  netCDF->read(m_displacement_length_x,
               m_displacement_length_y,
               &m_displacement_values_x,
               &m_displacement_values_y,
               &m_displacement,
               dis_path);
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getHeight(t_real i_x,
                                                                   t_real i_y) const
{
  t_real l_b_in = getBathymetryFromNetCdf(i_x, i_y);
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
  t_real l_b_in = getBathymetryFromNetCdf(i_x, i_y);

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
  return m_displacement[(int)std::floor(i_y) * m_bathymetry_length_x + (int)std::floor(i_x)];
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getBathymetryFromNetCdf(t_real i_x,
                                                                                 t_real i_y) const
{
  return m_bathymetry[(int)std::floor(i_y) * m_bathymetry_length_x + (int)std::floor(i_x)];
}