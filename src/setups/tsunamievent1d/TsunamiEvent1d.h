/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional tsunamievent problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_TSUNAMIEVENT_1D_H
#define TSUNAMI_LAB_SETUPS_TSUNAMIEVENT_1D_H

#include "./../Setup.h"

namespace tsunami_lab
{
  namespace setups
  {
    class TsunamiEvent1d;
  }
}

/**
 * 1d subcritical setup.
 **/
class tsunami_lab::setups::TsunamiEvent1d : public Setup
{
private:
  //! wall heigth
  t_real m_delta = 20;

  /**
   * @brief Get initial displacement
   *
   * @param i_x x-coordinate of the queried point.
   * @return displacement
   */
  t_real getDisplacement(t_real i_x) const;

  /**
   * @brief Get Bathymetry from CSV file
   *
   * @param i_x x-coordinate of the queried point.
   * @return bathymetry from csv
   */
  t_real getBathymetryFromCSV(t_real i_x) const;

public:
  /**
   * @brief Construct a new TsunamiEvent1d object
   *
   */
  TsunamiEvent1d();

  /**
   * Gets the water height.
   *
   * @param i_x x-coordinate of the queried point.
   * @return height of water.
   **/
  t_real getHeight(t_real i_x,
                   t_real) const;

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
   * @return bathymetry value
   */
  t_real getBathymetry(t_real i_x,
                       t_real) const;
};

#endif