/**
 * @author Marek Sommerfeld
 *
 * @section DESCRIPTION
 * CheckPoint Loader Setup.
 **/
#ifndef TSUNAMI_LAB_SETUPS_CHECK_POINT_H
#define TSUNAMI_LAB_SETUPS_CHECK_POINT_H

#include "../Setup.h"

namespace tsunami_lab {
    namespace setups {
        class CheckPoint;
    }
}  // namespace tsunami_lab

class tsunami_lab::setups::CheckPoint : public Setup {
   private:
    t_idx m_nx;
    t_idx m_ny;
    t_idx m_frameOffset;
    t_idx m_currentFrame;
    t_real m_cellWidthX;
    t_real m_cellWidthY;
    t_real *m_height;
    t_real *m_momentumX;
    t_real *m_momentumY;
    t_real *m_bathymetry;
    t_real *m_time;
    t_real *m_heightData;
    t_real *m_momentumXData;
    t_real *m_momentumYData;

   public:
    /**
     * Constructor.
     *
     * @param i_innerHeight water height in the dam.
     * @param i_outerHeight water height outside of the dam.
     * @param i_simLenX length of simulation in x direction.
     * @param i_simLenY length of simulation in y direction.
     * @param i_damLimit limit of the dam.
     **/
    CheckPoint(t_real i_nx,
               t_real i_ny,
               t_idx i_dimX,
               t_idx i_dimY,
               t_idx i_frame,
               t_real *i_height,
               t_real *i_momentumX,
               t_real *i_momentumY,
               t_real *i_bathymetry,
               t_real *i_time);

    ~CheckPoint();

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getHeight(t_real i_x,
                     t_real i_y) const;

    /**
     * Gets the momentum in x-direction.
     *
     * @return momentum in x-direction.
     **/
    t_real getMomentumX(t_real,
                        t_real) const;

    /**
     * Gets the momentum in y-direction.
     *
     * @return momentum in y-direction.
     **/
    t_real getMomentumY(t_real,
                        t_real) const;

    /**
     * Gets the bathymetry at given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return bathymetry.
     */
    t_real getBathymetry(t_real,
                         t_real) const;

    t_real *getHeightData(t_idx i_frame) {
        for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
            for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
                m_heightData[(l_ix + 1) + (l_iy + 1) * (m_nx + 2)] = m_height[l_ix + l_iy * m_nx + i_frame * m_nx * m_ny];
            }
        }

        return m_heightData;
    }

    t_real *getMomentumXData(t_idx i_frame) {
        for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
            for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
                m_momentumXData[(l_ix + 1) + (l_iy + 1) * (m_nx + 2)] = m_momentumX[l_ix + l_iy * m_nx + i_frame * m_nx * m_ny];
            }
        }

        return m_momentumXData;
    }

    t_real *getMomentumYData(t_idx i_frame) {
        for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
            for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
                m_momentumYData[(l_ix + 1) + (l_iy + 1) * (m_nx + 2)] = m_momentumY[l_ix + l_iy * m_nx + i_frame * m_nx * m_ny];
            }
        }
        return m_momentumYData;
    }

    t_real getSimTimeData(t_idx i_frame) {
        return m_time[i_frame];
    }

    t_real getCurrentFrame() {
        return m_currentFrame;
    }
};

#endif