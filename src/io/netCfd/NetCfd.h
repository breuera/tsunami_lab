/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for large binary data using netCfd.
 **/
#ifndef TSUNAMI_LAB_IO_NETCDF
#define TSUNAMI_LAB_IO_NETCDF

#include <cstring>
#include <iostream>
#include <vector>

#include "../../constants.h"

namespace tsunami_lab {
namespace io {
class NetCfd;
}
}  // namespace tsunami_lab

class tsunami_lab::io::NetCfd {
   public:
    /**
     * Writes the data as CSV to the given stream.
     *
     * @param i_dxy cell width in x- and y-direction.
     * @param i_nx number of cells in x-direction.
     * @param i_ny number of cells in y-direction.
     * @param i_x_offset offset x-direction.
     * @param i_y_offset offset in y-direction.
     * @param i_stride stride of the data arrays in y-direction (x is assumed to be stride-1).
     * @param i_h water height of the cells; optional: use nullptr if not required.
     * @param i_hu momentum in x-direction of the cells; optional: use nullptr if not required.
     * @param i_hv momentum in y-direction of the cells; optional: use nullptr if not required.
     * @param i_b bathymetry of the cells; optional: use nullptr if not required.
     * @param io_stream stream to which the CSV-data is written.
     **/
    static void write(t_real i_dxy,
                      t_idx i_nx,
                      t_idx i_ny,
                      t_real i_x_offset,
                      t_real i_y_offset,
                      t_idx i_stride,
                      t_real const *i_h,
                      t_real const *i_hu,
                      t_real const *i_hv,
                      t_real const *i_b,
                      std::ostream &io_stream);

    static void read(std::string i_filename,
                     std::vector<t_real> &o_depths);
};

#endif