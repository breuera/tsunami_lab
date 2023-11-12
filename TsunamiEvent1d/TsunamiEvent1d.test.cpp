/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/
#include <catch2/catch.hpp>
#include "TsunamiEvent1d.h"
#include <fstream>
#include "../io/Csv.h"

TEST_CASE( "Test the one-dimensional TsunamiEvent setup.", "[TsunamiSetup1d]" ) {

        tsunami_lab::t_real bathymetry[5];

    bathymetry[0] = 10.0;
    bathymetry[1] = 180000;
    bathymetry[2] = -100;
    bathymetry[3] = 2;
    bathymetry[4] = -300;

    tsunami_lab::t_real m_height = 0;
    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  bathymetry[0],
                                                    0.1,
                                                    m_height);

    REQUIRE( l_tsunami.getMomentumX( 0, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 0, 0 ) == Approx(20) );  
    REQUIRE( l_tsunami.getHeight( 0, 0 ) == Approx(0) );   

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  bathymetry[1],
                                                    0.1,
                                                    m_height);

    REQUIRE( l_tsunami.getMomentumX( 1, 0 ) == 0 );  
    REQUIRE( l_tsunami.getBathymetry( 1, 0 ) == Approx(180000) ); 
    REQUIRE( l_tsunami.getHeight( 1, 0 ) == Approx(0) );   

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  bathymetry[2],
                                                    0.1,
                                                    m_height);
 
    REQUIRE( l_tsunami.getMomentumX( 2, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 2, 0 ) == Approx(-100) );  
    REQUIRE( l_tsunami.getHeight( 2, 0 ) == Approx(100) );  

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  bathymetry[3],
                                                    0.1,
                                                    m_height);

    REQUIRE( l_tsunami.getMomentumX( 3, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 3, 0 ) == Approx(20) );  
    REQUIRE( l_tsunami.getHeight( 3, 0 ) == Approx(0) );  

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  bathymetry[4],
                                                    0.1,
                                                    m_height);

    REQUIRE( l_tsunami.getMomentumX( 4, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 4, 0 ) == Approx(-300) ); 
    REQUIRE( l_tsunami.getHeight( 4, 0 ) == Approx(300) );  

}

TEST_CASE( "Test the one-dimensional with dem.csv data.", "[DemTsunamiSetup1d]" ) {

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
    tsunami_lab::t_real m_height = 0;
  
    l_distance = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_bathymetry = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_x = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_y = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    tsunami_lab::t_real l_h_star = 0;

    tsunami_lab::io::Csv::read_gmt_states(  l_stream, 
                                            l_bathymetry, 
                                            l_x, 
                                            l_y, 
                                            l_distance,
                                            l_h_star);

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  l_bathymetry[0],
                                                    0.1,
                                                    m_height);
    REQUIRE( l_tsunami.getMomentumX( 0, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 0, 0 ) == Approx(-20) );  
    REQUIRE( l_tsunami.getHeight( 0, 0 ) == Approx(20) );  

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  l_bathymetry[100],
                                                    0.1,
                                                    m_height);
    REQUIRE( l_tsunami.getMomentumX( 100, 0 ) == 0 );  
    REQUIRE( l_tsunami.getBathymetry( 100, 0 ) == Approx(-127.975747046) ); 
    REQUIRE( l_tsunami.getHeight( 100, 0 ) == Approx(127.975747046) );  

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  l_bathymetry[800],
                                                    0.1,
                                                    m_height);
    REQUIRE( l_tsunami.getMomentumX( 800, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 800, 0 ) == Approx(-5115.21701793) );  
    REQUIRE( l_tsunami.getHeight( 800, 0 ) == Approx(5115.21701793) );  
 
    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  l_bathymetry[999],
                                                    0.1,
                                                    m_height);
    REQUIRE( l_tsunami.getMomentumX( 999, 0 ) == 0 );
    REQUIRE( l_tsunami.getBathymetry( 999, 0 ) == Approx(-6998.33542995) );  
    REQUIRE( l_tsunami.getHeight( 999, 0 ) == Approx(6998.33542995) );  

    tsunami_lab::setups::TsunamiEvent1d l_tsunami(  l_bathymetry[1762],
                                                    0.1,
                                                    m_height);
    REQUIRE( l_tsunami.getMomentumX( 1762, 0 ) == 0 ); 
    REQUIRE( l_tsunami.getBathymetry( 1762, 0 ) == Approx(-5533.77099898) ); 
    REQUIRE( l_tsunami.getHeight( 1762, 0 ) == Approx(5533.77099898) );   
}