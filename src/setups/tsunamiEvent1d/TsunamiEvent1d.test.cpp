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
  // todo: FIX THIS TEST
  // get rapidcsv::Document and row count from CSV file
  rapidcsv::Document l_doc;
  size_t l_rowCount;
  tsunami_lab::io::Csv::openCSV("../../data/data.csv", l_doc, l_rowCount);

  tsunami_lab::setups::TsunamiEvent1d l_tsunamievent(l_doc, l_rowCount);
  // x = 2
  REQUIRE(l_tsunamievent.getHeight(2, 0) == 0.33f);

  REQUIRE(l_tsunamievent.getMomentumX(2, 0) == 0.18f);

  REQUIRE(l_tsunamievent.getMomentumY(2, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(2, 0) == -0.33f);

  // x element of 8-12
  REQUIRE(l_tsunamievent.getHeight(10, 0) == 0.13f);

  REQUIRE(l_tsunamievent.getMomentumX(10, 0) == 0.18f);

  REQUIRE(l_tsunamievent.getMomentumY(4, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(10, 0) == -0.13f);

  // x element over 25

  REQUIRE(l_tsunamievent.getHeight(30, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumX(30, 0) == 0);

  REQUIRE(l_tsunamievent.getMomentumY(30, 0) == 0);

  REQUIRE(l_tsunamievent.getBathymetry(30, 0) == -0.33f);
}