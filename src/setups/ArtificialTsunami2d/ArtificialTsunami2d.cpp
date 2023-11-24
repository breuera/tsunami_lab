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

tsunami_lab::setups::ArtificialTsunami2d::ArtificialTsunami2d(t_real in_simLenX,
                                                              t_real in_simLenY,
                                                              t_real) {
    m_simLenX = in_simLenX;
    m_simLenY = in_simLenY;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getHeight(t_real,
                                                                        t_real) const {
    // max(-bathymetry, delta(20m)) -> bathymetry constant -100 -> height constant 100
    return 100;
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
    t_real pi = 3.14159265358979323846;
    // displacement = 5 * g(x) * f(y)
    displacement = 5 * sin(((i_x / 500) + 1) * pi) * (-((i_y / 500) * (i_y / 500)) + 1);

    // theory: 10km x 10km -> mid at 5000m. if |midx - in_x| <= 500 return -100 + displacement, else -100

    t_real midx = in_x - (m_simLenX / 2);
    t_real midy = in_y - (m_simLenY / 2);

    if (abs(midx - in_x) <= 500 && abs(midy - in_y) <= 500) {
        return -100 + displacement;
    } else {
        return -100;
    }
}