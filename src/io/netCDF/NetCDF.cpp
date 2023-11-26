/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
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
  handleNetCdfError(nc_close(m_ncid), "Error closing netCDF file");
}

void tsunami_lab::io::NetCdf::netCdf(const std::string &filename,
                                     t_real i_dxy,
                                     t_idx i_nx,
                                     t_idx i_ny,
                                     t_real i_x_offset,
                                     t_real i_y_offset,
                                     t_real const *i_b)
{
  handleNetCdfError(nc_create(filename.c_str(), NC_CLOBBER, &m_ncid), "Error creat the NetCDF file: ");

  // Define the dimensions
  handleNetCdfError(nc_def_dim(m_ncid, "x", i_nx, &m_x_dimid), "Error define x dimension: ");
  handleNetCdfError(nc_def_dim(m_ncid, "y", i_ny, &m_y_dimid), "Error define y dimension: ");
  handleNetCdfError(nc_def_dim(m_ncid, "time", NC_UNLIMITED, &m_time_dimid), "Error define time dimension: ");

  // Define variables
  int dims[3] = {m_time_dimid, m_y_dimid, m_x_dimid};
  handleNetCdfError(nc_def_var(m_ncid, "x", NC_FLOAT, 1, &m_x_dimid, &m_x_varid), "Error define x variable: ");
  handleNetCdfError(nc_def_var(m_ncid, "y", NC_FLOAT, 1, &m_y_dimid, &m_y_varid), "Error define y variable: ");
  handleNetCdfError(nc_def_var(m_ncid, "time", NC_FLOAT, 1, &m_time_dimid, &m_time_varid), "Error define y variable: ");

  handleNetCdfError(nc_def_var(m_ncid, "height", NC_FLOAT, 3, dims, &m_h_varid), "Error define height variable:");
  handleNetCdfError(nc_def_var(m_ncid, "momentum_x", NC_FLOAT, 3, dims, &m_hu_varid), "Error define momentum_x variable:");
  handleNetCdfError(nc_def_var(m_ncid, "momentum_y", NC_FLOAT, 3, dims, &m_hv_varid), "Error define momentum_y variable:");

  int bathy_dims[2] = {m_y_dimid, m_x_dimid};
  handleNetCdfError(nc_def_var(m_ncid, "bathymetry", NC_FLOAT, 2, bathy_dims, &m_b_varid), "Error define bathymetry variable:");

  handleNetCdfError(nc_put_att_text(m_ncid, m_x_varid, "units", strlen("meter"), "meter"), "Error adding text x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_y_varid, "units", strlen("meter"), "meter"), "Error adding text x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_time_varid, "units", strlen("seconds"), "seconds"), "Error adding text x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_h_varid, "units", strlen("meter"), "meter"), "Error adding text height dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_hu_varid, "units", strlen("seconds"), "seconds"), "Error adding text momentum_x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_hv_varid, "units", strlen("seconds"), "seconds"), "Error adding text momentum_y dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_b_varid, "units", strlen("meter"), "meter"), "Error adding text bathymetry dimension");

  handleNetCdfError(nc_enddef(m_ncid), "Error end defining: ");

  // put y
  t_real *l_y = new t_real[i_ny];
  for (t_idx l_iy = 0; l_iy < i_ny; l_iy++)
  {
    l_y[l_iy] = (l_iy + 0.5) * i_dxy - i_y_offset;
  }
  handleNetCdfError(nc_put_var_float(m_ncid, m_y_varid, l_y), "Error put y variables: ");

  // put x
  t_real *l_x = new t_real[i_nx];
  for (t_idx l_ix = 0; l_ix < i_nx; l_ix++)
  {
    l_x[l_ix] = (l_ix + 0.5) * i_dxy - i_x_offset;
  }
  handleNetCdfError(nc_put_var_float(m_ncid, m_x_varid, l_x), "Error put x variables: ");

  handleNetCdfError(nc_put_var_float(m_ncid, m_b_varid, i_b), "Error put bathymetry variables: ");

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

  handleNetCdfError(nc_put_vara_float(m_ncid, m_h_varid, start, count, i_h), "Error put height variables: ");
  handleNetCdfError(nc_put_vara_float(m_ncid, m_hu_varid, start, count, i_hu), "Error put momentum_x variables: ");
  handleNetCdfError(nc_put_var1_float(m_ncid, m_time_varid, &timeStep, &i_time), "Error put time variables: ");

  handleNetCdfError(nc_put_vara_float(m_ncid, m_hv_varid, start, count, i_hv), "Error put momentum_y variables: ");
}

