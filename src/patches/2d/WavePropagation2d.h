/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Two-dimensional wave propagation patch.
 **/
#ifndef TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_2D
#define TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_2D

#include "../WavePropagation.h"

namespace tsunami_lab {
    namespace patches {
        class WavePropagation2d;
    }
}  // namespace tsunami_lab

class tsunami_lab::patches::WavePropagation2d : public WavePropagation {
   private:
    //! current step which indicates the active values in the arrays below
    unsigned short m_step = 0;

    //! number of cells in x-direction discretizing the computational domain
    t_idx m_nCellsX = 0;

    //! number of cells in y-direction discretizing the computational domain
    t_idx m_mCellsY = 0;

    //! water heights for the current and next time step for all cells
    t_real *m_h[2] = {nullptr, nullptr};

    //! momenta in x-direction for the current and next time step for all cells
    t_real *m_hu[2] = {nullptr, nullptr};

    //! momenta in y-direction for the current and next time step for all cells
    t_real *m_hv[2] = {nullptr, nullptr};

    //! bathymetries for all cells
    t_real *m_b = nullptr;

   public:
    /**
     * Constructs the 2d wave propagation solver.
     *
     * @param i_nCellsX number of cells in x-direction.
     * @param i_nCellsY number of cells in y-direction.
     **/
    WavePropagation2d(t_idx i_nCellsX, t_idx i_nCellsY);

    /**
     * Destructor which frees all allocated memory.
     **/
    ~WavePropagation2d();

    /**
     * Performs a time step.
     *
     * @param i_scalingX scaling of the time step (dt / dx).
     * @param i_scalingY scaling of the time step (dt / dy).
     **/
    void timeStep(t_real i_scalingX,
                  t_real i_scalingY);
};

#endif