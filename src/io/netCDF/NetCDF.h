/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
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
  int m_x_varid, m_y_varid, m_z_varid, m_h_varid, m_hu_varid, m_hv_varid, m_b_varid, m_time_varid;

public:
  ~NetCdf();

  void netCdf(const std::string &filename,
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

  void read(t_idx &o_nx,
            t_idx &o_ny,
            t_real **o_x,
            t_real **o_y,
            t_real **o_z,
            const std::string filename);

  static void handleNetCdfError(int status, const std::string &errorMessage);

  static t_real *removeGhostCells(const t_real *i_data,
                                  t_idx m_nx,
                                  t_idx m_ny,
                                  t_idx m_ghostCellsX,
                                  t_idx m_ghostCellsY,
                                  t_idx m_stride);
};

#endif