/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#ifndef TSUNAMI_LAB_IO_CSV
#define TSUNAMI_LAB_IO_CSV

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
  t_idx m_strid;

public:
  static void write(t_real i_dxy,
                    t_idx i_nx,
                    t_idx i_ny,
                    t_real i_x_offset,
                    t_real i_y_offset,
                    t_real const *i_h,
                    t_real const *i_hu,
                    t_real const *i_hv,
                    t_real const *i_b,
                    const std::string &filename,
                    t_idx timeStep);
};

#endif