/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing and reading large data
 *
 **/
#include "NetCDF.h"
#include <netcdf.h>
#include <iostream>
#include <string>
#include <filesystem>

tsunami_lab::io::NetCdf::~NetCdf()
{
  if (m_ncid != -1)
  {
    // handleNetCdfError(nc_close(m_ncid), "Error closing netCDF file: ");
  }
}

void tsunami_lab::io::NetCdf::initialize(const std::string &filename,
                                         t_real i_dxy,
                                         t_idx i_nx,
                                         t_idx i_ny,
                                         int i_resolution_div,
                                         t_real i_x_offset,
                                         t_real i_y_offset,
                                         t_real const *i_b)
{
  m_out_file_name = filename;

  handleNetCdfError(nc_create(m_out_file_name.c_str(), NC_CLOBBER, &m_ncid), "Error creat the NetCDF file: ");

  // Define the dimensions
  t_idx new_nx = i_nx / i_resolution_div;
  t_idx new_ny = i_ny / i_resolution_div;
  handleNetCdfError(nc_def_dim(m_ncid, "x", new_nx, &m_x_dimid), "Error define x dimension: ");
  handleNetCdfError(nc_def_dim(m_ncid, "y", new_ny, &m_y_dimid), "Error define y dimension: ");
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

  handleNetCdfError(nc_put_att_text(m_ncid, m_x_varid, "units", 5, "meter"), "Error adding text x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_y_varid, "units", 5, "meter"), "Error adding text y dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_time_varid, "units", 7, "seconds"), "Error adding text x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_h_varid, "units", 5, "meter"), "Error adding text height dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_hu_varid, "units", 14, "newton-seconds"), "Error adding text momentum_x dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_hv_varid, "units", 14, "newton-seconds"), "Error adding text momentum_y dimension");
  handleNetCdfError(nc_put_att_text(m_ncid, m_b_varid, "units", 5, "meter"), "Error adding text bathymetry dimension");

  handleNetCdfError(nc_enddef(m_ncid), "Error end defining: ");

  // put y
  t_real *l_y = new t_real[new_ny];
  for (t_idx l_iy = 0; l_iy < new_ny; l_iy++)
  {
    l_y[l_iy] = (l_iy + 0.5) * i_dxy * i_resolution_div - i_y_offset;
  }
  handleNetCdfError(nc_put_var_float(m_ncid, m_y_varid, l_y), "Error put y variables: ");

  // put x
  t_real *l_x = new t_real[new_nx];
  for (t_idx l_ix = 0; l_ix < new_nx; l_ix++)
  {
    l_x[l_ix] = (l_ix + 0.5) * i_dxy * i_resolution_div - i_x_offset;
  }
  handleNetCdfError(nc_put_var_float(m_ncid, m_x_varid, l_x), "Error put x variables: ");

  t_real *scaled_b = scaleDownArray(i_b, i_nx, i_ny, i_resolution_div);
  handleNetCdfError(nc_put_var_float(m_ncid, m_b_varid, scaled_b), "Error put bathymetry variables: ");

  handleNetCdfError(nc_close(m_ncid), "Error closing in init: ");

  delete[] l_x;
  delete[] l_y;
  delete[] scaled_b;
  delete[] i_b;
}

void tsunami_lab::io::NetCdf::write(t_idx i_nx,
                                    t_idx i_ny,
                                    int i_resolution_div,
                                    t_real const *i_h,
                                    t_real const *i_hu,
                                    t_real const *i_hv,
                                    t_idx timeStep,
                                    t_real i_time)
{

  handleNetCdfError(nc_open(m_out_file_name.c_str(), NC_WRITE, &m_ncid), "Error opening in write: ");

  size_t start[3] = {timeStep, 0, 0};
  size_t count[3] = {1, i_ny / i_resolution_div, i_nx / i_resolution_div};

  t_real *scaled_h = scaleDownArray(i_h, i_nx, i_ny, i_resolution_div);
  t_real *scaled_hu = scaleDownArray(i_hu, i_nx, i_ny, i_resolution_div);
  t_real *scaled_hv = scaleDownArray(i_hv, i_nx, i_ny, i_resolution_div);

  handleNetCdfError(nc_put_vara_float(m_ncid, m_h_varid, start, count, scaled_h), "Error put height variables: ");
  handleNetCdfError(nc_put_vara_float(m_ncid, m_hu_varid, start, count, scaled_hu), "Error put momentum_x variables: ");
  handleNetCdfError(nc_put_var1_float(m_ncid, m_time_varid, &timeStep, &i_time), "Error put time variables: ");
  handleNetCdfError(nc_put_vara_float(m_ncid, m_hv_varid, start, count, scaled_hv), "Error put momentum_y variables: ");

  handleNetCdfError(nc_close(m_ncid), "Error closing in write: ");

  delete[] scaled_h;
  delete[] scaled_hu;
  delete[] scaled_hv;

  // freeing memory because "removeGhostCells"-function return these,
  // they are not saved in a variable so this is the only time they
  // can be deleted
  delete[] i_h;
  delete[] i_hu;
  delete[] i_hv;
}

