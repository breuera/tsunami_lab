/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/
#include "TsunamiEvent1d.h"

#include <catch2/catch.hpp>
#include <fstream>

#include "../../io/Csv.h"

TEST_CASE("Test the one-dimensional TsunamiEvent setup.", "[TsunamiSetup1d]") {
    tsunami_lab::t_real bathymetry[5];

    bathymetry[0] = 10.0;
    bathymetry[1] = 180000;
    bathymetry[2] = -100;
    bathymetry[3] = 2;
    bathymetry[4] = -300;

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(0);

    REQUIRE(l_tsunami.getMomentumX(bathymetry[0], 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(bathymetry[0], 0) == Approx(20));
    REQUIRE(l_tsunami.getHeight(bathymetry[0], 0) == Approx(0));

    REQUIRE(l_tsunami.getMomentumX(bathymetry[1], 1) == 0);
    REQUIRE(l_tsunami.getBathymetry(bathymetry[1], 1) == Approx(180000));
    REQUIRE(l_tsunami.getHeight(bathymetry[1], 1) == Approx(0));

    REQUIRE(l_tsunami.getMomentumX(bathymetry[2], 2) == 0);
    REQUIRE(l_tsunami.getBathymetry(bathymetry[2], 2) == Approx(-100));
    REQUIRE(l_tsunami.getHeight(bathymetry[2], 2) == Approx(100));

    REQUIRE(l_tsunami.getMomentumX(bathymetry[3], 3) == 0);
    REQUIRE(l_tsunami.getBathymetry(bathymetry[3], 3) == Approx(20));
    REQUIRE(l_tsunami.getHeight(bathymetry[3], 3) == Approx(0));

    REQUIRE(l_tsunami.getMomentumX(bathymetry[4], 4) == 0);
    REQUIRE(l_tsunami.getBathymetry(bathymetry[4], 4) == Approx(-300));
    REQUIRE(l_tsunami.getHeight(bathymetry[4], 4) == Approx(300));
}

TEST_CASE("Test the one-dimensional with dem.csv data.", "[DemTsunamiSetup1d]") {
    // initialize middle state sanitization
    tsunami_lab::t_idx l_scenarioCount = 1000000;
    std::string filePath = "./res/dem.csv";

    std::ifstream l_stream;
    // try to read middle states original file
    std::cout << "reading /res/dem.csv ..." << std::endl;
    l_stream.open(filePath, std::fstream::in);

    float *l_distance;
    float *l_bathymetry;
    float *l_x;
    float *l_y;

    l_distance = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_bathymetry = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_x = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_y = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));

    tsunami_lab::io::Csv::read_gmt_states(l_stream,
                                          l_bathymetry,
                                          l_x,
                                          l_y,
                                          l_distance);

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(0);

    REQUIRE(l_tsunami.getMomentumX(l_bathymetry[0], 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(l_bathymetry[0], 0) == Approx(-20));
    REQUIRE(l_tsunami.getHeight(l_bathymetry[0], 0) == Approx(20));

    REQUIRE(l_tsunami.getMomentumX(l_bathymetry[100], 100) == 0);
    REQUIRE(l_tsunami.getBathymetry(l_bathymetry[100], 100) == Approx(-127.975747046));
    REQUIRE(l_tsunami.getHeight(l_bathymetry[100], 100) == Approx(127.975747046));

    REQUIRE(l_tsunami.getMomentumX(l_bathymetry[800], 800) == 0);
    REQUIRE(l_tsunami.getBathymetry(l_bathymetry[800], 800) == Approx(-5115.21701793));
    REQUIRE(l_tsunami.getHeight(l_bathymetry[800], 800) == Approx(5115.21701793));

    REQUIRE(l_tsunami.getMomentumX(l_bathymetry[999], 999) == 0);
    REQUIRE(l_tsunami.getBathymetry(l_bathymetry[999], 999) == Approx(-6998.33542995));
    REQUIRE(l_tsunami.getHeight(l_bathymetry[999], 999) == Approx(6998.33542995));

    REQUIRE(l_tsunami.getMomentumX(l_bathymetry[1762], 1762) == 0);
    REQUIRE(l_tsunami.getBathymetry(l_bathymetry[1762], 1762) == Approx(-5533.77099898));
    REQUIRE(l_tsunami.getHeight(l_bathymetry[1762], 1762) == Approx(5533.77099898));
}