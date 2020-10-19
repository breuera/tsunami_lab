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
 * Roe Riemann solver for the shallow water equations.
 **/
#include "Roe.h"
#include <cmath>

void tsunami_lab::solvers::Roe::waveSpeeds( t_real   i_hL,
                                            t_real   i_hR,
                                            t_real   i_uL,
                                            t_real   i_uR,
                                            t_real & o_waveSpeedL,
                                            t_real & o_waveSpeedR ) {
  // pre-compute square-root ops
  t_real l_hSqrtL = std::sqrt( i_hL );
  t_real l_hSqrtR = std::sqrt( i_hR );

  // compute Roe averages
  t_real l_hRoe = 0.5f * ( i_hL + i_hR );
  t_real l_uRoe = l_hSqrtL * i_uL + l_hSqrtR * i_uR;
  l_uRoe /= l_hSqrtL + l_hSqrtR;

  // compute wave speeds
  t_real l_ghSqrtRoe = m_gSqrt * std::sqrt( l_hRoe );
  o_waveSpeedL = l_uRoe - l_ghSqrtRoe;
  o_waveSpeedR = l_uRoe + l_ghSqrtRoe;
}

void tsunami_lab::solvers::Roe::waveStrengths( t_real   i_hL,
                                               t_real   i_hR,
                                               t_real   i_huL,
                                               t_real   i_huR,
                                               t_real   i_waveSpeedL,
                                               t_real   i_waveSpeedR,
                                               t_real & o_strengthL,
                                               t_real & o_strengthR ) {
  // compute inverse of right eigenvector-matrix
  t_real l_detInv = 1 / (i_waveSpeedR - i_waveSpeedL);

  t_real l_rInv[2][2] = {0};
  l_rInv[0][0] =  l_detInv * i_waveSpeedR;
  l_rInv[0][1] = -l_detInv;
  l_rInv[1][0] = -l_detInv * i_waveSpeedL;
  l_rInv[1][1] =  l_detInv;

  // compute jump in quantities
  t_real l_hJump  = i_hR  - i_hL;
  t_real l_huJump = i_huR - i_huL;

  // compute wave strengths
  o_strengthL  = l_rInv[0][0] * l_hJump;
  o_strengthL += l_rInv[0][1] * l_huJump;

  o_strengthR  = l_rInv[1][0] * l_hJump;
  o_strengthR += l_rInv[1][1] * l_huJump;
}

void tsunami_lab::solvers::Roe::netUpdates( t_real i_hL,
                                            t_real i_hR,
                                            t_real i_huL,
                                            t_real i_huR,
                                            t_real o_netUpdateL[2],
                                            t_real o_netUpdateR[2] ) {
  // compute particle velocities
  t_real l_uL = i_huL / i_hL;
  t_real l_uR = i_huR / i_hR;

  // compute wave speeds
  t_real l_sL = 0;
  t_real l_sR = 0;

  waveSpeeds( i_hL,
              i_hR,
              l_uL,
              l_uR,
              l_sL,
              l_sR );

  // compute wave strengths
  t_real l_aL = 0;
  t_real l_aR = 0;

  waveStrengths( i_hL,
                 i_hR,
                 i_huL,
                 i_huR,
                 l_sL,
                 l_sR,
                 l_aL,
                 l_aR );

  // compute scaled waves
  t_real l_waveL[2] = {0};
  t_real l_waveR[2] = {0};

  l_waveL[0] = l_sL * l_aL;
  l_waveL[1] = l_sL * l_aL * l_sL;

  l_waveR[0] = l_sR * l_aR;
  l_waveR[1] = l_sR * l_aR * l_sR;

  // set net-updates depending on wave speeds
  for( unsigned short l_qt = 0; l_qt < 2; l_qt++ ) {
    // init
    o_netUpdateL[l_qt] = 0;
    o_netUpdateR[l_qt] = 0;

    // 1st wave
    if( l_sL < 0 ) {
      o_netUpdateL[l_qt] = l_waveL[l_qt];
    }
    else {
      o_netUpdateR[l_qt] = l_waveL[l_qt];
    }

    // 2nd wave
    if( l_sR > 0 ) {
      o_netUpdateR[l_qt] = l_waveR[l_qt];
    }
    else {
      o_netUpdateL[l_qt] = l_waveR[l_qt];
    }
  }
}