tsunami_lab::t_real *tsunami_lab::io::NetCdf::scaleDownArray(t_real const *i_array,
                                                             t_idx i_nx,
                                                             t_idx i_ny,
                                                             int i_resolution_div)
{
  t_idx new_nx = i_nx / i_resolution_div;
  t_idx new_ny = i_ny / i_resolution_div;
  t_real *new_array = new t_real[new_nx * new_ny];

  for (t_idx j = 0; j < new_ny; ++j)
  {
    for (t_idx i = 0; i < new_nx; ++i)
    {
      t_real sum = 0;
      for (t_idx y = j * i_resolution_div; y < (j + 1) * i_resolution_div; ++y)
      {
        for (t_idx x = i * i_resolution_div; x < (i + 1) * i_resolution_div; ++x)
        {
          sum += i_array[y * i_nx + x];
        }
      }
      new_array[j * new_nx + i] = sum / (i_resolution_div * i_resolution_div);
    }
  }

  return new_array;
}

void tsunami_lab::io::NetCdf::read(t_idx *o_nx,
                                   t_idx *o_ny,
                                   t_real **o_x,
                                   t_real **o_y,
                                   t_real **o_z,
                                   const std::string filename)
{

  std::cout << "NetCDF:: Looking for file: " << filename << std::endl;
  t_idx l_nx, l_ny;

  int l_ncid_read;

  handleNetCdfError(nc_open(filename.data(), NC_NOWRITE, &l_ncid_read), "Error open file: ");

  int l_x_dimid_read, l_y_dimid_read;

  handleNetCdfError(nc_inq_dimid(l_ncid_read, "x", &l_x_dimid_read), "Error getting y dimension id: ");
  handleNetCdfError(nc_inq_dimid(l_ncid_read, "y", &l_y_dimid_read), "Error getting y dimension id: ");

  handleNetCdfError(nc_inq_dimlen(l_ncid_read, l_x_dimid_read, &l_nx), "Error getting x dimension length: ");
  handleNetCdfError(nc_inq_dimlen(l_ncid_read, l_y_dimid_read, &l_ny), "Error getting y dimension length: ");

  int l_x_varid_read, l_y_varid_read, l_z_varid_read;

  handleNetCdfError(nc_inq_varid(l_ncid_read, "x", &l_x_varid_read), "Error getting x value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid_read, "y", &l_y_varid_read), "Error getting y value id:");
  handleNetCdfError(nc_inq_varid(l_ncid_read, "z", &l_z_varid_read), "Error getting z value id:");

  t_real *l_xv, *l_yv, *l_zv;
  l_xv = new t_real[l_nx];
  l_yv = new t_real[l_ny];
  l_zv = new t_real[l_nx * l_ny];

  handleNetCdfError(nc_get_var_float(l_ncid_read, l_x_varid_read, l_xv), "Error getting x value: ");
  handleNetCdfError(nc_get_var_float(l_ncid_read, l_y_varid_read, l_yv), "Error getting y value: ");
  handleNetCdfError(nc_get_var_float(l_ncid_read, l_z_varid_read, l_zv), "Error getting z value: ");

  *o_nx = l_nx;
  *o_ny = l_ny;
  *o_x = l_xv;
  *o_y = l_yv;
  *o_z = l_zv;

  handleNetCdfError(nc_close(l_ncid_read), "Error closing file: ");
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

  for (t_idx l_x = 0; l_x < i_nx; l_x++)
  {
    for (t_idx l_y = 0; l_y < i_ny; l_y++)
    {
      t_idx l_id = (l_y + i_ghostCellsY) * i_stride + (l_x + i_ghostCellsX);

      l_o[l_y * i_nx + l_x] = i_d[(l_id)];
    }
  }
  return l_o;
}

void tsunami_lab::io::NetCdf::writeCheckpoint(t_idx i_nx,
                                              t_idx i_ny,
                                              t_real const *i_h,
                                              t_real const *i_hu,
                                              t_real const *i_hv,
                                              t_real const *i_b,
                                              t_real i_x_offset,
                                              t_real i_y_offset,
                                              t_real i_stride,
                                              int i_solver_choice,
                                              int i_state_boundary_left,
                                              int i_state_boundary_right,
                                              int i_state_boundary_top,
                                              int i_state_boundary_bottom,
                                              t_real i_width,
                                              t_real i_endTime,
                                              t_idx i_timeStep,
                                              t_real i_time,
                                              t_idx i_nOut)
{
  if (!std::filesystem::exists("checkpoints"))
  {
    std::filesystem::create_directory("checkpoints");
  }
  std::string l_fileName = "checkpoints/checkpoint_1.nc";

  int l_ncid;

  handleNetCdfError(nc_create(l_fileName.c_str(), NC_CLOBBER, &l_ncid), "Error creat the NetCDF file: ");

  // Define the dimensions
  int l_x_dimid, l_y_dimid;
  handleNetCdfError(nc_def_dim(l_ncid, "x", i_nx, &l_x_dimid), "Error define x dimension: ");
  handleNetCdfError(nc_def_dim(l_ncid, "y", i_ny, &l_y_dimid), "Error define y dimension: ");

  int l_b_varid, l_h_varid, l_hu_varid, l_hv_varid;
  int x_y_dim[2] = {l_y_dimid, l_x_dimid};
  handleNetCdfError(nc_def_var(l_ncid, "bathymetry", NC_FLOAT, 2, x_y_dim, &l_b_varid), "Error define bathymetry variable:");
  handleNetCdfError(nc_def_var(l_ncid, "height", NC_FLOAT, 2, x_y_dim, &l_h_varid), "Error define height variable:");
  handleNetCdfError(nc_def_var(l_ncid, "momentum_x", NC_FLOAT, 2, x_y_dim, &l_hu_varid), "Error define momentum_x variable:");
  handleNetCdfError(nc_def_var(l_ncid, "momentum_y", NC_FLOAT, 2, x_y_dim, &l_hv_varid), "Error define momentum_y variable:");

  int l_x_offset_dimid,
      l_y_offset_dimid,
      l_stride_dimid,
      l_solver_choice_dimid,
      l_state_boundary_left_dimid,
      l_state_boundary_right_dimid,
      l_state_boundary_top_dimid,
      l_state_boundary_bottom_dimid,
      l_width_dimid,
      l_endTime_dimid,
      l_timeStep_dimid,
      l_time_dimid,
      l_nOut_dimid;

  // Defining the variables
  handleNetCdfError(nc_def_var(l_ncid, "x_offset", NC_FLOAT, 0, NULL, &l_x_offset_dimid), "Error define x_offset variable:");
  handleNetCdfError(nc_def_var(l_ncid, "y_offset", NC_FLOAT, 0, NULL, &l_y_offset_dimid), "Error define y_offset variable:");
  handleNetCdfError(nc_def_var(l_ncid, "stride", NC_FLOAT, 0, NULL, &l_stride_dimid), "Error define stride variable:");
  handleNetCdfError(nc_def_var(l_ncid, "solver_choice", NC_INT, 0, NULL, &l_solver_choice_dimid), "Error define solver_choice variable:");
  handleNetCdfError(nc_def_var(l_ncid, "state_boundary_left", NC_INT, 0, NULL, &l_state_boundary_left_dimid), "Error define state_boundary_left variable:");
  handleNetCdfError(nc_def_var(l_ncid, "state_boundary_right", NC_INT, 0, NULL, &l_state_boundary_right_dimid), "Error define state_boundary_right variable:");
  handleNetCdfError(nc_def_var(l_ncid, "state_boundary_top", NC_INT, 0, NULL, &l_state_boundary_top_dimid), "Error define state_boundary_top variable:");
  handleNetCdfError(nc_def_var(l_ncid, "state_boundary_bottom", NC_INT, 0, NULL, &l_state_boundary_bottom_dimid), "Error define state_boundary_bottom variable:");
  handleNetCdfError(nc_def_var(l_ncid, "width", NC_FLOAT, 0, NULL, &l_width_dimid), "Error define width variable:");
  handleNetCdfError(nc_def_var(l_ncid, "endTime", NC_FLOAT, 0, NULL, &l_endTime_dimid), "Error define endTime variable:");
  handleNetCdfError(nc_def_var(l_ncid, "timeStep", NC_INT, 0, NULL, &l_timeStep_dimid), "Error define timeStep variable:");
  handleNetCdfError(nc_def_var(l_ncid, "time", NC_FLOAT, 0, NULL, &l_time_dimid), "Error define time variable:");
  handleNetCdfError(nc_def_var(l_ncid, "nOut", NC_FLOAT, 0, NULL, &l_nOut_dimid), "Error define nOut variable:");

  handleNetCdfError(nc_enddef(l_ncid), "Error end defining: ");

  // Writing the values to the NetCDF file
  handleNetCdfError(nc_put_var_float(l_ncid, l_x_offset_dimid, &i_x_offset), "Error put x_offset variable: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_y_offset_dimid, &i_y_offset), "Error put y_offset variable: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_stride_dimid, &i_stride), "Error put stride variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_solver_choice_dimid, &i_solver_choice), "Error put solver_choice variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_state_boundary_left_dimid, &i_state_boundary_left), "Error put state_boundary_left variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_state_boundary_right_dimid, &i_state_boundary_right), "Error put state_boundary_right variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_state_boundary_top_dimid, &i_state_boundary_top), "Error put state_boundary_top variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_state_boundary_bottom_dimid, &i_state_boundary_bottom), "Error put state_boundary_bottom variable: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_width_dimid, &i_width), "Error put width variable: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_endTime_dimid, &i_endTime), "Error put endTime variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_timeStep_dimid, (const int *)&i_timeStep), "Error put timeStep variable: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_time_dimid, &i_time), "Error put time variable: ");
  handleNetCdfError(nc_put_var_int(l_ncid, l_nOut_dimid, (const int *)&i_nOut), "Error put nOut variable: ");

  handleNetCdfError(nc_put_var_float(l_ncid, l_b_varid, i_b), "Error put bathymetry variables: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_h_varid, i_h), "Error put bathymetry variables: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_hu_varid, i_hu), "Error put bathymetry variables: ");
  handleNetCdfError(nc_put_var_float(l_ncid, l_hv_varid, i_hv), "Error put bathymetry variables: ");

  handleNetCdfError(nc_close(l_ncid), "Error closing in write: ");
}

