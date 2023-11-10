/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional TSUNAMIEVENT problem.
 **/
#ifndef TSUNAMI_LAB_SETUPS_TSUNAMIEVENT_1D_H
#define TSUNAMI_LAB_SETUPS_TSUNAMIEVENT_1D_H

#include "../Setup.h"
#include <cmath>
#include <algorithm>
#include "../../io/Csv.h"
#include "../../io/rapidcsv.h"

namespace tsunami_lab
{
  namespace setups
  {
    class TsunamiEvent1d;
  }
}

/**
 * 1d TSUNAMIEVENT setup.
 **/
class tsunami_lab::setups::TsunamiEvent1d : public Setup
{
private:
  //! csv file as rapidcsv::Document
  rapidcsv::Document m_doc;

  //! row count of csv file
  size_t m_rowCount;

  //! delta for heights
  t_real m_delta = 20;

  /**
   * @brief Get the initial displacement
   *
   * @param i_x
   * @return displacement
   */
  t_real getDisplacement(t_real i_x) const;

  /**
   * @brief Get the Bathymetry of the CSV file
   *
   * @param i_x x-coordinate of the queried point. (length)
   * @return bathymetry
   */
  t_real getBathymetryBin(t_real i_x) const;

public:
  /**
   * @brief Construct a new TsunamiEvent1d object
   *
   * @param i_doc csv file as rapidcsv::Document
   * @param i_rowCount row count of csv file
   */
  TsunamiEvent1d(rapidcsv::Document i_doc, size_t i_rowCount);

  /**
   * Gets the water height at a given point.
   * @param i_x x-coordinate of the queried point.
   * @return height at the given point.
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
   * @param i_x x-coordinate of the queried point.
   * @return bathymetry
   */
  t_real getBathymetry(t_real i_x,
                       t_real) const;
};

#endif