void tsunami_lab::io::NetCdf::read(t_idx &o_nx,
                                   t_idx &o_ny,
                                   t_real **o_x,
                                   t_real **o_y,
                                   t_real **o_z,
                                   const std::string filename)
{

  std::cout << "NetCDF:: Looking for file: " << filename << std::endl;
  t_idx l_nx, l_ny;

  handleNetCdfError(nc_open(filename.data(), NC_NOWRITE, &m_ncid), "Error open file: ");

  handleNetCdfError(nc_inq_dimid(m_ncid, "x", &m_x_varid), "Error getting y dimension id: ");
  handleNetCdfError(nc_inq_dimid(m_ncid, "y", &m_y_varid), "Error getting y dimension id: ");

  handleNetCdfError(nc_inq_dimlen(m_ncid, m_x_varid, &l_nx), "Error getting x dimension length: ");
  handleNetCdfError(nc_inq_dimlen(m_ncid, m_y_varid, &l_ny), "Error getting y dimension length: ");

  handleNetCdfError(nc_inq_varid(m_ncid, "x", &m_x_varid), "Error getting x value id: ");
  handleNetCdfError(nc_inq_varid(m_ncid, "y", &m_y_varid), "Error getting y value id:");
  handleNetCdfError(nc_inq_varid(m_ncid, "z", &m_z_varid), "Error getting z value id:");

  t_real *l_xv, *l_yv, *l_zv;
  l_xv = new t_real[l_nx];
  l_yv = new t_real[l_ny];
  l_zv = new t_real[l_nx * l_ny];

  handleNetCdfError(nc_get_var_float(m_ncid, m_x_varid, l_xv), "Error getting x value: ");
  handleNetCdfError(nc_get_var_float(m_ncid, m_y_varid, l_yv), "Error getting y value: ");
  handleNetCdfError(nc_get_var_float(m_ncid, m_z_varid, l_zv), "Error getting z value: ");

  o_nx = l_nx;
  o_ny = l_ny;
  *o_x = l_xv;
  *o_y = l_yv;
  *o_z = l_zv;

  delete[] l_xv;
  delete[] l_yv;
  delete[] l_zv;
}

void tsunami_lab::io::NetCdf::handleNetCdfError(int status, const std::string &errorMessage)
{
  if (status != NC_NOERR)
  {
    std::cerr << errorMessage << nc_strerror(status) << std::endl;
    exit(-1);
  }
}

tsunami_lab::t_real *tsunami_lab::io::NetCdf::removeGhostCells(const t_real *i_d,
                                                               t_idx i_nx,
                                                               t_idx i_ny,
                                                               t_idx i_ghostCellsX,
                                                               t_idx i_ghostCellsY,
                                                               t_idx i_stride)
{
  t_real *l_o = new t_real[i_nx * i_ny];

  for (t_idx l_x = i_ghostCellsX; l_x < i_nx + i_ghostCellsX; l_x++)
  {
    for (t_idx l_y = i_ghostCellsY; l_y < i_ny + i_ghostCellsY; l_y++)
    {
      t_idx l_id = l_y * i_stride + l_x;

      l_o[l_y * i_nx + l_x] = i_d[(l_id)];
    }
  }
  return l_o;
  delete[] l_o;
}
