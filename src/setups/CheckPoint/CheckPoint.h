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
    t_idx m_dimX;
    t_idx m_dimY;
    t_idx m_frameOffset;
    t_real m_cellWidthX;
    t_real m_cellWidthY;
    t_real *m_height;
    t_real *m_momentumX;
    t_real *m_momentumY;
    t_real *m_bathymetry;
	 t_real *m_time;

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

    t_real *getHeightData() {
        return m_height;
    }

    t_real *getMomentumXData() {
        return m_momentumX;
    }

    t_real *getMomentumYData() {
        return m_momentumY;
    }

    t_real *getTimeData() {
        return m_time;
    }
};

#endif