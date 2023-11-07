/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * One-dimensional wave propagation patch.
 **/
#include "WavePropagation1d.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include "../solvers/f-wave/F_wave.h"
#include "../solvers/roe/Roe.h"

tsunami_lab::patches::WavePropagation1d::WavePropagation1d(t_idx i_nCells)
{
    m_nCells = i_nCells;
    // allocate memory including a single ghost cell on each side and initializing with 0
    for (unsigned short l_st = 0; l_st < 2; l_st++)
    {
        m_h[l_st] = new t_real[m_nCells + 2]{0};
        m_hu[l_st] = new t_real[m_nCells + 2]{0};
    }
    m_b = new t_real[m_nCells + 2]{0};
}

tsunami_lab::patches::WavePropagation1d::~WavePropagation1d()
{
    for (unsigned short l_st = 0; l_st < 2; l_st++)
    {
        delete[] m_h[l_st];
        delete[] m_hu[l_st];
    }
}

void tsunami_lab::patches::WavePropagation1d::timeStep(t_real i_scaling, std::string solver_choice)
{
    // pointers to old and new data
    t_real *l_hOld = m_h[m_step];
    t_real *l_huOld = m_hu[m_step];

    m_step = (m_step + 1) % 2;
    t_real *l_hNew = m_h[m_step];
    t_real *l_huNew = m_hu[m_step];

    t_real *l_b = m_b;

    // init new cell quantities
    for (t_idx l_ce = 1; l_ce < m_nCells + 1; l_ce++)
    {
        l_hNew[l_ce] = l_hOld[l_ce];
        l_huNew[l_ce] = l_huOld[l_ce];
    }

    // iterate over edges and update with Riemann solutions
    for (t_idx l_ed = 0; l_ed < m_nCells + 1; l_ed++)
    {
        // determine left and right cell-id
        t_idx l_ceL = l_ed;
        t_idx l_ceR = l_ed + 1;

        // compute net-updates
        t_real l_netUpdates[2][2];

        if (solver_choice == "roe")
        {
            solvers::Roe::netUpdates(l_hOld[l_ceL],
                                     l_hOld[l_ceR],
                                     l_huOld[l_ceL],
                                     l_huOld[l_ceR],
                                     l_netUpdates[0],
                                     l_netUpdates[1]);
        }
        else if (solver_choice == "fwave")
        {
            solvers::FWave::netUpdates(l_hOld[l_ceL],
                                       l_hOld[l_ceR],
                                       l_huOld[l_ceL],
                                       l_huOld[l_ceR],
                                       l_b[l_ceL],
                                       l_b[l_ceR],
                                       l_netUpdates[0],
                                       l_netUpdates[1]);
        }
        else
        {
            throw std::invalid_argument("Not a valid solver. Try again with either 'roe' or 'fwave'.");
        }

        // update the cells' quantities
        l_hNew[l_ceL] -= i_scaling * l_netUpdates[0][0];
        l_huNew[l_ceL] -= i_scaling * l_netUpdates[0][1];

        l_hNew[l_ceR] -= i_scaling * l_netUpdates[1][0];
        l_huNew[l_ceR] -= i_scaling * l_netUpdates[1][1];
    }
}

void tsunami_lab::patches::WavePropagation1d::setGhostOutflow()
{
    t_real *l_h = m_h[m_step];
    t_real *l_hu = m_hu[m_step];
    t_real *l_b = m_b;

    // set left boundary
    l_h[0] = l_h[1];
    l_hu[0] = l_hu[1];
    l_b[0] = l_b[1];

    // set right boundary
    l_h[m_nCells + 1] = l_h[m_nCells];
    l_hu[m_nCells + 1] = l_hu[m_nCells];
    l_b[m_nCells + 1] = l_b[m_nCells];
}