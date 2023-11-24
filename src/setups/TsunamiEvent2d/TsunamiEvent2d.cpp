/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Artificial 2d Tsunami setup.
 **/
#include "ArtificialTsunami2d.h"

#include <algorithm>
#include <cmath>
#include <iostream>

tsunami_lab::setups::ArtificialTsunami2d::ArtificialTsunami2d(t_real *i_bathymetry) {
    m_bathymetry = i_bathymetry;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getHeight(t_real in_x,
                                                                        t_real in_y,
                                                                        t_real) const {
    if (m_bathymetry < 0) {
        return (-m_bathymetry < 20) ? 20 : -m_bathymetry;
    }

    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getMomentumX(t_real,
                                                                           t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getMomentumY(t_real,
                                                                           t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getBathymetry(t_real in_x,
                                                                            t_real in_y,
                                                                            t_real) const {
    t_real displacement = 0;
    int delta = 20;
    t_real pi = 3.14159265358979323846;
    // displacement = 5 * g(x) * f(y)
    displacement = 5 * sin(((i_x / 500) + 1) * pi) * (-((i_y / 500) * (i_y / 500)) + 1);

    if (m_bathymetry < 0) {
        return !(m_bathymetry < -delta) ? -delta + displacement : m_bathymetry + displacement;
    } else {
        return (m_bathymetry < delta) ? delta + displacement : m_bathymetry + displacement;
    }
}