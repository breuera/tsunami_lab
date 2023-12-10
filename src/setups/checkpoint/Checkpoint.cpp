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
  delete[] m_bathymetry;
  delete[] m_height;
  delete[] m_momentumX;
  delete[] m_momentumY;
}

tsunami_lab::setups::Checkpoint::Checkpoint()
{
  tsunami_lab::io::NetCdf *netCDF = nullptr;

  netCDF = new tsunami_lab::io::NetCdf();

  std::cout << "Entering Checkpoint" << std::endl;

  netCDF->readCheckpoint(&m_nx,
                         &m_ny,
                         &m_height,
                         &m_momentumX,
                         &m_momentumY,
                         &m_bathymetry,
                         &m_x_offset,
                         &m_y_offset,
                         &m_solver_choice,
                         &m_state_boundary_left,
                         &m_state_boundary_right,
                         &m_state_boundary_top,
                         &m_state_boundary_bottom,
                         &m_width,
                         &m_endTime,
                         &m_timeStep,
                         &m_time,
                         &m_nOut,
                         &m_hMax,
                         &m_simulated_frame,
                         &m_filename,
                         "checkpoints/checkpoint_1.nc");

  delete netCDF;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getHeight(t_real i_x,
                                                               t_real i_y) const
{
  t_idx x_idx = static_cast<t_idx>(i_x);
  t_idx y_idx = static_cast<t_idx>(i_y);

  return m_height[x_idx + y_idx * m_nx];
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getMomentumX(t_real i_x,
                                                                  t_real i_y) const
{
  t_idx x_idx = static_cast<t_idx>(i_x);
  t_idx y_idx = static_cast<t_idx>(i_y);

  return m_momentumX[x_idx + y_idx * m_nx];
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getMomentumY(t_real i_x,
                                                                  t_real i_y) const
{
  t_idx x_idx = static_cast<t_idx>(i_x);
  t_idx y_idx = static_cast<t_idx>(i_y);

  return m_momentumY[x_idx + y_idx * m_nx];
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getBathymetry(t_real i_x,
                                                                   t_real i_y) const
{
  t_idx x_idx = static_cast<t_idx>(i_x);
  t_idx y_idx = static_cast<t_idx>(i_y);

  return m_bathymetry[x_idx + y_idx * m_nx];
}

tsunami_lab::t_idx tsunami_lab::setups::Checkpoint::getNx() const
{
  return m_nx;
}

tsunami_lab::t_idx tsunami_lab::setups::Checkpoint::getNy() const
{
  return m_ny;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getXOffset() const
{
  return m_x_offset;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getYOffset() const
{
  return m_y_offset;
}

int tsunami_lab::setups::Checkpoint::getSolverChoice() const
{
  return m_solver_choice;
}

int tsunami_lab::setups::Checkpoint::getStateBoundaryLeft() const
{
  return m_state_boundary_left;
}

int tsunami_lab::setups::Checkpoint::getStateBoundaryRight() const
{
  return m_state_boundary_right;
}

int tsunami_lab::setups::Checkpoint::getStateBoundaryTop() const
{
  return m_state_boundary_top;
}

int tsunami_lab::setups::Checkpoint::getStateBoundaryBottom() const
{
  return m_state_boundary_bottom;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getWidth() const
{
  return m_width;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getEndTime() const
{
  return m_endTime;
}

tsunami_lab::t_idx tsunami_lab::setups::Checkpoint::getTimeStep() const
{
  return m_timeStep;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getTime() const
{
  return m_time;
}

tsunami_lab::t_idx tsunami_lab::setups::Checkpoint::getNOut() const
{
  return m_nOut;
}

tsunami_lab::t_real tsunami_lab::setups::Checkpoint::getHMax() const
{
  return m_hMax;
}

tsunami_lab::t_idx tsunami_lab::setups::Checkpoint::getSimulated_frame() const
{
  return m_simulated_frame;
}

std::string tsunami_lab::setups::Checkpoint::getFilename() const
{
  return m_filename;
}
