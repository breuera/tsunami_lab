/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional tsunamievent problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_TSUNAMIEVENT_2D_H
#define TSUNAMI_LAB_SETUPS_TSUNAMIEVENT_2D_H

#include "./../Setup.h"
#include <vector>

namespace tsunami_lab
{
  namespace setups
  {
    class TsunamiEvent2d;
  }
}

/**
 * 1d subcritical setup.
 **/
class tsunami_lab::setups::TsunamiEvent2d : public Setup
{
private:
  //! wall heigth
  t_real m_delta = 20;

  //! Length of bathymetry in x direction.
  t_idx m_bathymetry_length_x;

  //! Length of bathymetry in y direction.
  t_idx m_bathymetry_length_y;

  //! Array of x-values for the bathymetry.
  t_real *m_bathymetry_values_x;

  //! Array of y-values for the bathymetry.
  t_real *m_bathymetry_values_y;

  //! Array for the bathymetry.
  t_real *m_bathymetry;

  //! Length of displacement in x direction.
  t_idx m_displacement_length_x;

  //! Length of displacement in y direction.
  t_idx m_displacement_length_y;

  //! Array of x-values for the displacement.
  t_real *m_displacement_values_x;

  //! Array of y-values for the displacement.
  t_real *m_displacement_values_y;

  //! Array for the displacement.
  t_real *m_displacement;

  /**
   * @brief Get initial displacement
   *
   * @param i_x x-coordinate of the queried point.
   * @param i_y y-coordinate of the queried point.
   * @return displacement
   */
  t_real getDisplacement(t_real i_x,
                         t_real i_y) const;

  /**
   * @brief Get Bathymetry from CSV file
   *
   * @param i_x x-coordinate of the queried point.
   * @param i_y y-coordinate of the queried point.
   * @return bathymetry from csv
   */
  t_real getBathymetryFromNetCdf(t_real i_x,
                                 t_real i_y) const;

public:
  /**
   * @brief Construct a new TsunamiEvent1d object
   *
   */
  TsunamiEvent2d();

  /**
   * Gets the water height.
   *
   * @param i_x x-coordinate of the queried point.
   * @param i_y y-coordinate of the queried point.
   * @return height of water.
   **/
  t_real getHeight(t_real i_x,
                   t_real i_y) const;

  /**
   * Gets the momentum in x-direction.
   *
   * @return momentum in x-direction.
   **/
  t_real getMomentumX(t_real,
                      t_real) const;

  /**
   * Gets the momentum in y-direction.
   *
   * @return momentum in y-direction.
   **/
  t_real getMomentumY(t_real,
                      t_real) const;

  /**
   * @brief Gets the bathymetry
   *
   * @param i_x x-coordinate of the queried point.
   * @param i_y y-coordinate of the queried point.
   * @return bathymetry value
   */
  t_real getBathymetry(t_real i_x,
                       t_real i_y) const;
};

#endif