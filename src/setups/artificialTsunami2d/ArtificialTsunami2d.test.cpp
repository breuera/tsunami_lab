/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional artificial-tsunami problem.
 **/
#include <catch2/catch.hpp>
#include "ArtificialTsunami2d.h"
#include "./../../io/csv/Csv.h"

TEST_CASE("Test the one-dimensional ArtificialTsunami2d setup.", "[ArtificialTsunami2d]")
{

    tsunami_lab::setups::ArtificialTsunami2d l_tsunamievent;

    // x or y not in [-500, 500]
    REQUIRE(l_tsunamievent.getHeight(501, 0) == 100);
    REQUIRE(l_tsunamievent.getMomentumX(501, 0) == 0);
    REQUIRE(l_tsunamievent.getMomentumY(501, 0) == 0);
    REQUIRE(l_tsunamievent.getBathymetry(501, 0) == -100);

    REQUIRE(l_tsunamievent.getHeight(0, 501) == 100);
    REQUIRE(l_tsunamievent.getMomentumX(0, 501) == 0);
    REQUIRE(l_tsunamievent.getMomentumY(0, 501) == 0);
    REQUIRE(l_tsunamievent.getBathymetry(0, 501) == -100);

    /**
     * x = y = 0
     * f(x) = sin(pi)  = 0
     * g(y) = 0 + 1 = 1
     * d(x,y) = 0
     */
    REQUIRE(l_tsunamievent.getHeight(0, 0) == 100);
    REQUIRE(l_tsunamievent.getMomentumX(0, 0) == 0);
    REQUIRE(l_tsunamievent.getMomentumY(0, 0) == 0);
    REQUIRE(l_tsunamievent.getBathymetry(0, 0) == -100);

    /**
     * x = y = 100
     * f(x) = −0.58778525229251
     * g(x) = 0.96
     * d(x,y) = −2.821369211004
     */
    REQUIRE(l_tsunamievent.getHeight(100, 100) == 100);
    REQUIRE(l_tsunamievent.getMomentumX(100, 100) == 0);
    REQUIRE(l_tsunamievent.getMomentumY(100, 100) == 0);
    REQUIRE(l_tsunamievent.getBathymetry(100, 100) == Approx(-102.821369211004));
}