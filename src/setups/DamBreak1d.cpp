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
 * One-dimensional dam break problem.
 **/
#include "DamBreak1d.h"

tsunami_lab::setups::DamBreak1d::DamBreak1d( t_real i_heightLeft,
                                             t_real i_heightRight,
                                             t_real i_locationDam ) {
  m_heightLeft = i_heightLeft;
  m_heightRight = i_heightRight;
  m_locationDam = i_locationDam;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak1d::getHeight( t_real i_x,
                                                                t_real      ) const {
  if( i_x < m_locationDam ) {
    return m_heightLeft;
  }
  else {
    return m_heightRight;
  }
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak1d::getMomentumX( t_real,
                                                                   t_real ) const {
  return 0;
}

tsunami_lab::t_real tsunami_lab::setups::DamBreak1d::getMomentumY( t_real,
                                                                   t_real ) const {
  return 0;
}