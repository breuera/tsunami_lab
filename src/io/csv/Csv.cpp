/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#include "Csv.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

void tsunami_lab::io::Csv::write(t_real i_dxy,
                                 t_idx i_nx,
                                 t_idx i_ny,
                                 t_idx i_x_offset,
                                 t_idx i_y_offset,
                                 t_idx i_stride,
                                 t_real const *i_h,
                                 t_real const *i_hu,
                                 t_real const *i_hv,
                                 t_real const *i_b,
                                 std::ostream &io_stream)
{

  int x_ghost_cell = 0;
  int y_ghost_cell = 0;
  // write the CSV header
  io_stream << "x,y";
  if (i_h != nullptr)
    io_stream << ",height";
  if (i_hu != nullptr)
  {
    io_stream << ",momentum_x";
    x_ghost_cell = 1;
  }
  if (i_hv != nullptr)
  {
    io_stream << ",momentum_y";
    y_ghost_cell = 1;
  }
  if (i_b != nullptr)
    io_stream << ",bathymetry";
  io_stream << "\n";

  // iterate over all cells
  for (t_idx l_iy = y_ghost_cell; l_iy < i_ny + y_ghost_cell; l_iy++)
  {
    for (t_idx l_ix = x_ghost_cell; l_ix < i_nx + x_ghost_cell; l_ix++)
    {
      // derive coordinates of cell center
      t_real l_posX = (l_ix + 0.5 - x_ghost_cell) * i_dxy + i_x_offset;
      t_real l_posY = (l_iy + 0.5 - y_ghost_cell) * i_dxy + i_y_offset;

      t_idx l_id = l_iy * i_stride + l_ix;

      // write data
      io_stream << l_posX << "," << l_posY;
      if (i_h != nullptr)
        io_stream << "," << i_h[l_id];
      if (i_hu != nullptr)
        io_stream << "," << i_hu[l_id];
      if (i_hv != nullptr)
        io_stream << "," << i_hv[l_id];
      if (i_b != nullptr)
        io_stream << "," << i_b[l_id];
      io_stream << "\n";
    }
  }
  io_stream << std::flush;
}

void tsunami_lab::io::Csv::read(std::string i_filename,
                                std::vector<t_real> &o_depths)
{

  std::ifstream file(i_filename);
  std::string line, cell;

  while (std::getline(file, line))
  {
    std::stringstream lineStream(line);

    // Skip the first three values in the line
    for (int i = 0; i < 3; ++i)
    {
      std::getline(lineStream, cell, ',');
    }

    // Extract and store the fourth value
    std::getline(lineStream, cell, ',');

    o_depths.push_back(std::stof(cell));
  }
}
