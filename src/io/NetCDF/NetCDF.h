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

#include <cmath>
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
    std::string m_outFileName;

    t_real *m_time;
    t_real *m_height, *m_momentumX, *m_momentumY;
    t_real *m_dataX, *m_dataY, *m_dataB;

    t_real m_dxy;
    t_idx m_nx, m_ny, m_nxCoarse, m_nyCoarse, m_nxy, m_nxyCoarse, m_stride;
    t_idx m_frameCount, m_dataSize, m_coarseFactor;

    int m_varXId, m_varYId, m_varTimeId, m_varBathymetryId, m_varHeightId, m_varMomentumXId, m_varMomentumYId, m_varSimTimeId, m_varEndTimeId, m_varFrameId;
    int m_dimXId, m_dimYId, m_dimTimeId, m_dimSimTimeId, m_dimEndTimeId, m_dimFrameId;
    int m_ncId;

    int init(t_idx i_currentFrame,
             std::string i_checkPointPath);

    bool isInBounds(int i_x, int i_y);

   public:
    /**
     * @brief constructor/deconstructor.
     *
     */
    NetCDF(t_real i_endTime,
           t_real i_dt,
           t_idx i_timeStepsPerFrame,
           t_real i_dxy,
           t_idx i_nx,
           t_idx i_ny,
           t_idx i_stride,
           t_idx i_coarseFactor,
           t_real const *i_b,
           std::string i_outFileName);

    ~NetCDF();

    /**
     * @brief appends data for given timestep.
     *
     * @param i_simTime amount of time passed.
     * @param i_frame counter for iterations done.
     * @param i_h water height of the cells.
     * @param i_hu momentum in x-direction of the cells.
     * @param i_hv momentum in y-direction of the cells.
     */
    int store(t_real i_simTime,
              t_idx i_frame,
              t_real const *i_h,
              t_real const *i_hu,
              t_real const *i_hv);

    int write(t_idx i_currentFrame,
              std::string i_checkPointPath,
              t_real i_simTime,
              t_real i_endTime);
    int write();

    static int readCheckpoint(std::string i_checkPoinPath,
                              t_real *o_height,
                              t_real *o_momentumX,
                              t_real *o_momentumY,
                              t_real *o_bathymetry,
                              t_real *o_time,
                              t_idx *o_currentFrame,
                              t_real *o_endSimTime,
                              t_real *o_startSimTime);

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