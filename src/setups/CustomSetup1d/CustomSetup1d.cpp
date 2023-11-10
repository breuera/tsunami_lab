/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/
#include "CustomSetup1d.h"

tsunami_lab::setups::CustomSetup1d::CustomSetup1d(  t_real i_hL,
                                                    t_real i_hR,
                                                    t_real i_huL,
                                                    t_real i_huR,
                                                    t_real i_locMiddle) 
{
    m_heightLeft = i_hL;
    m_heightRight = i_hR;
    m_momentumLeft = i_huL;
    m_momentumRight = i_huR;
    m_locationMiddle = i_locMiddle;
}

tsunami_lab::t_real tsunami_lab::setups::CustomSetup1d::getHeight( t_real i_x,
                                                                   t_real      ) const 
{
    if(i_x < m_locationMiddle) 
    {
        return m_heightLeft;
    } 
    else {
        return m_heightRight;
    }
}

tsunami_lab::t_real tsunami_lab::setups::CustomSetup1d::getMomentumX( t_real i_x,
                                                                      t_real ) const 
{
    if(i_x < m_locationMiddle) 
    {
        return m_momentumLeft;
    } 
    else {
        return m_momentumRight;
    }
}

tsunami_lab::t_real tsunami_lab::setups::CustomSetup1d::getMomentumY( t_real,
                                                                      t_real ) const 
{
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::CustomSetup1d::getBathymetry( t_real,
                                                                       t_real ) const 
{
    return 0;
}