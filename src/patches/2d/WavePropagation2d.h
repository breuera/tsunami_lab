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

    //! number of overall cells discretizing the computational domain including ghost cells
    t_idx m_mnCells = 0;

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
     * Calculate linear position from 2d coordinates.
     *
     * @param i_x x coordinate of queried point.
     * @param i_y y coordinate of queried point.
     */
    t_idx getIndex(t_idx i_x, t_idx i_y);

    /**
     * Performs a time step.
     *
     * @param i_scalingX scaling of the time step (dt / dx).
     * @param i_scalingY scaling of the time step (dt / dy).
     **/
    void timeStep(t_real i_scalingX,
                  t_real i_scalingY);

    /**
     * Sets the values of the ghost cells according to entered outflow boundary conditions.
     *
     * @param i_setting defines the boundary condition.
     **/
    void setGhostCells(std::string i_setting);

    /**
     * Gets the stride in y-direction. x-direction is stride-1.
     *
     * @return stride in y-direction.
     **/
    t_idx getStride() {
        return m_nCellsX + 2;
    }

    /**
     * Gets cells' water heights.
     *
     * @return water heights.
     */
    t_real const *getHeight() {
        return m_h[m_step];
    }

    /**
     * Gets the cells' momenta in x-direction.
     *
     * @return momenta in x-direction.
     **/
    t_real const *getMomentumX() {
        return m_hu[m_step];
    }

    /**
     * Gets the cells' momenta in y-direction.
     *
     * @return momenta in y-direction.
     **/
    t_real const *getMomentumY() {
        return m_hv[m_step];
    }

    /**
     * Gets the cells bathymetries;
     *
     * @return bathymetries.
     */
    t_real const *getBathymetry() {
        return m_b;
    }

    /**
     * Sets the height of the cell to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_h water height.
     **/
    void setHeight(t_idx i_ix,
                   t_idx i_iy,
                   t_real i_h) {
        t_idx l_idx = getIndex(i_ix + 1, i_iy + 1);
        m_h[m_step][l_idx] = i_h;
    }

    /**
     * Sets the momentum in x-direction to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_hu momentum in x-direction.
     **/
    void setMomentumX(t_idx i_ix,
                      t_idx i_iy,
                      t_real i_hu) {
        t_idx l_idx = getIndex(i_ix + 1, i_iy + 1);
        m_hu[m_step][l_idx] = i_hu;
    }

    /**
     * Sets the momentum in y-direction to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_hv momentum in y-direction.
     **/
    void setMomentumY(t_idx i_ix,
                      t_idx i_iy,
                      t_real i_hv) {
        t_idx l_idx = getIndex(i_ix + 1, i_iy + 1);
        m_hv[m_step][l_idx] = i_hv;
    };

    /**
     * Sets the bathymetry to the given value.
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_ix id of the cell in y-direction.
     * @param i_b bathymetry.
     **/
    void setBathymetry(t_idx i_ix,
                       t_idx i_iy,
                       t_real i_b) {
        t_idx l_idx = getIndex(i_ix + 1, i_iy + 1);
        m_b[l_idx] = i_b;
    }
};

#endif