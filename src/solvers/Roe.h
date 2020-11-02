/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 * 
 * @section LICENSE
 * Copyright 2020, Friedrich Schiller University Jena
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 * Roe Riemann solver for the one-dimensional shallow water equations.
 **/
#ifndef TSUNAMI_LAB_SOLVERS_ROE
#define TSUNAMI_LAB_SOLVERS_ROE

#include "../constants.h"

namespace tsunami_lab {
  namespace solvers {
    class Roe;
  }
}

class tsunami_lab::solvers::Roe {
  private:
    //! square root of gravity
    static t_real constexpr m_gSqrt = 3.131557121;

    /**
     * Computes the wave speeds.
     *
     * @param i_hL height of the left side.
     * @param i_hR height of the right side.
     * @param i_uL particle velocity of the leftside.
     * @param i_uR particles velocity of the right side.
     * @param o_waveSpeedL will be set to the speed of the wave propagating to the left.
     * @param o_waveSpeedR will be set to the speed of the wave propagating to the right.
     **/
    static void waveSpeeds( t_real   i_hL,
                            t_real   i_hR,
                            t_real   i_uL,
                            t_real   i_uR,
                            t_real & o_waveSpeedL,
                            t_real & o_waveSpeedR );

    /**
     * Computes the wave strengths.
     *
     * @param i_hL height of the left side.
     * @param i_hR height of the right side.
     * @param i_huL momentum of the left side.
     * @param i_huR momentum of the right side.
     * @param i_waveSpeedL speed of the wave propagating to the left.
     * @param i_waveSpeedR speed of the wave propagating to the right.
     * @param o_strengthL will be set to the strength of the wave propagating to the left.
     * @param o_strengthR will be set to the strength of the wave propagating to the right.
     **/
    static void waveStrengths( t_real   i_hL,
                               t_real   i_hR,
                               t_real   i_huL,
                               t_real   i_huR,
                               t_real   i_waveSpeedL,
                               t_real   i_waveSpeedR,
                               t_real & o_strengthL,
                               t_real & o_strengthR );

  public:
    /**
     * Computes the net-updates.
     *
     * @param i_hL height of the left side.
     * @param i_hR height of the right side.
     * @param i_huL momentum of the left side.
     * @param i_huR momentum of the right side.
     * @param o_netUpdateL will be set to the net-updates for the left side; 0: height, 1: momentum.
     * @param o_netUpdateR will be set to the net-updates for the right side; 0: height, 1: momentum.
     **/
    static void netUpdates( t_real i_hL,
                            t_real i_hR,
                            t_real i_huL,
                            t_real i_huR,
                            t_real o_netUpdateL[2],
                            t_real o_netUpdateR[2] );
};

#endif
