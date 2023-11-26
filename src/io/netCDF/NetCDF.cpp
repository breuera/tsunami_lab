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

tsunami_lab::io::NetCdf::~NetCdf()
{
  nc_close(m_ncid);
}

void tsunami_lab::io::NetCdf::netCDF(const std::string &filename,
                                     t_real i_dxy,
                                     t_idx i_nx,
                                     t_idx i_ny,
                                     t_real i_x_offset,
                                     t_real i_y_offset,
                                     t_real const *i_b)
{
  nc_create(filename.c_str(), NC_CLOBBER, &m_ncid);

  // Define the dimensions
  nc_def_dim(m_ncid, "x", i_nx, &m_x_dimid);
  nc_def_dim(m_ncid, "y", i_ny, &m_y_dimid);
  nc_def_dim(m_ncid, "time", NC_UNLIMITED, &m_time_dimid);

  // Define variables
  int dims[3] = {m_time_dimid, m_y_dimid, m_x_dimid};
  nc_def_var(m_ncid, "x", NC_FLOAT, 1, &m_x_dimid, &m_x_varid);
  nc_def_var(m_ncid, "y", NC_FLOAT, 1, &m_y_dimid, &m_y_varid);
  nc_def_var(m_ncid, "height", NC_FLOAT, 3, dims, &m_h_varid);
  nc_def_var(m_ncid, "momentum_x", NC_FLOAT, 3, dims, &m_hu_varid);
  nc_def_var(m_ncid, "momentum_y", NC_FLOAT, 3, dims, &m_hv_varid);

  int bathy_dims[2] = {m_y_dimid, m_x_dimid};
  nc_def_var(m_ncid, "bathymetry", NC_FLOAT, 2, bathy_dims, &m_b_varid);

  nc_enddef(m_ncid);

  // put y
  t_real *l_y = new t_real[i_ny];
  for (t_idx l_iy = 0; l_iy < i_ny; l_iy++)
  {
    l_y[l_iy] = (l_iy + 0.5) * i_dxy - i_y_offset;
  }
  nc_put_var_float(m_ncid, m_y_varid, l_y);

  // put x
  t_real *l_x = new t_real[i_nx];
  for (t_idx l_ix = 0; l_ix < i_nx; l_ix++)
  {
    l_x[l_ix] = (l_ix + 0.5) * i_dxy - i_x_offset;
  }
  nc_put_var_float(m_ncid, m_x_varid, l_x);

  nc_put_var_float(m_ncid, m_b_varid, i_b);

  delete[] l_x;
  delete[] l_y;
}

void tsunami_lab::io::NetCdf::write(t_idx i_nx,
                                    t_idx i_ny,
                                    t_real const *i_h,
                                    t_real const *i_hu,
                                    t_real const *i_hv,
                                    t_idx timeStep,
                                    t_real i_time)
{

  size_t start[3] = {timeStep, 0, 0};
  size_t count[3] = {1, i_ny, i_nx};

  nc_put_vara_float(m_ncid, m_h_varid, start, count, i_h);
  nc_put_vara_float(m_ncid, m_hu_varid, start, count, i_hu);
  nc_put_var1_float(m_ncid, m_time_dimid, &timeStep, &i_time);

  nc_put_vara_float(m_ncid, m_hv_varid, start, count, i_hv);
}
