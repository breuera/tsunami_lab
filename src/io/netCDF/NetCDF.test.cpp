/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing and reading large data
 *
 **/
#include "NetCDF.h"
#include <catch2/catch.hpp>
#include "../../constants.h"
#include <sstream>
#include <netcdf.h>
#include <filesystem>
#include <iostream>
#define private public
#undef public

TEST_CASE("Test the NetCDF-writer.", "[NetCDFWrite2d]")
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

    writer->initialize("netCDF_dump/netCDFdump.nc",
                       1,
                       4,
                       4,
                       0,
                       0,
                       writer->removeGhostCells(l_b, 4, 4, 0, 0, 4));

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
                  writer->removeGhostCells(l_h, 4, 4, 0, 0, 4),
                  writer->removeGhostCells(l_hu, 4, 4, 0, 0, 4),
                  writer->removeGhostCells(l_hv, 4, 4, 0, 0, 4),
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
                  writer->removeGhostCells(l_h, 4, 4, 0, 0, 4),
                  writer->removeGhostCells(l_hu, 4, 4, 0, 0, 4),
                  writer->removeGhostCells(l_hv, 4, 4, 0, 0, 4),
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

    tsunami_lab::t_real l_thvt[32] = {0, 4, 8, 12,
                                      1, 5, 9, 13,
                                      2, 6, 10, 14,
                                      3, 7, 11, 15,
                                      16, 20, 24, 28,
                                      17, 21, 25, 29,
                                      18, 22, 26, 30,
                                      19, 23, 27, 31};
    for (int i = 0; i < 32; i++)
    {
        REQUIRE(l_ht[i] == i);
        REQUIRE(l_hut[i] == 31 - i);
        REQUIRE(l_hvt[i] == l_thvt[i]);
    }

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_close(l_ncid), "Error closing the NetCDF file: ");

    delete[] l_xt;
    delete[] l_yt;
    delete[] l_bt;
    delete[] l_ht;
    delete[] l_hut;
    delete[] l_hvt;
}

TEST_CASE("Test the NetCDF-reader.", "[NetCDFRead2d]")
{

    int l_ncid, l_x_dimid, l_y_dimid;
    int l_x_varid, l_y_varid, l_z_varid;

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_create("test.nc", NC_CLOBBER, &l_ncid), "Error creat the NetCDF file: ");

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_def_dim(l_ncid, "x", 10, &l_x_dimid), "Error define x dimension: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_def_dim(l_ncid, "y", 10, &l_y_dimid), "Error define y dimension: ");

    int dims[2] = {l_y_dimid, l_x_dimid};
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_def_var(l_ncid, "x", NC_FLOAT, 1, &l_x_dimid, &l_x_varid), "Error define x variable: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_def_var(l_ncid, "y", NC_FLOAT, 1, &l_y_dimid, &l_y_varid), "Error define y variable: ");

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_def_var(l_ncid, "z", NC_FLOAT, 1, dims, &l_z_varid), "Error define y variable: ");

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_enddef(l_ncid), "Error end defining: ");

    tsunami_lab::t_real *l_y = new tsunami_lab::t_real[10];
    for (int i = 0; i < 10; i++)
    {
        l_y[i] = i;
    }
    tsunami_lab::t_real *l_x = new tsunami_lab::t_real[10];
    for (int i = 0; i < 10; i++)
    {
        l_x[i] = 9 - i;
    }
    tsunami_lab::t_real *l_z = new tsunami_lab::t_real[10];
    for (int i = 0; i < 10; i++)
    {
        l_z[i] = i * 10;
    }
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_put_var_float(l_ncid, l_y_varid, l_y), "Error put y variables: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_put_var_float(l_ncid, l_x_varid, l_x), "Error put x variables: ");
    tsunami_lab::io::NetCdf::handleNetCdfError(nc_put_var_float(l_ncid, l_z_varid, l_z), "Error put z variables: ");

    tsunami_lab::io::NetCdf::handleNetCdfError(nc_close(l_ncid), "Error closing netCDF file");

    tsunami_lab::io::NetCdf *netCDF = nullptr;

    netCDF = new tsunami_lab::io::NetCdf();

    tsunami_lab::t_idx l_nxv;
    tsunami_lab::t_idx l_nyv;
    tsunami_lab::t_real *l_xv;
    tsunami_lab::t_real *l_yv;
    tsunami_lab::t_real *l_zv;

    netCDF->read(&l_nxv, &l_nyv, &l_xv, &l_yv, &l_zv, "test.nc");

    REQUIRE(l_nxv == 10);
    REQUIRE(l_nyv == 10);
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(l_xv[i] == 9 - i);
        REQUIRE(l_yv[i] == i);
        REQUIRE(l_zv[i] == i * 10);
    }

    delete[] l_xv;
    delete[] l_yv;
    delete[] l_zv;
    delete[] l_x;
    delete[] l_y;
    delete[] l_z;
    delete netCDF;
    std::filesystem::remove_all("test.nc");
}

