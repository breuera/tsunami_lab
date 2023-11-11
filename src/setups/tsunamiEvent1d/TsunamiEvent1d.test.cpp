/**TsunamiEvent1d
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Tests the tsunamievent setup.
 **/
#include <catch2/catch.hpp>
#include "TsunamiEvent1d.h"
#include "../../io/Csv.h"

TEST_CASE("Test the one-dimensional tsunamievent setup.", "[TsunamiEvent1d]")
{
  rapidcsv::Document l_doc;
  size_t l_rowCount;
  tsunami_lab::io::Csv::openCSV("src/data/test.csv", l_doc, l_rowCount);

  // delta = 20
  // row = b_in < 0 and -b_in > delta and usage of getDisplacement
  tsunami_lab::t_real b_in_ltz_htd_gd = 247250;

  // row = b_in < 0 and -b_in > delta
  tsunami_lab::t_real b_in_ltz_htd = 5750.0072133;

  // row = b_in < 0 and -b_in < delta
  tsunami_lab::t_real b_in_ltz_ltd = 750.000973849;

  // b_in > 0 
  tsunami_lab::t_real b_in_gtz = 10750.01274;

  // b_in > 20
  tsunami_lab::t_real b_in_gtz_htd = 11000.01274;


  tsunami_lab::setups::TsunamiEvent1d l_tsunamievent(l_doc, l_rowCount);


  // row = b_in < 0 and -b_in > delta and usage of getDisplacement
  // bin = -7139.13368559
  REQUIRE(l_tsunamievent.getHeight(b_in_ltz_htd_gd, 0) == 7139.13368559f);

  REQUIRE(l_tsunamievent.getMomentumX(b_in_ltz_htd_gd, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumY(b_in_ltz_htd_gd, 0) == 0);

  // d = 2.2835087011066
  REQUIRE(l_tsunamievent.getBathymetry(b_in_ltz_htd_gd, 0) == -7136.850176888894f);


  // row = b_in < 0 and -b_in > delta
  // bin = -30.8495325326
  REQUIRE(l_tsunamievent.getHeight(b_in_ltz_htd, 0) == 30.8495325326f);

  REQUIRE(l_tsunamievent.getMomentumX(b_in_ltz_htd, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumY(b_in_ltz_htd, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(b_in_ltz_htd, 0) == -30.8495325326f);

  // row = b_in < 0 and -b_in < delta
  // bin = -7.00688893922
  REQUIRE(l_tsunamievent.getHeight(b_in_ltz_ltd, 0) == 20.0f);

  REQUIRE(l_tsunamievent.getMomentumX(b_in_ltz_ltd, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumY(b_in_ltz_ltd, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(b_in_ltz_ltd, 0) == -20.0f);

  // b_in = 1.0
  REQUIRE(l_tsunamievent.getHeight(b_in_gtz, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumX(b_in_gtz, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumY(b_in_gtz, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(b_in_gtz, 0) == 20.0f);

  // b_in = 25.0
  REQUIRE(l_tsunamievent.getHeight(b_in_gtz_htd, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumX(b_in_gtz_htd, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumY(b_in_gtz_htd, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(b_in_gtz_htd, 0) == 25.0f);

}