/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Two-dimensional wave propagation patch.
 **/

#include "WavePropagation2d.h"

#include "../../solvers/FWave.h"

tsunami_lab::patches::WavePropagation2d::WavePropagation2d(t_idx i_nCellsX,
                                                           t_idx i_mCellsY) {
    m_nCellsX = i_nCellsX;
    m_mCellsY = i_mCellsY;
    m_mnCells = (i_nCellsX + 2) * (i_mCellsY + 2);

    // allocate memory including a single ghost cell on each side
    for (unsigned short l_st = 0; l_st < 2; l_st++) {
        m_h[l_st] = new t_real[m_mnCells];
        m_hu[l_st] = new t_real[m_mnCells];
        m_hv[l_st] = new t_real[m_mnCells];
    }
    m_b = new t_real[m_mnCells];

    // init to zero
    for (t_idx l_ce = 0; l_ce < m_mnCells; l_ce++) {
        for (unsigned short l_st = 0; l_st < 2; l_st++) {
            m_h[l_st][l_ce] = 0;
            m_hu[l_st][l_ce] = 0;
            m_hv[l_st][l_ce] = 0;
        }
        m_b[l_ce] = 0;
    }
}

tsunami_lab::patches::WavePropagation2d::~WavePropagation2d() {
    for (unsigned short l_st = 0; l_st < 2; l_st++) {
        delete[] m_h[l_st];
        delete[] m_hu[l_st];
        delete[] m_hv[l_st];
    }

    delete[] m_b;
}

tsunami_lab::t_idx tsunami_lab::patches::WavePropagation2d::getIndex(t_idx i_x, t_idx i_y) {
    return i_y * getStride() + i_x;
}

void tsunami_lab::patches::WavePropagation2d::timeStep(t_real i_scalingX,
                                                       t_real i_scalingY) {
    // pointers to old and new data
    t_real *l_hOld = m_h[m_step];
    t_real *l_huOld = m_hu[m_step];
    t_real *l_hvOld = m_hv[m_step];

    m_step = (m_step + 1) % 2;
    t_real *l_hNew = m_h[m_step];
    t_real *l_huNew = m_hu[m_step];
    t_real *l_hvNew = m_hv[m_step];

    // create arrays to save the data from the x-sweep
    t_real *l_hStar = new t_real[m_mnCells];
    t_real *l_huStar = new t_real[m_mnCells];
    t_real *l_hvStar = new t_real[m_mnCells];

    // init cell (Star) quantities
    for (t_idx l_ceY = 0; l_ceY < m_mCellsY + 2; l_ceY++) {
        for (t_idx l_ceX = 0; l_ceX < m_nCellsX + 2; l_ceX++) {
            t_idx l_idx = getIndex(l_ceX, l_ceY);
            l_hStar[l_idx] = l_hOld[l_idx];
            l_huStar[l_idx] = l_huOld[l_idx];
            l_hvStar[l_idx] = l_hvOld[l_idx];
        }
    }

    // iterate over edges in x-direction for every row and update with Riemann solutions (x-sweep)
    for (t_idx l_edY = 0; l_edY < m_mCellsY + 2; l_edY++) {
        for (t_idx l_edX = 0; l_edX < m_nCellsX + 1; l_edX++) {
            // determine left and right cell-id
            t_idx l_ceL = getIndex(l_edX, l_edY);
            t_idx l_ceR = getIndex(l_edX + 1, l_edY);

            // compute net-updates
            t_real l_netUpdates[2][2];

            solvers::FWave::netUpdates(l_hOld[l_ceL],
                                       l_hOld[l_ceR],
                                       l_huOld[l_ceL],
                                       l_huOld[l_ceR],
                                       m_b[l_ceL],
                                       m_b[l_ceR],
                                       l_netUpdates[0],
                                       l_netUpdates[1]);

            // update the cells' quantities
            l_hStar[l_ceL] -= i_scalingX * l_netUpdates[0][0];
            l_huStar[l_ceL] -= i_scalingX * l_netUpdates[0][1];

            l_hStar[l_ceR] -= i_scalingX * l_netUpdates[1][0];
            l_huStar[l_ceR] -= i_scalingX * l_netUpdates[1][1];
        }
    }

    // init new cell quantities
    for (t_idx l_ceY = 1; l_ceY < m_mCellsY + 1; l_ceY++) {
        for (t_idx l_ceX = 1; l_ceX < m_nCellsX + 1; l_ceX++) {
            t_idx l_idx = getIndex(l_ceX, l_ceY);
            l_hNew[l_idx] = l_hStar[l_idx];
            l_huNew[l_idx] = l_huStar[l_idx];
            l_hvNew[l_idx] = l_hvStar[l_idx];
        }
    }

    // iterate over edges in y-direction for every column and update with Riemann solutions (y-sweep)
    for (t_idx l_edX = 1; l_edX < m_nCellsX + 1; l_edX++) {
        for (t_idx l_edY = 0; l_edY < m_mCellsY + 1; l_edY++) {
            // determine upper and lower cell-id
            t_idx l_ceU = getIndex(l_edX, l_edY);
            t_idx l_ceD = getIndex(l_edX, l_edY + 1);

            // compute net-updates
            t_real l_netUpdates[2][2];

            solvers::FWave::netUpdates(l_hStar[l_ceU],
                                       l_hStar[l_ceD],
                                       l_hvStar[l_ceU],
                                       l_hvStar[l_ceD],
                                       m_b[l_ceU],
                                       m_b[l_ceD],
                                       l_netUpdates[0],
                                       l_netUpdates[1]);

            // update the cells' quantities
            l_hNew[l_ceU] -= i_scalingY * l_netUpdates[0][0];
            l_hvNew[l_ceU] -= i_scalingY * l_netUpdates[0][1];

            l_hNew[l_ceD] -= i_scalingY * l_netUpdates[1][0];
            l_hvNew[l_ceD] -= i_scalingY * l_netUpdates[1][1];
        }
    }

    delete[] l_hStar;
    delete[] l_huStar;
    delete[] l_hvStar;
}

