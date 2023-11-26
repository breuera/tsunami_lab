/**
 origin/main
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for reading and writing NetCDF files.
 **/
#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../../constants.h"
#define private public
#include "NetCDF.h"
#undef public

TEST_CASE("Test the NetCDF read.", "[NetCDFRead]") {
    std::string l_bathymetryName = "dummy_bathymetry.nc";
    std::string l_displacementsName = "dummy_disp.nc";

    tsunami_lab::t_idx l_bathymetryDimX, l_bathymetryDimY, l_dispDimX, l_dispDimY;
    tsunami_lab::t_real *l_bathymetry;
    tsunami_lab::t_real *l_bathymetryPosX;
    tsunami_lab::t_real *l_bathymetryPosY;
    tsunami_lab::t_real *l_displacements;
    tsunami_lab::t_real *l_dispPosX;
    tsunami_lab::t_real *l_dispPosY;

    int l_error = tsunami_lab::io::NetCDF::read(l_bathymetryName,
                                                l_displacementsName,
                                                &l_bathymetryDimX,
                                                &l_bathymetryDimY,
                                                l_bathymetryPosX,
                                                l_bathymetryPosY,
                                                l_bathymetry,
                                                &l_dispDimX,
                                                &l_dispDimY,
                                                l_dispPosX,
                                                l_dispPosY,
                                                l_displacements);

    REQUIRE(l_error == 0);
    REQUIRE(l_bathymetryDimX == 5);
    REQUIRE(l_bathymetryDimY == 5);
    REQUIRE(l_dispDimX == 2);
    REQUIRE(l_dispDimY == 2);

    for (tsunami_lab::t_idx l_i = 0; l_i < l_bathymetryDimX; l_i++) {
        REQUIRE(l_bathymetryPosX[l_i] == l_i);
        REQUIRE(l_bathymetryPosY[l_i] == l_i);
    }

    for (tsunami_lab::t_idx l_i = 0; l_i < l_dispDimX; l_i++) {
        REQUIRE(l_dispPosX[l_i] == l_i + 2);
        REQUIRE(l_dispPosY[l_i] == l_i + 2);
    }

    float l_testBathymetry[25] = {0.7362, 1.2548, 2.7894, 0.6543, 3.9876,
                                  5.321, 4.5678, 2.3456, 1.1111, 0.9876,
                                  6.5432, 8.7654, 3.2109, 4.5678, 9.8765,
                                  2.3456, 1.2345, 7.8901, 5.4321, 0.1234,
                                  3.4567, 9.0123, 6.789, 8.9012, 4.321};

    for (tsunami_lab::t_idx l_i = 0; l_i < l_bathymetryDimX * l_bathymetryDimY; l_i++) {
        REQUIRE(l_bathymetry[l_i] == l_testBathymetry[l_i]);
    }

    float l_testDisplacements[4] = {0.7362, 1.2548,
                                    8.9012, 4.3210};

    for (tsunami_lab::t_idx l_i = 0; l_i < l_dispDimX * l_dispDimY; l_i++) {
        REQUIRE(l_displacements[l_i] == l_testDisplacements[l_i]);
    }

    delete[] l_bathymetryPosX;
    delete[] l_bathymetryPosY;
    delete[] l_dispPosX;
    delete[] l_dispPosY;
    delete[] l_bathymetry;
    delete[] l_displacements;
}
