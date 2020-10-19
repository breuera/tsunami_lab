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
#ifndef TSUNAMI_LAB_SETUPS_DAM_BREAK_1D_H
#define TSUNAMI_LAB_SETUPS_DAM_BREAK_1D_H

#include "Setup.h"

namespace tsunami_lab {
  namespace setups {
    class DamBreak1d;
  }
}

/**
 * 1d dam break setup.
 **/
class tsunami_lab::setups::DamBreak1d: public Setup {
  private:
    //! height on the left side 
    t_real m_heightLeft = 0;
    
    //! height on the right side
    t_real m_heightRight = 0;

    //! location of the dam
    t_real m_locationDam = 0;

  public:
    /**
     * Constructor.
     *
     * @param i_heightLeft water height on the left side of the dam.
     * @param i_heightRight water height on the right side of the dam.
     * @param i_locationDam location (x-coordinate) of the dam.
     **/
    DamBreak1d( t_real i_heightLeft,
                t_real i_heightRight,
                t_real i_locationDam );

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getHeight( t_real i_x,
                      t_real      ) const;

    /**
     * Gets the momentum in x-direction.
     *
     * @return momentum in x-direction.
     **/
    t_real getMomentumX( t_real,
                         t_real ) const;

    /**
     * Gets the momentum in y-direction.
     *
     * @return momentum in y-direction.
     **/
    t_real getMomentumY( t_real,
                         t_real ) const;

};

#endif