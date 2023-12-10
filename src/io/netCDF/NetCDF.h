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
  std::string m_out_file_name;

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

  tsunami_lab::t_real *scaleDownArray(t_real const *i_array,
                                      t_idx i_nx,
                                      t_idx i_ny,
                                      int i_resolution_div);

public:
  ~NetCdf();

  /**
   * @brief Sets up the initial settings for the write-function, like initializing the output-file id and writing bathymetry (needs to be done only once)
   *
   * @param filename File-path + name of the output-file
   * @param i_dxy cell width in x- and y-direction.
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_resolution_div Scalar by which the resolution will be divided.
   * @param i_x_offset offset x-direction.
   * @param i_y_offset offset y-direction.
   * @param i_b bathymetry of the cells.
   */
  void initialize(const std::string &filename,
                  t_real i_dxy,
                  t_idx i_nx,
                  t_idx i_ny,
                  int i_resolution_div,
                  t_real i_x_offset,
                  t_real i_y_offset,
                  t_real const *i_b);

  /**
   * @brief Writes one instance of h, hu, hv, time-step and stamp into the output-file.
   *
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_resolution_div Scalar by which the resolution will be divided.
   * @param i_h water height of the cells.
   * @param i_hu momentum in x-direction of the cells.
   * @param i_hv momentum in y-direction of the cells
   * @param timeStep Current time-step of the simulation.
   * @param i_time Current time-stamp of the simulation.
   */
  void write(t_idx i_nx,
             t_idx i_ny,
             int i_resolution_div,
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

  /**
   * @brief Writes every nessecary parameter for a checkpoint
   *
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_h water height of the cells.
   * @param i_hu momentum in x-direction of the cells.
   * @param i_hv momentum in y-direction of the cells
   * @param i_b bathymetry of the cells.
   * @param i_x_offset offset x-direction.
   * @param i_y_offset offset y-direction.
   * @param i_stride Stride (x-axis + 2).
   * @param i_solver_choice Solver-choice (0 = roe, 1 = fwave)
   * @param i_state_boundary_left State of the left-boundary (0 = open, 1 = closed)
   * @param i_state_boundary_right State of the right-boundary (0 = open, 1 = closed)
   * @param i_state_boundary_top State of the top-boundary (0 = open, 1 = closed)
   * @param i_state_boundary_bottom State of the bottom-boundary (0 = open, 1 = closed)
   * @param i_width width of the simulated area
   * @param i_endTime Time of simulation
   * @param i_timeStep Current time-step of the simulation.
   * @param i_time Current time-stamp of the simulation.
   * @param i_nOut Counter
   * @param i_hMax get max heigth
   * @param i_simulated_frame get max simulated frames
   */
  void writeCheckpoint(t_idx i_nx,
                       t_idx i_ny,
                       t_real const *i_h,
                       t_real const *i_hu,
                       t_real const *i_hv,
                       t_real const *i_b,
                       t_real i_x_offset,
                       t_real i_y_offset,
                       int i_solver_choice,
                       int i_state_boundary_left,
                       int i_state_boundary_right,
                       int i_state_boundary_top,
                       int i_state_boundary_bottom,
                       t_real i_width,
                       t_real i_endTime,
                       t_idx i_timeStep,
                       t_real i_time,
                       t_idx i_nOut,
                       t_real i_hMax,
                       t_idx i_simulated_frame);

  /**
   * @brief Reads all necessary parameters for a checkpoint from a file
   *
   * @param o_nx Pointer to number of cells in x-direction.
   * @param o_ny Pointer to number of cells in y-direction.
   * @param o_h Pointer to water height of the cells.
   * @param o_hu Pointer to momentum in x-direction of the cells.
   * @param o_hv Pointer to momentum in y-direction of the cells.
   * @param o_b Pointer to bathymetry of the cells.
   * @param o_x_offset Pointer to offset in x-direction.
   * @param o_y_offset Pointer to offset in y-direction.
   * @param o_stride Pointer to Stride (x-axis + 2).
   * @param o_solver_choice Pointer to Solver-choice (0 = roe, 1 = fwave)
   * @param o_state_boundary_left Pointer to State of the left-boundary (0 = open, 1 = closed)
   * @param o_state_boundary_right Pointer to State of the right-boundary (0 = open, 1 = closed)
   * @param o_state_boundary_top Pointer to State of the top-boundary (0 = open, 1 = closed)
   * @param o_state_boundary_bottom Pointer to State of the bottom-boundary (0 = open, 1 = closed)
   * @param o_width Pointer to width of the simulated area
   * @param o_endTime Pointer to Time of simulation
   * @param o_timeStep Pointer to Current time-step of the simulation.
   * @param o_time Pointer to Current time-stamp of the simulation.
   * @param o_nOut Pointer to Counter
   * @param o_hMax Pointer to Current hMax of the simulation.
   * @param o_simulated_frame Pointer to simulated_frame
   * @param filename Name of the file to read the checkpoint from.
   */
  void readCheckpoint(t_idx *o_nx,
                      t_idx *o_ny,
                      t_real **o_h,
                      t_real **o_hu,
                      t_real **o_hv,
                      t_real **o_b,
                      t_real *o_x_offset,
                      t_real *o_y_offset,
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
                      t_real *o_hMax,
                      t_idx *o_simulated_frame,
                      const std::string filename);
};

#endif