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
#include <string>
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
      m_x_dimid = -1,
      m_y_dimid = -1,
      m_time_dimid = -1;

  int m_x_varid = -1,
      m_y_varid = -1,
      m_z_varid = -1,
      m_h_varid = -1,
      m_hu_varid = -1,
      m_hv_varid = -1,
      m_b_varid = -1,
      m_time_varid = -1;

public:
  ~NetCdf();

  /**
   * @brief Sets up the initial settings for the write-function, like initializing the output-file id and writing bathymetry (needs to be done only once)
   *
   * @param filename File-path + name of the output-file
   * @param i_dxy cell width in x- and y-direction.
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_x_offset offset x-direction.
   * @param i_y_offset offset y-direction.
   * @param i_b bathymetry of the cells.
   */
  void initialize(const std::string &filename,
                  t_real i_dxy,
                  t_idx i_nx,
                  t_idx i_ny,
                  t_real i_x_offset,
                  t_real i_y_offset,
                  t_real const *i_b);

  /**
   * @brief Writes one instance of h, hu, hv, time-step and stamp into the output-file.
   *
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_h water height of the cells.
   * @param i_hu momentum in x-direction of the cells.
   * @param i_hv momentum in y-direction of the cells
   * @param timeStep Current time-step of the simulation.
   * @param i_time Current time-stamp of the simulation.
   */
  void write(t_idx i_nx,
             t_idx i_ny,
             t_real const *i_h,
             t_real const *i_hu,
             t_real const *i_hv,
             t_idx timeStep,
             t_real i_time);

  /**
   * @brief Reads one
   *
   * @param o_nx address of x-coordinate-count variable.
   * @param o_ny address of y-coordinate-count variable.
   * @param o_x address of input-x-array, in this case the x-coordinate array.
   * @param o_y address of input-y-array, in this case the y-coordinate array.
   * @param o_z address of input-z-array, in this case the value array.
   * @param filename filename + path of file to be read.
   */
  void read(t_idx *o_nx,
            t_idx *o_ny,
            t_real **o_x,
            t_real **o_y,
            t_real **o_z,
            const std::string filename);

  /**
   * @brief Checks, if given netcdf-function returns an error and writes a report, if so.
   *
   * @param status Retrun-value of a netcdf-function.
   * @param errorMessage address of message to be written.
   */
  static void handleNetCdfError(int status, const std::string &errorMessage);

  /**
   * @brief Removes possible ghost-cells from the data-array
   *
   * @param i_data Array of values, where ghost-cells need to be deleted from.
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_ghostCellsX existance of ghost-cells in x-direction (1 or 0).
   * @param i_ghostCellsY existance of ghost-cells in y-direction (1 or 0).
   * @param i_stride Stride (x-axis + 2).
   * @return t_real* copy of i_data without the ghost-cells.
   */
  static t_real *removeGhostCells(const t_real *i_data,
                                  t_idx i_nx,
                                  t_idx i_ny,
                                  t_idx i_ghostCellsX,
                                  t_idx i_ghostCellsY,
                                  t_idx i_stride);
};

#endif