TEST_CASE("Test the NetCDF-checkpoint_reader.", "[NetCDFReadCheckpoint]")
{
    tsunami_lab::io::NetCdf *checkpoint = nullptr;

    checkpoint = new tsunami_lab::io::NetCdf();

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

    tsunami_lab::t_real l_b[16] = {15, 14, 13, 12,
                                   11, 10, 9, 8,
                                   7, 6, 5, 4,
                                   3, 2, 1, 0};

    checkpoint->writeCheckpoint(4,
                                4,
                                l_h,
                                l_hu,
                                l_hv,
                                l_b,
                                0,
                                0,
                                1,
                                1,
                                1,
                                1,
                                1,
                                200,
                                36000,
                                500,
                                16000,
                                20,
                                1,
                                15);
    tsunami_lab::t_idx l_nx;
    tsunami_lab::t_idx l_ny;
    tsunami_lab::t_real *l_h1;
    tsunami_lab::t_real *l_hu1;
    tsunami_lab::t_real *l_hv1;
    tsunami_lab::t_real *l_b1;
    tsunami_lab::t_real l_x_offset;
    tsunami_lab::t_real l_y_offset;
    int l_solver_choice;
    int l_state_boundary_left;
    int l_state_boundary_right;
    int l_state_boundary_top;
    int l_state_boundary_bottom;
    tsunami_lab::t_real l_width;
    tsunami_lab::t_real l_endTime;
    tsunami_lab::t_idx l_timeStep;
    tsunami_lab::t_real l_time;
    tsunami_lab::t_idx l_nOut;
    tsunami_lab::t_real l_hMax;
    tsunami_lab::t_idx l_simulated_frame;

    checkpoint->readCheckpoint(&l_nx,
                               &l_ny,
                               &l_h1,
                               &l_hu1,
                               &l_hv1,
                               &l_b1,
                               &l_x_offset,
                               &l_y_offset,
                               &l_solver_choice,
                               &l_state_boundary_left,
                               &l_state_boundary_right,
                               &l_state_boundary_top,
                               &l_state_boundary_bottom,
                               &l_width,
                               &l_endTime,
                               &l_timeStep,
                               &l_time,
                               &l_nOut,
                               &l_hMax,
                               &l_simulated_frame,
                               "checkpoints/checkpoint_1.nc");
    REQUIRE(l_nx == 4);
    REQUIRE(l_ny == 4);
    REQUIRE(l_x_offset == 0);
    REQUIRE(l_y_offset == 0);
    REQUIRE(l_solver_choice == 1);
    REQUIRE(l_state_boundary_left == 1);
    REQUIRE(l_state_boundary_right == 1);
    REQUIRE(l_state_boundary_top == 1);
    REQUIRE(l_state_boundary_bottom == 1);
    REQUIRE(l_width == 200);
    REQUIRE(l_endTime == 36000);
    REQUIRE(l_timeStep == 500);
    REQUIRE(l_time == 16000);
    REQUIRE(l_nOut == 20);
    REQUIRE(l_hMax == 1);
    REQUIRE(l_simulated_frame == 15);

    // Verify the values read from the checkpoint for each array
    for (tsunami_lab::t_idx i = 0; i < 16; ++i)
    {
        REQUIRE(l_h1[i] == l_h[i]);
        REQUIRE(l_hu1[i] == l_hu[i]);
        REQUIRE(l_hv1[i] == l_hv[i]);
        REQUIRE(l_b1[i] == l_b[i]);
    }

    // Clean up dynamically allocated memory
    delete[] l_h1;
    delete[] l_hu1;
    delete[] l_hv1;
    delete[] l_b1;

    // Clean up the checkpoint object
    delete checkpoint;
}
