/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional tsunamievent problem.
 **/
#include <catch2/catch.hpp>
#include "TsunamiEvent1d.h"
#include "./../../io/csv/Csv.h"

TEST_CASE("Test the one-dimensional TsunamiEvent1d setup.", "[TsunamiEvent1d]")
{
    std::vector<tsunami_lab::t_real> m_b_in;
    tsunami_lab::io::Csv::read("data/real.csv", m_b_in);

    tsunami_lab::t_real beginning = 10;

    // b_in < 0 and -b_in > delta
    tsunami_lab::t_real middle = 150000;

    // b_in > 20
    tsunami_lab::t_real end = 375000;

    tsunami_lab::setups::TsunamiEvent1d l_tsunamievent(m_b_in);

    //
    REQUIRE(l_tsunamievent.getHeight(beginning, 0) == 20.0f);

    REQUIRE(l_tsunamievent.getMomentumX(beginning, 0) == 0);

    REQUIRE(l_tsunamievent.getMomentumY(beginning, 0) == 0);

    REQUIRE(l_tsunamievent.getBathymetry(beginning, 0) == -20.0f);

    //
    REQUIRE(l_tsunamievent.getHeight(middle, 0) == Approx(2337.15381f));

    REQUIRE(l_tsunamievent.getMomentumX(middle, 0) == 0);

    REQUIRE(l_tsunamievent.getMomentumY(middle, 0) == 0);

    REQUIRE(l_tsunamievent.getBathymetry(middle, 0) == Approx(-2337.15381f));

    //
    REQUIRE(l_tsunamievent.getHeight(end, 0) == Approx(5675.89795f));

    REQUIRE(l_tsunamievent.getMomentumX(end, 0) == 0);

    REQUIRE(l_tsunamievent.getMomentumY(end, 0) == 0);

    REQUIRE(l_tsunamievent.getBathymetry(end, 0) == Approx(-5675.89795f));
}