/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional custum roe problem.
 **/
#include "TsunamiEvent1d.h"
#include <algorithm>
#include <iostream>
#include <cmath>

tsunami_lab::setups::TsunamiEvent1d::TsunamiEvent1d(t_real i_bathymetry,
                                                    t_real i_distance,
                                                    t_real i_loacationMid)
{
    m_bathymetry = i_bathymetry;
    m_distance = i_distance;
    m_locattionMis = i_loacationMid;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getHeight( t_real i_x,
                                                                    t_real      ) const
{


    if (m_bathymetry < 0){
        return (-m_bathymetry<20)?20:-m_bathymetry;
    }

    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumX(  t_real,
                                                                        t_real ) const 
{
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumY(  t_real,
                                                                        t_real ) const 
{
    return 0;
}

tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetry( t_real i_x,
                                                                        t_real ) const 
{
    float d = 0;
    if ((175000 < i_x) && (i_x < 250000))
    {
        t_real pi = 3.14159265358979323846;
        d = 10 * sin(((i_x-175000)/37500)*pi+pi);
    }

    if (m_bathymetry < 0)
    {
       return !(m_bathymetry<-20)?-20+d:m_bathymetry+d; 
    }
    else
    {
        return (m_bathymetry<20)?20+d:m_bathymetry+d;  
    }
    
}