/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custom problem.
 **/
#include "Custom1d.h"

tsunami_lab::setups::Custom1d::Custom1d(t_real i_heightLeft,
                                        t_real i_heightRight,
                                        t_real i_momentumLeft,
                                        t_real i_momentumRight,
                                        t_real i_middlePoint)
{
    m_heightLeft = i_heightLeft;
    m_heightRight = i_heightRight;
    m_momentumLeft = i_momentumLeft;
    m_momentumRight = i_momentumRight;
    m_middlePoint = i_middlePoint;
}

tsunami_lab::t_real tsunami_lab::setups::Custom1d::getHeight(t_real i_x,
                                                             t_real) const
{
    if (i_x < m_middlePoint)
    {
        return m_heightLeft;
    }
    else
    {
        return m_heightRight;
    }
}

tsunami_lab::t_real tsunami_lab::setups::Custom1d::getMomentumX(t_real i_x,
                                                                t_real) const
{
    if (i_x < m_middlePoint)
    {
        return m_momentumLeft;
    }
    else
    {
        return m_momentumRight;
    }
}

tsunami_lab::t_real tsunami_lab::setups::Custom1d::getMomentumY(t_real,
                                                                t_real) const
{
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::Custom1d::getBathymetry(t_real,
                                                                 t_real) const
{
    return 0;
}