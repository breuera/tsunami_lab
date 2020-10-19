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
 * Base class of the wave propagation patches.
 **/
#ifndef TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION
#define TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION

#include "../constants.h"

namespace tsunami_lab {
  namespace patches {
    class WavePropagation;
  }
}

class tsunami_lab::patches::WavePropagation {
  public:
    /**
     * Virtual destructor for base class.
     **/
    virtual ~WavePropagation(){};

    /**
     * Performs a time step.
     *
     * @param i_scaling scaling of the time step.
     **/
    virtual void timeStep( t_real i_scaling ) = 0;

    /**
     * Sets the values of the ghost cells according to outflow boundary conditions.
     **/
    virtual void setGhostOutflow() = 0;

    /**
     * Gets the stride in y-direction. x-direction is stride-1.
     *
     * @return stride in y-direction.
     **/
    virtual t_idx getStride() = 0;

    /**
     * Gets cells' water heights.
     *
     * @return water heights.
     */
    virtual t_real const * getHeight() = 0;

    /**
     * Gets the cells' momenta in x-direction.
     *
     * @return momenta in x-direction.
     **/
    virtual t_real const * getMomentumX() = 0;

    /**
     * Gets the cells' momenta in y-direction.
     *
     * @return momenta in y-direction.
     **/
    virtual t_real const * getMomentumY() = 0;

    /**
     * Sets the height of the cell to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_h water height.
     **/
    virtual void setHeight( t_idx  i_ix,
                            t_idx  i_iy,
                            t_real i_h ) = 0;

    /**
     * Sets the momentum in x-direction to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_hu momentum in x-direction.
     **/
    virtual void setMomentumX( t_idx  i_ix,
                               t_idx  i_iy,
                               t_real i_hu ) = 0;

    /**
     * Sets the momentum in y-direction to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_hv momentum in y-direction.
     **/
    virtual void setMomentumY( t_idx  i_ix,
                               t_idx  i_iy,
                               t_real i_hv ) = 0;
};

#endif