void tsunami_lab::patches::WavePropagation2d::setGhostCells(std::string i_setting) {
    t_real *l_h = m_h[m_step];
    t_real *l_hu = m_hu[m_step];
    t_real *l_hv = m_hv[m_step];

    if (i_setting.compare("OO") == 0) {
        for (t_idx l_x = 1; l_x < m_nCellsX + 1; l_x++) {
            // set upper boundary
            l_h[getIndex(l_x, 0)] = l_h[getIndex(l_x, 1)];
            l_hu[getIndex(l_x, 0)] = l_hu[getIndex(l_x, 1)];
            l_hv[getIndex(l_x, 0)] = l_hv[getIndex(l_x, 1)];
            m_b[getIndex(l_x, 0)] = m_b[getIndex(l_x, 1)];

            // set lower boundary
            l_h[getIndex(l_x, m_mCellsY + 1)] = l_h[getIndex(l_x, m_mCellsY)];
            l_hu[getIndex(l_x, m_mCellsY + 1)] = l_hu[getIndex(l_x, m_mCellsY)];
            l_hv[getIndex(l_x, m_mCellsY + 1)] = l_hv[getIndex(l_x, m_mCellsY)];
            m_b[getIndex(l_x, m_mCellsY + 1)] = m_b[getIndex(l_x, m_mCellsY)];
        }

        for (t_idx l_y = 1; l_y < m_mCellsY + 1; l_y++) {
            // set left boundary
            l_h[getIndex(0, l_y)] = l_h[getIndex(1, l_y)];
            l_hu[getIndex(0, l_y)] = l_hu[getIndex(1, l_y)];
            l_hv[getIndex(0, l_y)] = l_hv[getIndex(1, l_y)];
            m_b[getIndex(0, l_y)] = m_b[getIndex(1, l_y)];

            // set right boundary
            l_h[getIndex(m_nCellsX + 1, l_y)] = l_h[getIndex(m_nCellsX, l_y)];
            l_hu[getIndex(m_nCellsX + 1, l_y)] = l_hu[getIndex(m_nCellsX, l_y)];
            l_hv[getIndex(m_nCellsX + 1, l_y)] = l_hv[getIndex(m_nCellsX, l_y)];
            m_b[getIndex(m_nCellsX + 1, l_y)] = m_b[getIndex(m_nCellsX, l_y)];
        }

        // set corner boundaries

        // upper left
        l_h[getIndex(0, 0)] = l_h[getIndex(1, 1)];
        l_hu[getIndex(0, 0)] = l_hu[getIndex(1, 1)];
        l_hv[getIndex(0, 0)] = l_hv[getIndex(1, 1)];
        m_b[getIndex(0, 0)] = m_b[getIndex(1, 1)];

        // upper right
        l_h[getIndex(m_nCellsX + 1, 0)] = l_h[getIndex(m_nCellsX, 1)];
        l_hu[getIndex(m_nCellsX + 1, 0)] = l_hu[getIndex(m_nCellsX, 1)];
        l_hv[getIndex(m_nCellsX + 1, 0)] = l_hv[getIndex(m_nCellsX, 1)];
        m_b[getIndex(m_nCellsX + 1, 0)] = m_b[getIndex(m_nCellsX, 1)];

        // lower left
        l_h[getIndex(0, m_mCellsY + 1)] = l_h[getIndex(1, m_mCellsY)];
        l_hu[getIndex(0, m_mCellsY + 1)] = l_hu[getIndex(1, m_mCellsY)];
        l_hv[getIndex(0, m_mCellsY + 1)] = l_hv[getIndex(1, m_mCellsY)];
        m_b[getIndex(0, m_mCellsY + 1)] = m_b[getIndex(1, m_mCellsY)];

        // lower right
        l_h[getIndex(m_nCellsX + 1, m_mCellsY + 1)] = l_h[getIndex(m_nCellsX, m_mCellsY)];
        l_hu[getIndex(m_nCellsX + 1, m_mCellsY + 1)] = l_hu[getIndex(m_nCellsX, m_mCellsY)];
        l_hv[getIndex(m_nCellsX + 1, m_mCellsY + 1)] = l_hv[getIndex(m_nCellsX, m_mCellsY)];
        m_b[getIndex(m_nCellsX + 1, m_mCellsY + 1)] = m_b[getIndex(m_nCellsX, m_mCellsY)];
    }
}
