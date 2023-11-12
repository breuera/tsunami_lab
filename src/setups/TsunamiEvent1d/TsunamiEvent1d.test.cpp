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

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(bathymetry);

    REQUIRE(l_tsunami.getMomentumX(0, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(0, 0) == Approx(20));
    REQUIRE(l_tsunami.getHeight(0, 0) == Approx(0));

    REQUIRE(l_tsunami.getMomentumX(250, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(250, 0) == Approx(180000));
    REQUIRE(l_tsunami.getHeight(250, 0) == Approx(0));

    REQUIRE(l_tsunami.getMomentumX(500, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(500, 0) == Approx(-100));
    REQUIRE(l_tsunami.getHeight(500, 0) == Approx(100));

    REQUIRE(l_tsunami.getMomentumX(750, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(750, 0) == Approx(20));
    REQUIRE(l_tsunami.getHeight(750, 0) == Approx(0));

    REQUIRE(l_tsunami.getMomentumX(1000, 0) == 0);
    REQUIRE(l_tsunami.getBathymetry(1000, 0) == Approx(-300));
    REQUIRE(l_tsunami.getHeight(1000, 0) == Approx(300));
}

TEST_CASE("Test the one-dimensional with dem.csv data.", "[DemTsunamiSetup1d]") {
    // initialize middle state sanitization
    tsunami_lab::t_idx l_scenarioCount = 1763;
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
}