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

#include <string>

#include "../../constants.h"
#include "netcdf.h"

namespace tsunami_lab {
    namespace io {
        class NetCDF;
    }
}  // namespace tsunami_lab

class tsunami_lab::io::NetCDF {
    void read(std::string i_pathBathymetry,
              std::string i_pathDisplacements,
              t_real *&o_bathymetry,
              t_real *&o_displacements);

    void write();
};

#endif