/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional artificial-tsunami problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_ARTIFICIAL_TSUNAMI_2D_H
#define TSUNAMI_LAB_SETUPS_ARTIFICIAL_TSUNAMI_2D_H

#include "./../Setup.h"
#include <cmath>

namespace tsunami_lab
{
  namespace setups
  {
    class ArtificialTsunami2d;
  }
}

/**
 * 1d subcritical setup.
 **/
class tsunami_lab::setups::ArtificialTsunami2d : public Setup
{
private:
  //! wall heigth
  t_real m_delta = 20;

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
   * @brief Calculates and returns f(x)
   *
   * @param i_x x-coordinate of the queried point.
   */
  t_real f(t_real i_x,
           t_real) const
  {
    return std::sin(((i_x * 0.002) + 1) * M_PI);
  };

  /**
   * @brief Calculates and returns g(y)
   *
   * @param i_y y-coordinate of the queried point.
   */
  t_real g(t_real,
           t_real i_y) const
  {
    return (-1 * pow(i_y * 0.002, 2)) + 1;
  };

public:
  /**
   * Gets the water height.
   *
   * @return height of water.
   **/
  t_real getHeight(t_real,
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
   * @param i_y y-coordinate of the queried point.
   * @return bathymetry value
   */
  t_real getBathymetry(t_real i_x,
                       t_real i_y) const;
};

#endif