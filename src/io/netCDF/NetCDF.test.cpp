/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for the NetCDF-interface.
 **/
#include "NetCDF.h"
#include <catch2/catch.hpp>
#include "../../constants.h"
#include <sstream>
#include <netcdf.h>
#include <filesystem>
#define private public
#undef public

TEST_CASE("Test the NetCDF-writer for 2D settings.", "[NetCDFWrite2d]")
{

    if (std::filesystem::exists("netCDF_dump"))
    {
        std::filesystem::remove_all("netCDF_dump");
    }

    // create csv_dump folder
    std::filesystem::create_directory("netCDF_dump");

    tsunami_lab::io::NetCdf *writer = nullptr;

    writer = new tsunami_lab::io::NetCdf();

    // define a simple example
    tsunami_lab::t_real l_b[16] = {15, 14, 13, 12,
                                   11, 10, 9, 8,
                                   7, 6, 5, 4,
                                   3, 2, 1, 0};

    writer->netCdf("netCDF_dump/netCDFdump.nc",
                   1,
                   4,
                   4,
                   0,
                   0,
                   l_b);

    tsunami_lab::t_real l_h[16] = {0, 1, 2, 3,
                                   4, 5, 6, 7,
                                   8, 9, 10, 11,
                                   12, 13, 14, 15};
    tsunami_lab::t_real l_hu[16] = {31, 30, 29, 28,
                                    27, 26, 25, 24,
                                    23, 22, 21, 20,
                                    19, 18, 17, 16};
    tsunami_lab::t_real l_hv[16] = {0, 4, 8, 12,
                                    1, 5, 9, 13,
                                    2, 6, 10, 14,
                                    3, 7, 11, 15};
    writer->write(4,
                  4,
                  l_h,
                  l_hu,
                  l_hv,
                  0,
                  0.2);

    for (int i = 0; i < 16; i++)
    {
        l_h[i] += 16;
        l_hu[i] -= 16;
        l_hv[i] += 16;
    }

    writer->write(4,
                  4,
                  l_h,
                  l_hu,
                  l_hv,
                  1,
                  1.8);
    delete writer;

    REQUIRE(std::filesystem::exists("netCDF_dump/netCDFdump.nc"));

    int l_ncid, l_x_dimid, l_y_dimid, l_time_dimid;
    int l_x_varid, l_y_varid, l_h_varid, l_hu_varid, l_hv_varid, l_b_varid;

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_open("netCDF_dump/netCDFdump.nc", NC_NOWRITE, &l_ncid), "Error opening the NetCDF file: ");

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_dimid(l_ncid, "x", &l_x_dimid), "Error getting x dimension: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_dimid(l_ncid, "y", &l_y_dimid), "Error getting y dimension: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_dimid(l_ncid, "time", &l_time_dimid), "Error getting time dimension: ");

    size_t l_nx, l_ny, l_time;
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_dimlen(l_ncid, l_x_dimid, &l_nx), "Error getting x dimension length: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_dimlen(l_ncid, l_y_dimid, &l_ny), "Error getting y dimension length: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_dimlen(l_ncid, l_time_dimid, &l_time), "Error getting y dimension length: ");

    REQUIRE(l_nx == 4);
    REQUIRE(l_ny == 4);
    REQUIRE(l_time == 2);

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_varid(l_ncid, "x", &l_x_varid), "Error getting x variable: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_varid(l_ncid, "y", &l_y_varid), "Error getting y variable: ");

    tsunami_lab::t_real *l_xt = new tsunami_lab::t_real[4];
    tsunami_lab::t_real *l_yt = new tsunami_lab::t_real[4];

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_get_var_float(l_ncid, l_x_varid, l_xt), "Error getting x value: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_get_var_float(l_ncid, l_y_varid, l_yt), "Error getting y value: ");

    for (int i = 0; i < 4; i++)
    {
        REQUIRE(l_xt[i] == i + 0.5);
        REQUIRE(l_yt[i] == i + 0.5);
    }

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_varid(l_ncid, "bathymetry", &l_b_varid), "Error getting bathymetry variable: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_varid(l_ncid, "height", &l_h_varid), "Error getting height variable: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_varid(l_ncid, "momentum_x", &l_hu_varid), "Error getting momentum_x variable: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_inq_varid(l_ncid, "momentum_y", &l_hv_varid), "Error getting momentum_y variable: ");

    tsunami_lab::t_real *l_bt = new tsunami_lab::t_real[16];
    tsunami_lab::t_real *l_ht = new tsunami_lab::t_real[32];
    tsunami_lab::t_real *l_hut = new tsunami_lab::t_real[32];
    tsunami_lab::t_real *l_hvt = new tsunami_lab::t_real[32];

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_get_var_float(l_ncid, l_b_varid, l_bt), "Error getting x value: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_get_var_float(l_ncid, l_h_varid, l_ht), "Error getting y value: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_get_var_float(l_ncid, l_hu_varid, l_hut), "Error getting x value: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_get_var_float(l_ncid, l_hv_varid, l_hvt), "Error getting y value: ");

    for (int i = 0; i < 16; i++)
    {
        REQUIRE(l_bt[i] == 15 - i);
    }

    for (int i = 0; i < 32; i++)
    {
        REQUIRE(l_ht[i] == i);
        REQUIRE(l_hut[i] == 31 - i);
    }

    // ToDo:
    /*
     int count = 0;
    for (int j = 0; j < 16; j++)
    {
        for (int k = 0; k < 17; k += 4)
        {
            REQUIRE(l_hvt[count] == k + j);
            count++;
        }
    }*/

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_close(l_ncid), "Error closing the NetCDF file: ");

    delete[] l_xt;
    delete[] l_yt;
    delete[] l_bt;
    delete[] l_ht;
    delete[] l_hut;
    delete[] l_hvt;
}