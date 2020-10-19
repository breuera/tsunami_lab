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
 * One-dimensional wave propagation patch.
 **/
#include "WavePropagation1d.h"
#include "../solvers/Roe.h"

tsunami_lab::patches::WavePropagation1d::WavePropagation1d( t_idx i_nCells ) {
  m_nCells = i_nCells;

  // allocate memory including a single ghost cell on each side
  for( unsigned short l_st = 0; l_st < 2; l_st++ ) {
    m_h[l_st] = new t_real[  m_nCells + 2 ];
    m_hu[l_st] = new t_real[ m_nCells + 2 ];
  }

  // init to zero
  for( unsigned short l_st = 0; l_st < 2; l_st++ ) {
    for( t_idx l_ce = 0; l_ce < m_nCells; l_ce++ ) {
      m_h[l_st][l_ce] = 0;
      m_hu[l_st][l_ce] = 0;
    }
  }
}

tsunami_lab::patches::WavePropagation1d::~WavePropagation1d() {
  for( unsigned short l_st = 0; l_st < 2; l_st++ ) {
    delete[] m_h[l_st];
    delete[] m_hu[l_st];
  }
}

void tsunami_lab::patches::WavePropagation1d::timeStep( t_real i_scaling ) {
  // pointers to old and new data
  t_real * l_hOld = m_h[m_step];
  t_real * l_huOld = m_hu[m_step];

  m_step = (m_step+1) % 2;
  t_real * l_hNew =  m_h[m_step];
  t_real * l_huNew = m_hu[m_step];

  // init new cell quantities
  for( t_idx l_ce = 1; l_ce < m_nCells+1; l_ce++ ) {
    l_hNew[l_ce] = l_hOld[l_ce];
    l_huNew[l_ce] = l_huOld[l_ce];
  }

  // iterate over edges and update with Riemann solutions
  for( t_idx l_ed = 0; l_ed < m_nCells+1; l_ed++ ) {
    // determine left and right cell-id
    t_idx l_ceL = l_ed;
    t_idx l_ceR = l_ed+1;

    // compute net-updates
    t_real l_netUpdates[2][2];

    solvers::Roe::netUpdates( l_hOld[l_ceL],
                              l_hOld[l_ceR],
                              l_huOld[l_ceL],
                              l_huOld[l_ceR],
                              l_netUpdates[0],
                              l_netUpdates[1] );

    // update the cells' quantities
    l_hNew[l_ceL]  -= i_scaling * l_netUpdates[0][0];
    l_huNew[l_ceL] -= i_scaling * l_netUpdates[0][1];

    l_hNew[l_ceR]  -= i_scaling * l_netUpdates[1][0];
    l_huNew[l_ceR] -= i_scaling * l_netUpdates[1][1];
  }
}

void tsunami_lab::patches::WavePropagation1d::setGhostOutflow() {
  t_real * l_h = m_h[m_step];
  t_real * l_hu = m_hu[m_step];

  // set left boundary
  l_h[0] = l_h[1];
  l_hu[0] = l_hu[1];

  // set right boundary
  l_h[m_nCells+1] = l_h[m_nCells];
  l_hu[m_nCells+1] = l_hu[m_nCells];
}