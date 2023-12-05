/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional tsunamievent problem.
 **/
#include "Checkpoint.h"
#include "../../io/netCDF/NetCDF.h"
#include <iostream>

tsunami_lab::setups::Checkpoint::~Checkpoint()
{
  delete[] m_bathymetry_values_x;
  delete[] m_bathymetry_values_y;
  delete[] m_bathymetry;
  delete[] m_displacement_values_x;
  delete[] m_displacement_values_y;
  delete[] m_displacement;
}

tsunami_lab::setups::Checkpoint::Checkpoint(std::string bat_path,
                                            std::string dis_path,
                                            t_real *o_width,
                                            t_real *o_height,
                                            t_real *o_x_offset,
                                            t_real *o_y_offset)
{
  tsunami_lab::io::NetCdf *netCDF = nullptr;

  netCDF = new tsunami_lab::io::NetCdf();

  std::cout << "Entering Checkpoint" << std::endl;

  netCDF->read(&m_bathymetry_length_x,
               &m_bathymetry_length_y,
               &m_bathymetry_values_x,
               &m_bathymetry_values_y,
               &m_bathymetry,
               bat_path);

  netCDF->read(&m_displacement_length_x,
               &m_displacement_length_y,
               &m_displacement_values_x,
               &m_displacement_values_y,
               &m_displacement,
               dis_path);

  // Make width/height/offsets public after calculatin,
  // opens possibility for different input-files
  *o_width = m_bathymetry_values_x[m_bathymetry_length_x - 1] - m_bathymetry_values_x[0];
  *o_height = m_bathymetry_values_y[m_bathymetry_length_y - 1] - m_bathymetry_values_y[0];

  m_x_offset = m_bathymetry_values_x[0];
  m_y_offset = m_bathymetry_values_y[0];
  *o_x_offset = -m_x_offset;
  *o_y_offset = -m_y_offset;

  delete netCDF;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getHeight(t_real i_x,
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

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getMomentumX(t_real,
                                                                  t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getMomentumY(t_real,
                                                                  t_real) const
{
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getBathymetry(t_real i_x,
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

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getDisplacement(t_real i_x,
                                                                     t_real i_y) const
{
  if (i_x < m_displacement_values_x[0] || i_x > m_displacement_values_x[m_displacement_length_x - 1])
  {
    return 0;
  }
  if (i_y < m_displacement_values_y[0] || i_y > m_displacement_values_y[m_displacement_length_y - 1])
  {
    return 0;
  }

  t_real l_dxy = m_displacement_values_x[1] - m_displacement_values_x[0];
  t_real l_offset_x = m_displacement_values_x[0];
  t_real l_offset_y = m_displacement_values_y[0];

  t_idx l_x = (i_x - l_offset_x) / l_dxy;
  t_idx l_y = (i_y - l_offset_y) / l_dxy;

  return m_displacement[l_y * m_displacement_length_x + l_x];
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getBathymetryFromNetCdf(t_real i_x,
                                                                             t_real i_y) const
{

  if (i_x < m_bathymetry_values_x[0] || i_x > m_bathymetry_values_x[m_bathymetry_length_x - 1])
  {
    return 0;
  }
  if (i_y < m_bathymetry_values_y[0] || i_y > m_bathymetry_values_y[m_bathymetry_length_y - 1])
  {
    return 0;
  }

  t_real l_dxy = m_bathymetry_values_x[1] - m_bathymetry_values_x[0];

  t_idx l_x = (i_x - m_x_offset) / l_dxy;
  t_idx l_y = (i_y - m_y_offset) / l_dxy;

  return m_bathymetry[l_y * m_bathymetry_length_x + l_x];
}