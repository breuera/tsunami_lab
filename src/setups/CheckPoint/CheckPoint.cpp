/**
 * @author Marek Sommerfeld
 *
 * @section DESCRIPTION
 * CheckPoint Loader Setup.
 **/

#include "CheckPoint.h"

#include <cmath>
#include <iostream>

tsunami_lab::setups::CheckPoint::CheckPoint(t_real i_nx,
                                            t_real i_ny,
                                            t_idx i_dimX,
                                            t_idx i_dimY,
														  t_idx i_frame,
                                            t_real *i_height,
                                            t_real *i_momentumX,
                                            t_real *i_momentumY,
                                            t_real *i_bathymetry,
														  t_real *i_time) {
    m_dimX = i_dimX;
    m_dimY = i_dimY;
	 m_frameOffset = i_frame * i_nx * i_ny;
    m_height = i_height;
    m_momentumX = i_momentumX;
    m_momentumY = i_momentumY;
    m_bathymetry = i_bathymetry;
	 m_time = i_time;

    m_cellWidthX = m_dimX / i_nx;
    m_cellWidthY = m_dimY / i_ny;
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getHeight(t_real i_x,
                                                               t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_height[l_ix + l_iy * m_dimX + m_frameOffset];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getMomentumX(t_real i_x,
                                                                  t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_momentumX[l_ix + l_iy * m_dimX + m_frameOffset];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getMomentumY(t_real i_x,
                                                                  t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_momentumY[l_ix + l_iy * m_dimX + m_frameOffset];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getBathymetry(t_real i_x,
                                                                   t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_bathymetry[l_ix + l_iy * m_dimX + m_frameOffset];
}
