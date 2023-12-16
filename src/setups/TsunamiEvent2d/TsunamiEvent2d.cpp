/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional Tsunami event setup.
 **/
#include "TsunamiEvent2d.h"

#include <algorithm>
#include <cmath>
#include <iostream>

tsunami_lab::setups::TsunamiEvent2d::TsunamiEvent2d(t_real i_simLenX,
                                                    t_real i_simLenY,
                                                    t_idx i_bathymetryDimX,
                                                    t_idx i_bathymetryDimY,
                                                    t_real *i_bathymetryPosX,
                                                    t_real *i_bathymetryPosY,
                                                    t_real *i_bathymetry,
                                                    t_idx i_displacementsDimX,
                                                    t_idx i_displacementsDimY,
                                                    t_real *i_displacementsPosX,
                                                    t_real *i_displacementsPosY,
                                                    t_real *i_displacements,
                                                    t_real i_epicenterOffsetX,
                                                    t_real i_epicenterOffsetY) {
    m_simLenX = i_simLenX;
    m_simLenY = i_simLenY;
    m_bathymetryDimX = i_bathymetryDimX;
    m_bathymetryDimY = i_bathymetryDimY;
    m_bathymetryPosX = i_bathymetryPosX;
    m_bathymetryPosY = i_bathymetryPosY;
    m_bathymetry = i_bathymetry;
    m_displacementsDimX = i_displacementsDimX;
    m_displacementsDimY = i_displacementsDimY;
    m_displacementsPosX = i_displacementsPosX;
    m_displacementsPosY = i_displacementsPosY;
    m_displacement = i_displacements;
    m_epicenterOffsetX = i_epicenterOffsetX;
    m_epicenterOffsetY = i_epicenterOffsetY;
}

tsunami_lab::setups::TsunamiEvent2d::~TsunamiEvent2d() {
    delete[] m_bathymetryPosX;
    delete[] m_bathymetryPosY;
    delete[] m_bathymetry;
    delete[] m_displacementsPosX;
    delete[] m_displacementsPosY;
    delete[] m_displacement;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getHeight(t_real i_x,
                                                                   t_real i_y) const {
    t_real l_offsetX = m_epicenterOffsetX;
    t_real l_offsetY = m_epicenterOffsetY;

    i_x += l_offsetX;
    i_y += l_offsetY;

    t_idx l_gridIdxX = 0;
    t_idx l_gridIdxY = 0;
    t_real l_gridX = m_bathymetryPosX[0];
    t_real l_gridY = m_bathymetryPosY[0];

    for (t_idx l_i = 1; l_i < m_bathymetryDimX; l_i++) {
        if (fabs(i_x - l_gridX) > fabs(i_x - m_bathymetryPosX[l_i])) {
            l_gridX = m_bathymetryPosX[l_i];
            l_gridIdxX = l_i;
        }
    }

    for (t_idx l_i = 1; l_i < m_bathymetryDimY; l_i++) {
        if (fabs(i_y - l_gridY) > fabs(i_y - m_bathymetryPosY[l_i])) {
            l_gridY = m_bathymetryPosY[l_i];
            l_gridIdxY = l_i;
        }
    }

    t_idx l_mappedGridIdx = l_gridIdxY * m_bathymetryDimX + l_gridIdxX;
    if (m_bathymetry[l_mappedGridIdx] < 0) {
        return std::max(-m_bathymetry[l_mappedGridIdx], m_delta);
    }
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getMomentumX(t_real,
                                                                      t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getMomentumY(t_real,
                                                                      t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getBathymetry(t_real i_x,
                                                                       t_real i_y) const {
    t_real l_offsetX = m_epicenterOffsetX;
    t_real l_offsetY = m_epicenterOffsetY;

    i_x += l_offsetX;
    i_y += l_offsetY;

    t_idx l_gridIdxX = 0;
    t_idx l_gridIdxY = 0;
    t_real l_gridX = m_bathymetryPosX[0];
    t_real l_gridY = m_bathymetryPosY[0];

    for (t_idx l_i = 1; l_i < m_bathymetryDimX; l_i++) {
        if (fabs(i_x - l_gridX) > fabs(i_x - m_bathymetryPosX[l_i])) {
            l_gridX = m_bathymetryPosX[l_i];
            l_gridIdxX = l_i;
        }
    }

    for (t_idx l_i = 1; l_i < m_bathymetryDimY; l_i++) {
        if (fabs(i_y - l_gridY) > fabs(i_y - m_bathymetryPosY[l_i])) {
            l_gridY = m_bathymetryPosY[l_i];
            l_gridIdxY = l_i;
        }
    }

    t_idx l_mappedGridIdx = l_gridIdxY * m_bathymetryDimX + l_gridIdxX;

    t_idx l_mappedDispGridIdx = l_gridIdxY * m_displacementsDimX + l_gridIdxX;

    // get possible displacement
    t_real l_displacement = m_displacement[l_mappedDispGridIdx];

    if (m_bathymetry[l_mappedGridIdx] < 0) {
        return std::min(m_bathymetry[l_mappedGridIdx], -m_delta) + l_displacement;
    } else {
        return std::max(m_bathymetry[l_mappedGridIdx], m_delta) + l_displacement;
    }
}