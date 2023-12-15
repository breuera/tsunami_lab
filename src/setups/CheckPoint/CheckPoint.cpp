/**
 * @author Marek Sommerfeld
 *
 * @section DESCRIPTION
 * CheckPoint Loader Setup.
 **/

#include "CheckPoint.h"

#include <cmath>
#include <iostream>

tsunami_lab::setups::CheckPoint::CheckPoint(t_real i_dimX,
                                            t_real i_dimY,
                                            t_idx i_nx,
                                            t_idx i_ny,
														  t_idx i_frame,
                                            t_real *i_height,
                                            t_real *i_momentumX,
                                            t_real *i_momentumY,
                                            t_real *i_bathymetry,
														  t_real *i_time) {
    m_nx = i_nx;
    m_ny = i_ny;
	 m_frameOffset = i_frame * i_nx * i_ny;
    m_height = i_height;
    m_momentumX = i_momentumX;
    m_momentumY = i_momentumY;
    m_bathymetry = i_bathymetry;
	 m_time = i_time;
	 m_currentFrame = i_frame;

    m_cellWidthX = m_nx / i_dimX;
    m_cellWidthY = m_ny / i_dimY;

	 m_heightData = new t_real[(m_nx + 2) * (m_ny + 2)];
	 m_momentumXData = new t_real[(m_nx + 2) * (m_ny + 2)];
	 m_momentumYData = new t_real[(m_nx + 2) * (m_ny + 2)];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getHeight(t_real i_x,
                                                               t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_height[l_ix + l_iy * m_nx + m_frameOffset];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getMomentumX(t_real i_x,
                                                                  t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_momentumX[l_ix + l_iy * m_nx + m_frameOffset];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getMomentumY(t_real i_x,
                                                                  t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_momentumY[l_ix + l_iy * m_nx + m_frameOffset];
}

tsunami_lab::t_real tsunami_lab::setups::CheckPoint::getBathymetry(t_real i_x,
                                                                   t_real i_y) const {
    t_idx l_ix = round(i_x * m_cellWidthX);
    t_idx l_iy = round(i_y * m_cellWidthY);

    return m_bathymetry[l_ix + l_iy * m_nx];
}

tsunami_lab::setups::CheckPoint::~CheckPoint() {
	delete[] m_heightData;
	delete[] m_momentumXData;
	delete[] m_momentumYData;

	delete[] m_height;
	delete[] m_momentumX;
	delete[] m_momentumY;
	delete[] m_bathymetry;
	delete[] m_time;
}