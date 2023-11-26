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

tsunami_lab::setups::TsunamiEvent2d::TsunamiEvent2d(t_real *in_bathymetry,
                                                    t_real *in_rawX_bathymetry,
                                                    t_idx in_dimX_bathymetry,
                                                    t_real *in_rawY_bathymetry,
                                                    t_idx in_dimY_bathymetry,
                                                    t_real *in_displacement,
                                                    t_real *in_rawX_displacement,
                                                    t_idx in_dimX_displacement,
                                                    t_real *in_rawY_displacement,
                                                    t_idx in_dimY_displacement) {
    m_bathymetry = in_bathymetry;
    m_rawX_bathymetry = in_rawX_bathymetry;
    m_dimX_bathymetry = in_dimX_bathymetry;
    m_rawY_bathymetry = in_rawY_bathymetry;
    m_dimY_bathymetry = in_dimY_bathymetry;
    m_displacement = in_displacement;
    m_rawX_displacement = in_rawX_displacement;
    m_dimX_displacement = in_dimX_displacement;
    m_rawY_displacement = in_rawY_displacement;
    m_dimY_displacement = in_dimY_displacement;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getHeight(t_real in_x,
                                                                   t_real in_y,
                                                                   t_real) const {
    // convert scaled x,y to given values from netCDF
    // simple unoptimzed solution: iterate over array and store index of nearest Value
    int nearestValueX = 0;
    int nearestValueY = 0;
    for (int i = 1; i < m_dimX_bathymetry; i++) {
        if (fabs(m_rawX_bathymetry[i] - in_x) < fabs(m_rawX_bathymetry[nearestValueX] - in_x)) {
            nearestValueX = i;
        }
    }

    for (int i = 1; i < m_dimY_bathymetry; i++) {
        if (fabs(m_rawX_bathymetry[i] - in_x) < fabs(m_rawX_bathymetry[nearestValueY] - in_x)) {
            nearestValueY = i;
        }
    }

    if (m_bathymetry[nearestValueX] < 0) {
        return (-m_bathymetry[(t_idx)floor(in_x / 250)] < 20) ? 20 : -m_bathymetry[(t_idx)floor(in_x / 250)];
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

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getBathymetry(t_real in_x,
                                                                       t_real in_y,
                                                                       t_real) const {
    // convert scaled x,y to given values from netCDF
    // simple unoptimzed solution: iterate over array and store index of nearest Value
    int nearestValueX = 0;
    int nearestValueY = 0;
    for (int i = 1; i < m_dimX_bathymetry; i++) {
        if (fabs(m_rawX_bathymetry[i] - in_x) < fabs(m_rawX_bathymetry[nearestValueX] - in_x)) {
            nearestValueX = i;
        }
    }

    for (int i = 1; i < m_dimY_bathymetry; i++) {
        if (fabs(m_rawY_bathymetry[i] - in_y) < fabs(m_rawY_bathymetry[nearestValueY] - in_y)) {
            nearestValueY = i;
        }
    }

    int newCord = nearestValueY
    
    //
    if (m_bathymetry[?] < 0) {
        return !(m_bathymetry[?] < -20) ? -20 + m_displacement[?] : m_bathymetry[?] + m_displacement[?];
    }
    else {
        return (m_bathymetry[?] < 20) ? 20 + m_displacement[?] : m_bathymetry[?] + m_displacement[?];
    }
}