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
  rapidcsv::Document doc;
  t_real rowCount;
public:

  TsunamiEvent1d(const std::string& i_filePath) {
      try {
          io::Csv::openCSV(i_filePath, this->doc, this->rowCount);
      } catch (const std::exception& e) {
          std::cerr << "Error: " << e.what() << std::endl;
          throw;
      }
  }
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

  t_real getDisplacement(t_real i_x) const;

  t_real getBathymetryBin(t_real i_x) const;


};

#endif