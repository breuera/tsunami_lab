/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Artificial two-dimensional tsunami event test.
 **/
#include "ArtificialTsunami2d.h"

#include <catch2/catch.hpp>

TEST_CASE("Test the two-dimensional artificial tsunami setup.", "[ArtificialTsunami2d]") {
    tsunami_lab::setups::ArtificialTsunami2d l_artificialTsunami(10000,
                                                                 10000);

    // normal case / no displacement (x/y out of range)
    REQUIRE(l_artificialTsunami.getHeight(3210, 7952) == 100);
    REQUIRE(l_artificialTsunami.getMomentumX(3210, 7952) == 0);
    REQUIRE(l_artificialTsunami.getMomentumY(3210, 7952) == 0);
    REQUIRE(l_artificialTsunami.getBathymetry(3210, 7952) == -100);

    // normal case / no displacement (x in range, y out of range)
    REQUIRE(l_artificialTsunami.getHeight(5214, 1468) == 100);
    REQUIRE(l_artificialTsunami.getMomentumX(5214, 1468) == 0);
    REQUIRE(l_artificialTsunami.getMomentumY(5214, 1468) == 0);
    REQUIRE(l_artificialTsunami.getBathymetry(5214, 1468) == -100);

    // normal case / no displacement (x out of range, y in range)
    REQUIRE(l_artificialTsunami.getHeight(2974, 5896) == 100);
    REQUIRE(l_artificialTsunami.getMomentumX(2974, 5896) == 0);
    REQUIRE(l_artificialTsunami.getMomentumY(2974, 5896) == 0);
    REQUIRE(l_artificialTsunami.getBathymetry(2974, 5896) == -100);

    // x/y in range of bathymetry displacement
    REQUIRE(l_artificialTsunami.getHeight(5400, 4600) == 100);
    REQUIRE(l_artificialTsunami.getMomentumX(5400, 4600) == 0);
    REQUIRE(l_artificialTsunami.getMomentumY(5400, 4600) == 0);
    REQUIRE(l_artificialTsunami.getBathymetry(5400, 4600) == Approx(145.81));
    // wolfram alpha: 5 * sin(((5400 / 500) + 1) * pi) * (-(4600 / 500)^2 + 1) = 245.81179250871...
    // -100 + 245.81179250871... = 145.811792508712...
}