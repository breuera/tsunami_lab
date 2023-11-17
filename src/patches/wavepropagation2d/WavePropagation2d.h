/**
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional wave propagation patch.
 **/
#ifndef TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_2D
#define TSUNAMI_LAB_PATCHES_WAVE_PROPAGATION_2D

#include <string>
#include <vector>

#include "../WavePropagation.h"

namespace tsunami_lab
{
    namespace patches
    {
        class WavePropagation2d;
    }
} // namespace tsunami_lab

class tsunami_lab::patches::WavePropagation2d : public WavePropagation
{
private:
    //! current step which indicates the active values in the arrays below
    unsigned short m_step = 0;

    //! number of cells in x-direction discretizing the computational domain
    t_idx m_nCells_x = 0;

    //! number of cells in y-direction discretizing the computational domain
    t_idx m_nCells_y = 0;

    //! choice of solver, 0 = roe, 1 = fwave
    int m_solver_choice = 0;

    //! state of left boundary, 0 = open, 1 = closed
    int m_state_boundary_left = 0;

    //! state of right boundary, 0 = open, 1 = closed
    int m_state_boundary_right = 0;

    //! state of top boundary, 0 = open, 1 = closed
    int m_state_boundary_top = 0;

    //! state of bottom boundary, 0 = open, 1 = closed
    int m_state_boundary_bottom = 0;

    //! water heights for the current and next time step for all cells
    // t_real *m_h[2] = {nullptr, nullptr};
    t_real **m_h[2];
    //! momenta for the current and next time step for all cells in x-direction
    t_real **m_hu[2];
    //! momenta for the current and next time step for all cells in y-direction
    t_real **m_hv[2];

    //! bathymetry for all cells
    t_real **m_b;

public:
    /**
     *
     * Constructs the 1d wave propagation solver.
     *
     * @param i_nCells_x number of cells in x-direction.
     * @param i_nCells_y number of cells in y-direction.
     * @param solver_choice type int, defines the choice of solver. Possible values: 0 for "roe" and 1 for "fwave".
     * @param state_boundary_left type int, defines the state of the left boundary. Possible values: 0 = "open" and 1 = "closed".
     * @param state_boundary_right type int, defines the state of the right boundary. Possible values: 0 = "open" and 1 = "closed".
     * @param state_boundary_top type int, defines the state of the top boundary. Possible values: 0 = "open" and 1 = "closed".
     * @param state_boundary_bottom type int, defines the state of the bottom boundary. Possible values: 0 = "open" and 1 = "closed".
     **/
    WavePropagation2d(t_idx i_nCells_x,
                      t_idx i_nCells_y,
                      int solver_choice,
                      int state_boundary_left,
                      int state_boundary_right,
                      int state_boundary_top,
                      int state_boundary_bottom);

    /**
     * Destructor which frees all allocated memory.
     **/
    ~WavePropagation2d();

    /**
     * Performs a time step.
     *
     * @param i_scaling scaling of the time step (dt / dx).
     **/
    void timeStep(t_real i_scaling);

    /**
     * Sets the values of the ghost cells according to outflow boundary conditions.
     **/
    void setGhostOutflow();

    /**
     * Gets the stride in y-direction. x-direction is stride-1.
     *
     * @return stride in y-direction.
     **/
    t_idx getStride()
    {
        return m_nCells_y + 2;
    }

    /**
     * Gets cells' water heights.
     *
     * @return water heights.
     */
    t_real const *getHeight()
    {
        return m_h[m_step] + 1;
    }

    /**
     * Gets the cells' momenta in x-direction.
     *
     * @return momenta in x-direction.
     **/
    t_real const *getMomentumX()
    {
        return m_hu[m_step] + 1;
    }

    /**
     * Dummy function which returns a nullptr.
     **/
    t_real const *getMomentumY()
    {
        return m_hv[m_step] + 1;
    }

    /**
     * Gets the cells' bathymetry.
     *
     * @return bathymetry.
     **/
    t_real const *getBathymetry()
    {
        return m_b + 1;
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
                   t_real i_h)
    {
        m_h[m_step][i_ix + 1][i_iy + 1] = i_h;
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
                      t_real i_hu)
    {
        m_hu[m_step][i_ix + 1][i_iy + 1] = i_hu;
    }

    /**
     * Dummy function since there is no y-momentum in the 1d solver.
     **/
    void setMomentumY(t_idx i_ix,
                      t_idx i_iy,
                      t_real i_hv)
    {
        m_hv[m_step][i_ix + 1][i_iy + 1] = i_hv;
    }

    /**
     * @brief Set the bathymetry
     *
     * @param i_ix id of the cell in x-direction.
     * @param i_iy id of the cell in y-direction.
     * @param i_b bathymetry
     */
    void setBathymetry(t_idx i_ix,
                       t_idx i_iy,
                       t_real i_b)
    {
        m_b[i_ix + 1][i_iy + 1] = i_b;
    }
};

#endif