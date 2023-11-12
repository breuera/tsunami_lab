/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional tsunamievent problem.
 **/
#include <catch2/catch.hpp>
#include "TsunamiEvent1d.h"

TEST_CASE("Test the one-dimensional TsunamiEvent1d setup.", "[TsunamiEvent1d]")
{
  tsunami_lab::setups::TsunamiEvent1d l_tsunamievent_1d;

  // x in [8,12]
  REQUIRE(l_tsunamievent_1d.getHeight(10, 0) == 0.13f);

  REQUIRE(l_tsunamievent_1d.getMomentumX(10, 0) == 0.18f);

  REQUIRE(l_tsunamievent_1d.getMomentumY(10, 0) == 0);

  REQUIRE(l_tsunamievent_1d.getBathymetry(10, 0) == -0.13f);

  // x in [0,25] AND x notin [8,12]
  REQUIRE(l_tsunamievent_1d.getHeight(4, 0) == 0.33f);

  REQUIRE(l_tsunamievent_1d.getMomentumX(4, 0) == 0.18f);

  REQUIRE(l_tsunamievent_1d.getMomentumY(4, 0) == 0);

  REQUIRE(l_tsunamievent_1d.getBathymetry(4, 0) == -0.33f);

  // x > 25 (same for x < 0)
  REQUIRE(l_tsunamievent_1d.getHeight(30, 0) == 0);

  REQUIRE(l_tsunamievent_1d.getMomentumX(30, 0) == 0);

  REQUIRE(l_tsunamievent_1d.getMomentumY(30, 0) == 0);

  REQUIRE(l_tsunamievent_1d.getBathymetry(30, 0) == -0.33f);
}