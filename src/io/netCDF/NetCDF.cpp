/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#include "NetCDF.h"
#include <netcdf.h>
#include <vector>
#include <iostream>
#include <string>

void tsunami_lab::io::NetCdf::write(t_real i_dxy,
                                    t_idx i_nx,
                                    t_idx i_ny,
                                    t_real i_x_offset,
                                    t_real i_y_offset,
                                    t_real const *i_h,
                                    t_real const *i_hu,
                                    t_real const *i_hv,
                                    t_real const *i_b,
                                    const std::string &filename,
                                    t_idx timeStep)
{
  int ncid, x_dimid, y_dimid, time_dimid;
  int x_varid, y_varid, h_varid, hu_varid, hv_varid, b_varid;

  nc_create(filename.c_str(), NC_CLOBBER, &ncid);

  // Define the dimensions
  nc_def_dim(ncid, "x", i_nx, &x_dimid);
  nc_def_dim(ncid, "y", i_ny, &y_dimid);
  nc_def_dim(ncid, "time", NC_UNLIMITED, &time_dimid);

  nc_def_var(ncid, "x", NC_FLOAT, 1, &x_dimid, &x_varid);
  nc_def_var(ncid, "y", NC_FLOAT, 1, &y_dimid, &y_varid);

  // Define other variables
  int dims[3] = {time_dimid, y_dimid, x_dimid};
  nc_def_var(ncid, "height", NC_FLOAT, 3, dims, &h_varid);
  nc_def_var(ncid, "momentum_x", NC_FLOAT, 3, dims, &hu_varid);
  nc_def_var(ncid, "momentum_y", NC_FLOAT, 3, dims, &hv_varid);

  int bathy_dims[2] = {y_dimid, x_dimid};
  nc_def_var(ncid, "bathymetry", NC_FLOAT, 2, bathy_dims, &b_varid);

  // put y
  t_real *l_y = new t_real[i_ny];
  for (t_idx l_iy = 0; l_iy < i_ny; l_iy++)
  {
    l_y[l_iy] = (l_iy + 0.5) * i_dxy - i_y_offset;
  }
  nc_put_var_float(ncid, y_varid, l_y);

  // put x
  t_real *l_x = new t_real[i_nx];
  for (t_idx l_ix = 0; l_ix < i_nx; l_ix++)
  {
    l_x[l_ix] = (l_ix + 0.5) * i_dxy - i_x_offset;
  }
  nc_put_var_float(ncid, x_varid, l_x);

  nc_put_var_float(ncid, b_varid, i_b);

  size_t start[3] = {timeStep, 0, 0};
  size_t count[3] = {1, i_ny, i_nx};

  nc_put_vara_float(ncid, h_varid, start, count, i_h);
  nc_put_vara_float(ncid, hu_varid, start, count, i_hu);
  nc_put_vara_float(ncid, hv_varid, start, count, i_hv);

  nc_enddef(ncid);

  nc_close(ncid);
}
