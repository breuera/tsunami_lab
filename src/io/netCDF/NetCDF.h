/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#ifndef TSUNAMI_LAB_IO_NETCDF
#define TSUNAMI_LAB_IO_NETCDF

#include "../../constants.h"
#include <cstring>
#include <iostream>
#include <vector>

namespace tsunami_lab
{
  namespace io
  {
    class NetCdf;
  }
}

class tsunami_lab::io::NetCdf
{
private:
  int m_ncid, m_x_dimid, m_y_dimid, m_time_dimid;
  int m_x_varid, m_y_varid, m_z_varid, m_h_varid, m_hu_varid, m_hv_varid, m_b_varid;

public:
  ~NetCdf();

  void netCDF(const std::string &filename,
              t_real i_dxy,
              t_idx i_nx,
              t_idx i_ny,
              t_real i_x_offset,
              t_real i_y_offset,
              t_real const *i_b);

  void write(t_idx i_nx,
             t_idx i_ny,
             t_real const *i_h,
             t_real const *i_hu,
             t_real const *i_hv,
             t_idx timeStep,
             t_real i_time);
};

#endif