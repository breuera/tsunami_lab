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

public:
  /**
   * @brief Construct a new Checkpoint object
   *
   * This function is used to construct a new Checkpoint object.
   */
  Checkpoint();

  /**
   * @brief Destroy the Checkpoint object
   *
   * This function is used to destroy the Checkpoint object.
   */
  ~Checkpoint();

  /**
   * @brief Gets the water height.
   *
   * @param i_x The x-coordinate.
   * @param i_y The y-coordinate.
   * @return The height of water at the given coordinates.
   */
  t_real getHeight(t_real i_x, t_real i_y) const;

  /**
   * @brief Gets the momentum in x-direction.
   *
   * @param i_x The x-coordinate.
   * @param i_y The y-coordinate.
   * @return The momentum in x-direction at the given coordinates.
   */
  t_real getMomentumX(t_real i_x, t_real i_y) const;

  /**
   * @brief Gets the momentum in y-direction.
   *
   * @param i_x The x-coordinate.
   * @param i_y The y-coordinate.
   * @return The momentum in y-direction at the given coordinates.
   */
  t_real getMomentumY(t_real i_x, t_real i_y) const;

  /**
   * @brief Gets the bathymetry.
   *
   * @param i_x The x-coordinate.
   * @param i_y The y-coordinate.
   * @return The bathymetry value at the given coordinates.
   */
  t_real getBathymetry(t_real i_x, t_real i_y) const;

  /**
   * @brief Gets the number of cells in the x-direction.
   *
   * @return The number of cells in the x-direction.
   */
  t_idx getNx() const;

  /**
   * @brief Gets the number of cells in the y-direction.
   *
   * @return The number of cells in the y-direction.
   */
  t_idx getNy() const;

  /**
   * @brief Gets the x-offset.
   *
   * @return The x-offset.
   */
  t_real getXOffset() const;

  /**
   * @brief Gets the y-offset.
   *
   * @return The y-offset.
   */
  t_real getYOffset() const;

  /**
   * @brief Gets the solver choice.
   *
   * @return The solver choice.
   */
  int getSolverChoice() const;

  /**
   * @brief Gets the state boundary on the left.
   *
   * @return The state boundary on the left.
   */
  int getStateBoundaryLeft() const;

  /**
   * @brief Gets the state boundary on the right.
   *
   * @return The state boundary on the right.
   */
  int getStateBoundaryRight() const;

  /**
   * @brief Gets the state boundary on the top.
   *
   * @return The state boundary on the top.
   */
  int getStateBoundaryTop() const;

  /**
   * @brief Gets the state boundary on the bottom.
   *
   * @return The state boundary on the bottom.
   */
  int getStateBoundaryBottom() const;

  /**
   * @brief Gets the width.
   *
   * @return The width.
   */
  t_real getWidth() const;

  /**
   * @brief Gets the end time.
   *
   * @return The end time.
   */
  t_real getEndTime() const;

  /**
   * @brief Gets the time step.
   *
   * @return The time step.
   */
  t_idx getTimeStep() const;

  /**
   * @brief Gets the time.
   *
   * @return The time.
   */
  t_real getTime() const;

  /**
   * @brief Gets the number of outputs.
   *
   * @return The number of outputs.
   */
  t_idx getNOut() const;

  /**
   * @brief Gets the maximum height.
   *
   * @return The maximum height.
   */
  t_real getHMax() const;

  /**
   * @brief Gets the simulated frame.
   *
   * @return The simulated frame.
   */
  t_idx getSimulated_frame() const;

  /**
   * @brief Gets the filename.
   *
   * @return The filename.
   */
  std::string getFilename() const;
};

#endif