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

tsunami_lab::setups::ArtificialTsunami2d::ArtificialTsunami2d(t_real i_simLenX,
                                                              t_real i_simLenY) {
    m_simLenX = i_simLenX;
    m_simLenY = i_simLenY;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getHeight(t_real,
                                                                        t_real) const {
    if (m_bIn < 0) {
        return std::max((-m_bIn), m_delta);
    } else {
        return 0;
    }
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getMomentumX(t_real,
                                                                           t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getMomentumY(t_real,
                                                                           t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getBathymetry(t_real i_x,
                                                                            t_real i_y) const {
    t_real l_offsetX = -(m_simLenX / 2);
    t_real l_offsetY = -(m_simLenY / 2);

    t_real l_dispDomainStart = -((m_simLenX * 0.1) / 2);
    t_real l_dispDomainEnd = ((m_simLenX * 0.1) / 2);

    bool l_isInDomainX = (i_x + l_offsetX) > l_dispDomainStart && (i_x + l_offsetX) < l_dispDomainEnd;
    bool l_isInDomainY = (i_y + l_offsetY) > l_dispDomainStart && (i_y + l_offsetY) < l_dispDomainEnd;
    bool l_setDisplacement = l_isInDomainX && l_isInDomainY;
    std::cout << (i_x + l_offsetX) << ", " << i_y + l_offsetY << ", " << l_isInDomainX << "/" << l_isInDomainY << std::endl;
    t_real l_dxy = 0;
    if (l_setDisplacement) {
        t_real l_fx = std::sin(((i_x / 500) + 1) * C_PI);
        t_real l_gx = -std::pow((i_y / 500), 2) + 1;
        l_dxy = 5 * l_fx * l_gx;
    }

    if (m_bIn < 0) {
        return std::min(m_bIn, -m_delta) + l_dxy;
    } else {
        return std::max(m_bIn, m_delta) + l_dxy;
    }
}