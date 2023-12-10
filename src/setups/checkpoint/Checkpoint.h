/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional tsunamievent problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_CHECKPOINT_H
#define TSUNAMI_LAB_SETUPS_CHECKPOINT_H

#include "./../Setup.h"
#include <string>

namespace tsunami_lab
{
  namespace setups
  {
    class Checkpoint;
  }
}

/**
 * 1d subcritical setup.
 **/
class tsunami_lab::setups::Checkpoint : public Setup
{
private:
  //! Array for the bathymetry.
  t_real *m_bathymetry;

  t_real *m_height;

  t_real *m_momentumX;

  t_real *m_momentumY;

  t_real m_x_offset;

  t_real m_y_offset;

  t_idx m_nx;

  t_idx m_ny;

  int m_solver_choice;

  int m_state_boundary_left;

  int m_state_boundary_right;

  int m_state_boundary_top;

  int m_state_boundary_bottom;

  t_real m_width;

  t_real m_endTime;

  t_idx m_timeStep;

  t_real m_time;

  t_idx m_nOut;

  t_real m_hMax;

  t_idx m_simulated_frame;

  std::string m_filename;

  int m_resolutionDiv;

public:
  /**
   * @brief Construct a new TsunamiEvent1d object
   *
   */
  Checkpoint();

  /**
   * @brief Destroy the Tsunami Event 2d object
   *
   */
  ~Checkpoint();

  /**
   * Gets the water height.
   *
   * @return height of water.
   **/
  t_real getHeight(t_real i_x,
                   t_real i_y) const;

  /**
   * Gets the momentum in x-direction.
   *
   * @return momentum in x-direction.
   **/
  t_real getMomentumX(t_real i_x,
                      t_real i_y) const;

  /**
   * Gets the momentum in y-direction.
   *
   * @return momentum in y-direction.
   **/
  t_real getMomentumY(t_real i_x,
                      t_real i_y) const;

  /**
   * @brief Gets the bathymetry
   *
   * @return bathymetry value
   */
  t_real getBathymetry(t_real i_x,
                       t_real i_y) const;

  t_idx getNx() const;

  t_idx getNy() const;

  t_real getXOffset() const;

  t_real getYOffset() const;

  int getSolverChoice() const;
  int getStateBoundaryLeft() const;
  int getStateBoundaryRight() const;
  int getStateBoundaryTop() const;
  int getStateBoundaryBottom() const;
  t_real getWidth() const;
  t_real getEndTime() const;
  t_idx getTimeStep() const;
  t_real getTime() const;
  t_idx getNOut() const;
  t_real getHMax() const;
  t_idx getSimulated_frame() const;
  std::string getFilename() const;
  int getResolutionDiv() const;
};

#endif