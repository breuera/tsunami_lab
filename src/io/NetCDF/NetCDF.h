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

#include <cstring>
#include <string>

#include "../../constants.h"

namespace tsunami_lab {
    namespace io {
        class NetCDF;
    }
}  // namespace tsunami_lab

class tsunami_lab::io::NetCDF {
   private:
    std::string m_fileName;

    t_real const *m_b;

    t_real m_dxy;
    t_idx m_nx, m_ny, m_stride;

    int m_ncId;

   public:
    /**
     * @brief constructor/deconstructor.
     *
     */
    NetCDF();
    ~NetCDF();

    /**
     * @brief initialize the netCDF writer.
     *
     * @param i_dxy cell width in x- and y-direction.
     * @param i_nx number of cells in x-direction.
     * @param i_ny number of cells in y-direction.
     * @param stride stride of the data arrays in y-direction (including ghost cells).
     * @param i_b bathymetry of the cells; optional: use nullptr if not required.
     * @param i_fileName the name or path of the output file.
     */
    int init(t_real i_dxy,
             t_idx i_nx,
             t_idx i_ny,
             t_idx stride,
             t_real const *i_b,
             std::string i_outFileName);

    /**
     * @brief appends data for given timestep.
     *
     * @param i_time amount of time passed.
     * @param i_timeStep counter for iterations done.
     * @param i_h water height of the cells.
     * @param i_hu momentum in x-direction of the cells.
     * @param i_hv momentum in y-direction of the cells.
     */
    int write(t_real i_time,
              t_idx i_timeStep,
              t_real const *i_h,
              t_real const *i_hu,
              t_real const *i_hv);

    /**
     * Reads the bathymetry and displacement data from the respective file.
     *
     * @param i_nameBathymetry name of the file containing the bathymetry
     * @param i_nameDisplacements name of the file containing the displacement
     * @param o_bathymetryDimX dimension of the bathymetry data in x-direction
     * @param o_bathymetryDimY dimension of the bathymetry data in y-direction
     * @param o_bathymetryPosX x-coordinates of bathymetry data
     * @param o_bathymetryPosY y-coordinates of bathymetry data
     * @param o_bathymetry bathymetry data
     * @param o_dispDimX dimension of the displacement data in x-direction
     * @param o_dispDimY dimension of the displacement data in y-direction
     * @param o_dispPosX x-coordinates of displacement data
     * @param o_dispPosY x-coordinates of displacement data
     * @param o_displacements displacements data
     */
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
};

#endif