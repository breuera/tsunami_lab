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
   public:
    static int read(std::string i_nameBathymetry,
                    std::string i_nameDisplacements,
                    t_idx *o_bathymetryDimX,
                    t_idx *o_bathymetryDimY,
                    t_real *&o_bathymetryPosX,
                    t_real *&o_bathymetryPosY,
                    t_real *&o_bathymetry,
                    t_idx *o_dispDimX,
                    t_idx *o_dispDimY,
                    t_real *&o_dispPosX,
                    t_real *&o_dispPosY,
                    t_real *&o_displacements);

    static void write();
};

#endif