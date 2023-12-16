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
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../../constants.h"
#define private public
#include "NetCDF.h"
#undef public

TEST_CASE("Test the NetCDF writer.", "[NetCDFWrite]") {
    // -1 == ghost cell
    tsunami_lab::t_real b[16] = {-1, -1, -1, -1,
                                 -1, 1, 2, -1,
                                 -1, 3, 4, -1,
                                 -1, -1, -1, -1};
    tsunami_lab::t_real h1[16] = {-1, -1, -1, -1, -1, 1, 2, -1, -1, 3, 4, -1, -1, -1, -1, -1};
    tsunami_lab::t_real hu1[16] = {-1, -1, -1, -1, -1, 1, 2, -1, -1, 3, 4, -1, -1, -1, -1, -1};
    tsunami_lab::t_real hv1[16] = {-1, -1, -1, -1, -1, 1, 2, -1, -1, 3, 4, -1, -1, -1, -1, -1};
    tsunami_lab::t_real h2[16] = {-1, -1, -1, -1, -1, 4, 3, -1, -1, 2, 1, -1, -1, -1, -1, -1};
    tsunami_lab::t_real hu2[16] = {-1, -1, -1, -1, -1, 4, 3, -1, -1, 2, 1, -1, -1, -1, -1, -1};
    tsunami_lab::t_real hv2[16] = {-1, -1, -1, -1, -1, 4, 3, -1, -1, 2, 1, -1, -1, -1, -1, -1};

    tsunami_lab::io::NetCDF *l_writer = new tsunami_lab::io::NetCDF(1.0, 0.02, 25, 1, 2, 2, 4, 1, b, "writer_test.nc");

    REQUIRE(l_writer->store(0.5, 0, h1, hu1, hv1) == NC_NOERR);
    REQUIRE(l_writer->store(1.0, 1, h2, hu2, hv2) == NC_NOERR);
    REQUIRE(l_writer->write() == NC_NOERR);

    int l_ncId;
    int l_varIDx, l_varIDy, l_varIDtime, l_varIDheight, l_varIDmomentumX, l_varIDmomentumY, l_varIDbathymetry;

    REQUIRE(nc_open("writer_test.nc", NC_NOWRITE, &l_ncId) == NC_NOERR);

    REQUIRE(nc_inq_varid(l_ncId, "x", &l_varIDx) == NC_NOERR);
    REQUIRE(nc_inq_varid(l_ncId, "y", &l_varIDy) == NC_NOERR);
    REQUIRE(nc_inq_varid(l_ncId, "time", &l_varIDtime) == NC_NOERR);
    REQUIRE(nc_inq_varid(l_ncId, "height", &l_varIDheight) == NC_NOERR);
    REQUIRE(nc_inq_varid(l_ncId, "momentum_x", &l_varIDmomentumX) == NC_NOERR);
    REQUIRE(nc_inq_varid(l_ncId, "momentum_y", &l_varIDmomentumY) == NC_NOERR);
    REQUIRE(nc_inq_varid(l_ncId, "bathymetry", &l_varIDbathymetry) == NC_NOERR);

    float l_dataX[2] = {0.5, 1.5};
    float l_dataY[2] = {0.5, 1.5};
    float l_dataTime[2] = {0.5, 1};
    float l_dataHeight[8] = {1, 2, 3, 4, 5, 5, 5, 5};
    float l_dataMomentumX[8] = {1, 2, 3, 4, 4, 3, 2, 1};
    float l_dataMomentumY[8] = {1, 2, 3, 4, 4, 3, 2, 1};
    float l_dataBathymetry[4] = {1, 2, 3, 4};

    float l_resultX[2];
    float l_resultY[2];
    float l_resultTime[2];
    float l_resultHeight[8];
    float l_resultMomentumX[8];
    float l_resultMomentumY[8];
    float l_resultBathymetry[4];

    REQUIRE(nc_get_var_float(l_ncId, l_varIDx, l_resultX) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataX[i] == l_resultX[i]);

    REQUIRE(nc_get_var_float(l_ncId, l_varIDy, l_resultY) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataY[i] == l_resultY[i]);

    REQUIRE(nc_get_var_float(l_ncId, l_varIDtime, l_resultTime) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataTime[i] == l_resultTime[i]);

    REQUIRE(nc_get_var_float(l_ncId, l_varIDheight, l_resultHeight) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataHeight[i] == l_resultHeight[i]);

    REQUIRE(nc_get_var_float(l_ncId, l_varIDmomentumX, l_resultMomentumX) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataMomentumX[i] == l_resultMomentumX[i]);

    REQUIRE(nc_get_var_float(l_ncId, l_varIDmomentumY, l_resultMomentumY) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataMomentumY[i] == l_resultMomentumY[i]);

    REQUIRE(nc_get_var_float(l_ncId, l_varIDbathymetry, l_resultBathymetry) == NC_NOERR);
    for (int i = 0; i < 2; i++) REQUIRE(l_dataBathymetry[i] == l_resultBathymetry[i]);

    std::remove("writer_test.nc");

    delete l_writer;
}

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
    REQUIRE(l_bathymetryDimY == 6);
    REQUIRE(l_dispDimX == 5);
    REQUIRE(l_dispDimY == 6);

    float l_testBathymetryPosX[5] = {-25, -15, 0, 15, 25};
    float l_testBathymetryPosY[6] = {-5, -3, 0, 15, 25, 35};

    for (tsunami_lab::t_idx l_i = 0; l_i < 5; l_i++) {
        REQUIRE(l_bathymetryPosX[l_i] == l_testBathymetryPosX[l_i]);
    }

    for (tsunami_lab::t_idx l_i = 0; l_i < 6; l_i++) {
        REQUIRE(l_bathymetryPosY[l_i] == l_testBathymetryPosY[l_i]);
    }

    float l_testDispPosX[5] = {-25, -15, 0, 15, 25};
    float l_testDispPosY[6] = {-5, -3, 0, 15, 25, 35};

    for (tsunami_lab::t_idx l_i = 0; l_i < 5; l_i++) {
        REQUIRE(l_dispPosX[l_i] == l_testDispPosX[l_i]);
    }
    for (tsunami_lab::t_idx l_i = 0; l_i < 6; l_i++) {
        REQUIRE(l_dispPosY[l_i] == l_testDispPosY[l_i]);
    }

    float l_testBathymetry[30] = {-400.0, -300.0, -200.0, -100.0, 0,
                                  -425.0, -350.0, -250.0, -150.0, -50.0,
                                  -350.0, -250.0, -150.0, -50.0, 0.0,
                                  -250.0, -150.0, -50.0, 50.0, 150.0,
                                  -150.0, -50.0, 50.0, 150.0, 225.0,
                                  -50.0, 50.0, 150.0, 225.0, 250.0};

    for (tsunami_lab::t_idx l_i = 0; l_i < 30; l_i++) {
        REQUIRE(l_bathymetry[l_i] == l_testBathymetry[l_i]);
    }

    float l_testDisplacements[30] = {0.0, 0.0, 0.0, 0.0, 0.0,
                                     0.0, 0.0, 0.0, 0.0, 0.0,
                                     0.0, 8.0, 4.0, -4.0, 0.0,
                                     0.0, -8.0, -6.0, -3.0, 0.0,
                                     0.0, 0.0, 0.0, 0.0, 0.0,
                                     0.0, 0.0, 0.0, 0.0, 0.0};

    for (tsunami_lab::t_idx l_i = 0; l_i < 30; l_i++) {
        REQUIRE(l_displacements[l_i] == l_testDisplacements[l_i]);
    }

    delete[] l_bathymetryPosX;
    delete[] l_bathymetryPosY;
    delete[] l_dispPosX;
    delete[] l_dispPosY;
    delete[] l_bathymetry;
    delete[] l_displacements;
}
