/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional Tsunami Event test.
 **/
#include "TsunamiEvent2d.h"

#include <catch2/catch.hpp>
#include <fstream>

#include "../../io/Csv/Csv.h"

TEST_CASE("Test the one-dimensional with dem.csv data.", "[DemTsunamiSetup1d]") {
    std::string filePath = "./res/dem.csv";

    std::ifstream l_stream;
    // read bathymetry original file
    std::cout << "reading /res/dem.csv ..." << std::endl;
    l_stream.open(filePath, std::fstream::in);
    REQUIRE(!l_stream.fail());

    float *l_distance = nullptr;
    float *l_bathymetry = nullptr;
    float *l_x = nullptr;
    float *l_y = nullptr;

    tsunami_lab::io::Csv::read_gmt_states(l_stream,
                                          l_bathymetry,
                                          l_x,
                                          l_y,
                                          l_distance);

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(l_bathymetry);

    REQUIRE(l_tsunami.getMomentumX(0, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(0, 0) == Approx(-20));
    REQUIRE(l_tsunami.getHeight(0, 0) == Approx(20));

    REQUIRE(l_tsunami.getMomentumX(25000, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(25000, 0) == Approx(-127.975747046));
    REQUIRE(l_tsunami.getHeight(25000, 0) == Approx(127.975747046));

    REQUIRE(l_tsunami.getMomentumX(200000, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(200000, 0) == Approx(-5123.87695f));
    REQUIRE(l_tsunami.getHeight(200000, 0) == Approx(5115.21701793));

    REQUIRE(l_tsunami.getMomentumX(249750, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(249750, 0) == Approx(-6998.12598));
    REQUIRE(l_tsunami.getHeight(249750, 0) == Approx(6998.33542995));

    REQUIRE(l_tsunami.getMomentumX(440500, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(440500, 0) == Approx(-5533.77099898));
    REQUIRE(l_tsunami.getHeight(440500, 0) == Approx(5533.77099898));

    delete[] l_bathymetry;
    delete[] l_distance;
    delete[] l_x;
    delete[] l_y;
}