void tsunami_lab::io::NetCdf::readCheckpoint(t_idx *o_nx,
                                             t_idx *o_ny,
                                             t_real **o_h,
                                             t_real **o_hu,
                                             t_real **o_hv,
                                             t_real **o_b,
                                             t_real *o_x_offset,
                                             t_real *o_y_offset,
                                             t_real *o_stride,
                                             int *o_solver_choice,
                                             int *o_state_boundary_left,
                                             int *o_state_boundary_right,
                                             int *o_state_boundary_top,
                                             int *o_state_boundary_bottom,
                                             t_real *o_width,
                                             t_real *o_endTime,
                                             t_idx *o_timeStep,
                                             t_real *o_time,
                                             t_idx *o_nOut,
                                             const std::string filename)
{

  std::cout << "NetCDF:: Looking for file: " << filename << std::endl;

  int l_ncid;
  handleNetCdfError(nc_open(filename.data(), NC_NOWRITE, &l_ncid), "Error open file: ");

  int l_x_dimid_read, l_y_dimid_read;
  handleNetCdfError(nc_inq_dimid(l_ncid, "x", &l_x_dimid_read), "Error getting y dimension id: ");
  handleNetCdfError(nc_inq_dimid(l_ncid, "y", &l_y_dimid_read), "Error getting y dimension id: ");

  handleNetCdfError(nc_inq_dimlen(l_ncid, l_x_dimid_read, o_nx), "Error getting x dimension length: ");
  handleNetCdfError(nc_inq_dimlen(l_ncid, l_y_dimid_read, o_ny), "Error getting y dimension length: ");

  int l_b_varid, l_h_varid, l_hu_varid, l_hv_varid;

  handleNetCdfError(nc_inq_varid(l_ncid, "bathymetry", &l_b_varid), "Error getting bathymetry value id:");
  handleNetCdfError(nc_inq_varid(l_ncid, "height", &l_h_varid), "Error getting height value id:");
  handleNetCdfError(nc_inq_varid(l_ncid, "momentum_x", &l_hu_varid), "Error getting momentum_x value id:");
  handleNetCdfError(nc_inq_varid(l_ncid, "momentum_y", &l_hv_varid), "Error getting momentum_y value id:");

  *o_b = new t_real[(*o_nx) * (*o_ny)];
  *o_h = new t_real[(*o_nx) * (*o_ny)];
  *o_hu = new t_real[(*o_nx) * (*o_ny)];
  *o_hv = new t_real[(*o_nx) * (*o_ny)];

  handleNetCdfError(nc_get_var_float(l_ncid, l_b_varid, *o_b), "Error getting h value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_h_varid, *o_h), "Error getting hu value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_hu_varid, *o_hu), "Error getting hv value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_hv_varid, *o_hv), "Error getting b value: ");

  int l_x_offset_dimid,
      l_y_offset_dimid,
      l_stride_dimid,
      l_solver_choice_dimid,
      l_state_boundary_left_dimid,
      l_state_boundary_right_dimid,
      l_state_boundary_top_dimid,
      l_state_boundary_bottom_dimid,
      l_width_dimid,
      l_endTime_dimid,
      l_timeStep_dimid,
      l_time_dimid,
      l_nOut_dimid;

  handleNetCdfError(nc_inq_varid(l_ncid, "x_offset", &l_x_offset_dimid), "Error getting x_offset value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "y_offset", &l_y_offset_dimid), "Error getting y_offset value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "stride", &l_stride_dimid), "Error getting stride value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "solver_choice", &l_solver_choice_dimid), "Error getting solver_choice value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "state_boundary_left", &l_state_boundary_left_dimid), "Error getting state_boundary_left value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "state_boundary_right", &l_state_boundary_right_dimid), "Error getting state_boundary_right value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "state_boundary_top", &l_state_boundary_top_dimid), "Error getting state_boundary_top value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "state_boundary_bottom", &l_state_boundary_bottom_dimid), "Error getting state_boundary_bottom value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "width", &l_width_dimid), "Error getting width value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "endTime", &l_endTime_dimid), "Error getting endTime value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "timeStep", &l_timeStep_dimid), "Error getting timeStep value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "time", &l_time_dimid), "Error getting time value id: ");
  handleNetCdfError(nc_inq_varid(l_ncid, "nOut", &l_nOut_dimid), "Error getting nOut value id: ");

  // Float variables
  handleNetCdfError(nc_get_var_float(l_ncid, l_x_offset_dimid, o_x_offset), "Error getting x_offset value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_y_offset_dimid, o_y_offset), "Error getting y_offset value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_stride_dimid, o_stride), "Error getting stride value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_width_dimid, o_width), "Error getting width value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_endTime_dimid, o_endTime), "Error getting endTime value: ");
  handleNetCdfError(nc_get_var_float(l_ncid, l_time_dimid, o_time), "Error getting time value: ");

  // Integer variables
  handleNetCdfError(nc_get_var_int(l_ncid, l_solver_choice_dimid, o_solver_choice), "Error getting solver_choice value: ");
  handleNetCdfError(nc_get_var_int(l_ncid, l_state_boundary_left_dimid, o_state_boundary_left), "Error getting state_boundary_left value: ");
  handleNetCdfError(nc_get_var_int(l_ncid, l_state_boundary_right_dimid, o_state_boundary_right), "Error getting state_boundary_right value: ");
  handleNetCdfError(nc_get_var_int(l_ncid, l_state_boundary_top_dimid, o_state_boundary_top), "Error getting state_boundary_top value: ");
  handleNetCdfError(nc_get_var_int(l_ncid, l_state_boundary_bottom_dimid, o_state_boundary_bottom), "Error getting state_boundary_bottom value: ");
  int l_nOut, l_timeStep;
  handleNetCdfError(nc_get_var_int(l_ncid, l_timeStep_dimid, &l_timeStep), "Error getting timeStep value: ");
  handleNetCdfError(nc_get_var_int(l_ncid, l_nOut_dimid, &l_nOut), "Error getting nOut value: ");
  *o_nOut = l_nOut;
  *o_timeStep = l_timeStep;

  handleNetCdfError(nc_close(l_ncid), "Error closing file: ");
}
