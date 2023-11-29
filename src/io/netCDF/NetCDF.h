/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing and reading large data
 *
 **/
#ifndef TSUNAMI_LAB_IO_NETCDF
#define TSUNAMI_LAB_IO_NETCDF

#include "../../constants.h"
#include <cstring>
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
  int m_ncid = -1,
      m_x_dimid,
      m_y_dimid,
      m_time_dimid;

  int m_x_varid,
      m_y_varid,
      m_z_varid,
      m_h_varid,
      m_hu_varid,
      m_hv_varid,
      m_b_varid,
      m_time_varid;

public:
  ~NetCdf();

  /**
   * @brief
   *
   * @param filename
   * @param i_dxy
   * @param i_nx
   * @param i_ny
   * @param i_x_offset
   * @param i_y_offset
   * @param i_b
   */
  void initialize(const std::string &filename,
                  t_real i_dxy,
                  t_idx i_nx,
                  t_idx i_ny,
                  t_real i_x_offset,
                  t_real i_y_offset,
                  t_real const *i_b);

  /**
   * @brief
   *
   * @param i_nx
   * @param i_ny
   * @param i_h
   * @param i_hu
   * @param i_hv
   * @param timeStep
   * @param i_time
   */
  void write(t_idx i_nx,
             t_idx i_ny,
             t_real const *i_h,
             t_real const *i_hu,
             t_real const *i_hv,
             t_idx timeStep,
             t_real i_time);

  /**
   * @brief
   *
   * @param o_nx
   * @param o_ny
   * @param o_x
   * @param o_y
   * @param o_z
   * @param filename
   */
  void read(t_idx *o_nx,
            t_idx *o_ny,
            t_real **o_x,
            t_real **o_y,
            t_real **o_z,
            const std::string filename);

  /**
   * @brief
   *
   * @param status
   * @param errorMessage
   */
  static void handleNetCdfError(int status, const std::string &errorMessage);

  /**
   * @brief
   *
   * @param i_data
   * @param m_nx
   * @param m_ny
   * @param m_ghostCellsX
   * @param m_ghostCellsY
   * @param m_stride
   * @return t_real*
   */
  static t_real *removeGhostCells(const t_real *i_data,
                                  t_idx m_nx,
                                  t_idx m_ny,
                                  t_idx m_ghostCellsX,
                                  t_idx m_ghostCellsY,
                                  t_idx m_stride);
};

#endif