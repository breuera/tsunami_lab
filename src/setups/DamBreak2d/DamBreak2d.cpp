/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Two-dimensional dam break problem.
 **/

#include "DamBreak2d.h"

#include <cmath>

tsunami_lab::setups::DamBreak2d::DamBreak2d(t_real i_innerHeight,
                                            t_real i_outerHeight,
                                            t_real i_simLenX,
                                            t_real i_simLenY,
                                            t_real i_damLimit) {
    m_innerHeight = i_innerHeight;
    m_outerHeight = i_outerHeight;
    m_simLenX = i_simLenX;
    m_simLenY = i_simLenY;
    m_damLimit = i_damLimit;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getHeight(t_real i_x,
                                                               t_real i_y) const {
    t_real l_x = i_x - (m_simLenX / 2);
    t_real l_y = i_y - (m_simLenY / 2);
    if (sqrt(pow(l_x, 2) + pow(l_y, 2)) < m_damLimit) {
        return 10 + fabs(getBathymetry(i_x, i_y));
    } else {
        return 5 + fabs(getBathymetry(i_x, i_y));
    }
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getMomentumX(t_real,
                                                                  t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getMomentumY(t_real,
                                                                  t_real) const {
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getBathymetry(t_real i_x,
                                                                   t_real i_y) const {
    bool l_inRangeX = 0.3 * m_simLenX < i_x && 0.4 * m_simLenX > i_x;
    bool l_inRangeY = 0.3 * m_simLenY < i_y && 0.4 * m_simLenY > i_y;

    if (l_inRangeX && l_inRangeY) {
        return -2;
    } else {
        return -10;
    }
}
