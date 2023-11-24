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

tsunami_lab::setups::TsunamiEvent2d::TsunamiEvent2d(t_real *i_bathymetry,
                                                    t_real *i_displacement) {
    m_bathymetry = i_bathymetry;
    m_displacement = i_displacement;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent2d::getHeight(t_real in_x,
                                                                   t_real in_y,
                                                                   t_real) const {
    if (m_bathymetry < 0) {
        return (-m_bathymetry < 20) ? 20 : -m_bathymetry;
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
        int parsing = 0;
    if (m_bathymetry[(t_idx)floor(in_x / parsing)] < 0) {
        return !(m_bathymetry[(t_idx)floor(in_x / parsing)] < -20) ? -20 + m_displacement : m_bathymetry[(t_idx)floor(in_x / parsing)] + m_displacement;
    } else {
        return (m_bathymetry[(t_idx)floor(in_x / parsing)] < 20) ? 20 + m_displacement : m_bathymetry[(t_idx)floor(in_x / parsing)] + m_displacement;
    }
}