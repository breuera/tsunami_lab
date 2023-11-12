/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/
#include "TsunamiEvent1d.h"

#include <algorithm>
#include <cmath>
#include <iostream>

tsunami_lab::setups::TsunamiEvent1d::TsunamiEvent1d(t_real *i_bathymetry) {
    m_bathymetry = i_bathymetry;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getHeight(t_real i_x,
                                                                   t_real) const {
    if (m_bathymetry[(t_idx)i_x] < 0) {
        return (-m_bathymetry[(t_idx)i_x] < 20) ? 20 : -m_bathymetry[(t_idx)i_x];
    }

    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumX(t_real,
                                                                      t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumY(t_real,
                                                                      t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetry(t_real i_x,
                                                                       t_real) const {
    float d = 0;
    if ((175000 < i_x) && (i_x < 250000)) {
        t_real pi = 3.14159265358979323846;
        d = 10 * sin(((i_x - 175000) / 37500) * pi + pi);
    }

    if (m_bathymetry[(t_idx)i_x] < 0) {
        return !(m_bathymetry[(t_idx)i_x] < -20) ? -20 + d : m_bathymetry[(t_idx)i_x] + d;
    } else {
        return (m_bathymetry[(t_idx)i_x] < 20) ? 20 + d : m_bathymetry[(t_idx)i_x] + d;
    }
}