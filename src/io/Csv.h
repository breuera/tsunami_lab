/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#ifndef TSUNAMI_LAB_IO_CSV
#define TSUNAMI_LAB_IO_CSV

#include "../constants.h"
#include <cstring>
#include <fstream> 
#include <iostream>

namespace tsunami_lab {
  namespace io {
    class Csv;
  }
}

class tsunami_lab::io::Csv {
  public:
    /**
     * Writes the data as CSV to the given stream.
     *
     * @param i_dxy cell width in x- and y-direction.
     * @param i_nx number of cells in x-direction.
     * @param i_ny number of cells in y-direction.
     * @param i_stride stride of the data arrays in y-direction (x is assumed to be stride-1).
     * @param i_h water height of the cells; optional: use nullptr if not required.
     * @param i_hu momentum in x-direction of the cells; optional: use nullptr if not required.
     * @param i_hv momentum in y-direction of the cells; optional: use nullptr if not required.
     * @param i_b bathymetry of the cells; optional: use nullptr if not required.
     * @param io_stream stream to which the CSV-data is written.
     **/
    static void write( t_real               i_dxy,
                       t_idx                i_nx,
                       t_idx                i_ny,
                       t_idx                i_stride,
                       t_real       const * i_h,
                       t_real       const * i_hu,
                       t_real       const * i_hv,
                       t_real       const * i_b,
                       std::ostream       & io_stream );
    
    /**
     * Reads a file filled with middle states from a given iostream.
     * 
     * @param iostream stream from which the CSV-Data is read.
     * @param o_heightsL array of initial heigths on the left side
     * @param o_momentumsL array of initial momentums on the left side
     * @param o_heightsR array of initial heights on the right side
     * @param o_momentumsR array of initial momentums on the right side 
     * @param o_hStar array of middle state heights
     **/
    static void read_middle_states( std::ifstream  & io_stream,     
                                    t_real         *& o_heightsL,
                                    t_real         *& o_momentumsL,
                                    t_real         *& o_heightsR,
                                    t_real         *& o_momentumsR, 
                                    t_real         *& o_hStar);
};

#endif