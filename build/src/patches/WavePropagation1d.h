/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional wave propagation patch.
 **/
#ifndef TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_1D
#define TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_1D

#include "WavePropagation.h"

namespace tsunami_lab {
  namespace patches {
    class WavePropagation1d;
  }
}

class tsunami_lab::patches::WavePropagation1d: public WavePropagation {
  private:
    //! current step which indicates the active values in the arrays below
    unsigned short m_step = 0;

    //! number of cells discretizing the computational domain
    t_idx m_nCells = 0;

    //! water heights for the current and next time step for all cells
    t_real * m_h[2] = { nullptr, nullptr };

    //! momenta for the current and next time step for all cells
    t_real * m_hu[2] = { nullptr, nullptr };

  public:
    /**
     * Constructs the 1d wave propagation solver.
     *
     * @param i_nCells number of cells.
     **/
    WavePropagation1d( t_idx i_nCells );

    /**
     * Destructor which frees all allocated memory.
     **/
    ~WavePropagation1d();

    /**
     * Performs a time step.
     *
     * @param i_scaling scaling of the time step (dt / dx).
     **/
    void timeStep( t_real i_scaling );

    /**
     * Sets the values of the ghost cells according to outflow boundary conditions.
     **/
    void setGhostOutflow();

    /**
     * Gets the stride in y-direction. x-direction is stride-1.
     *
     * @return stride in y-direction.
     **/
    t_idx getStride(){
      return m_nCells+2;
    }

    /**
     * Gets cells' water heights.
     *
     * @return water heights.
     */
    t_real const * getHeight(){
      return m_h[m_step]+1;
    }

    /**
     * Gets the cells' momenta in x-direction.
     *
     * @return momenta in x-direction.
     **/
    t_real const * getMomentumX(){
      return m_hu[m_step]+1;
    }

    /**
     * Dummy function which returns a nullptr.
     **/
    t_real const * getMomentumY(){
      return nullptr;
    }

    /**
     * Sets the height of the cell to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_h water height.
     **/
    void setHeight( t_idx  i_ix,
                    t_idx,
                    t_real i_h ) {
      m_h[m_step][i_ix+1] = i_h;
    }

    /**
     * Sets the momentum in x-direction to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_hu momentum in x-direction.
     **/
    void setMomentumX( t_idx  i_ix,
                       t_idx,
                       t_real i_hu ) {
      m_hu[m_step][i_ix+1] = i_hu;
    }

    /**
     * Dummy function since there is no y-momentum in the 1d solver.
     **/
    void setMomentumY( t_idx,
                       t_idx,
                       t_real ) {};
};

#endif