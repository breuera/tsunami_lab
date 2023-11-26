/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for reading and writing NetCDF files.
 **/

#ifndef TSUNAMI_LAB_IO_NETCDF
#define TSUNAMI_LAB_IO_NETCDF

#include <netcdf.h>

#include <string>

#include "../../constants.h"

namespace tsunami_lab {
    namespace io {
        class NetCDF;
    }
}  // namespace tsunami_lab

class tsunami_lab::io::NetCDF {
   public:
    void
    read(std::string i_pathBathymetry,
         std::string i_pathDisplacements,
         t_real *&o_bathymetry,
         t_real *&o_displacements);

    static void write(t_real i_dxy,
                      t_idx i_nx,
                      t_idx i_ny,
                      t_idx i_stride,
                      //  t_real const *i_h,
                      //  t_real const *i_hu,
                      //  t_real const *i_hv,
                      t_real const *i_b);
};

#endif