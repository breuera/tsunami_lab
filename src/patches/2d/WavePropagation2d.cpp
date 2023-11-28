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
    m_nCellsY = i_mCellsY;
    m_nCellsAll = (i_nCellsX + 2) * (i_mCellsY + 2);

    // allocate memory including a single ghost cell on each side
    for (unsigned short l_st = 0; l_st < 2; l_st++) {
        m_h[l_st] = new t_real[m_nCellsAll];
        m_hu[l_st] = new t_real[m_nCellsAll];
        m_hv[l_st] = new t_real[m_nCellsAll];
    }
    m_b = new t_real[m_nCellsAll];

    // init to zero
    for (t_idx l_ce = 0; l_ce < m_nCellsAll; l_ce++) {
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
    t_real *l_hStar = new t_real[m_nCellsAll];
    t_real *l_huStar = new t_real[m_nCellsAll];
    t_real *l_hvStar = new t_real[m_nCellsAll];

    // init cell (Star) quantities
    for (t_idx l_ceY = 0; l_ceY < m_nCellsY + 2; l_ceY++) {
        for (t_idx l_ceX = 0; l_ceX < m_nCellsX + 2; l_ceX++) {
            t_idx l_idx = getIndex(l_ceX, l_ceY);
            l_hStar[l_idx] = l_hOld[l_idx];
            l_huStar[l_idx] = l_huOld[l_idx];
            l_hvStar[l_idx] = l_hvOld[l_idx];
        }
    }

    // iterate over edges in x-direction for every row and update with Riemann solutions (x-sweep)
    for (t_idx l_edY = 0; l_edY < m_nCellsY + 2; l_edY++) {
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
    for (t_idx l_ceY = 1; l_ceY < m_nCellsY + 1; l_ceY++) {
        for (t_idx l_ceX = 1; l_ceX < m_nCellsX + 1; l_ceX++) {
            t_idx l_idx = getIndex(l_ceX, l_ceY);
            l_hNew[l_idx] = l_hStar[l_idx];
            l_huNew[l_idx] = l_huStar[l_idx];
            l_hvNew[l_idx] = l_hvStar[l_idx];
        }
    }

    // iterate over edges in y-direction for every column and update with Riemann solutions (y-sweep)
    for (t_idx l_edX = 1; l_edX < m_nCellsX + 1; l_edX++) {
        for (t_idx l_edY = 0; l_edY < m_nCellsY + 1; l_edY++) {
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

void tsunami_lab::patches::WavePropagation2d::copyCornerCells(t_real *o_dataArray) {
    t_idx l_xMax = m_nCellsX + 1;
    t_idx l_yMax = m_nCellsY + 1;

    o_dataArray[getIndex(0, 0)] = o_dataArray[getIndex(1, 1)];
    o_dataArray[getIndex(l_xMax, 0)] = o_dataArray[getIndex(l_xMax - 1, 1)];
    o_dataArray[getIndex(0, l_yMax)] = o_dataArray[getIndex(1, l_yMax - 1)];
    o_dataArray[getIndex(l_xMax, l_yMax)] = o_dataArray[getIndex(l_xMax - 1, l_yMax - 1)];
}

void tsunami_lab::patches::WavePropagation2d::copyGhostCellsOutflow(short i_axis[2], t_real *o_dataArray) {
    t_idx l_xMax = m_nCellsX + 1;
    t_idx l_yMax = m_nCellsY + 1;

    if (i_axis[0] == 1) {
        for (t_idx l_iy = 1; l_iy < l_yMax; l_iy++) {
            o_dataArray[getIndex(l_xMax, l_iy)] = o_dataArray[getIndex(l_xMax - 1, l_iy)];
        }
    } else if (i_axis[0] == -1) {
        for (t_idx l_iy = 1; l_iy < l_yMax; l_iy++) {
            o_dataArray[getIndex(0, l_iy)] = o_dataArray[getIndex(1, l_iy)];
        }
    }

    if (i_axis[1] == 1) {
        for (t_idx l_ix = 1; l_ix < l_xMax; l_ix++) {
            o_dataArray[getIndex(l_ix, l_yMax)] = o_dataArray[getIndex(l_ix, l_yMax - 1)];
        }
    } else if (i_axis[1] == -1) {
        for (t_idx l_ix = 1; l_ix < l_xMax; l_ix++) {
            o_dataArray[getIndex(l_ix, 0)] = o_dataArray[getIndex(l_ix, 1)];
        }
    }

    copyCornerCells(o_dataArray);
}

void tsunami_lab::patches::WavePropagation2d::copyGhostCellsReflecting(short i_axis[2], t_real i_value, t_real *o_dataArray) {
    t_idx l_xMax = m_nCellsX + 1;
    t_idx l_yMax = m_nCellsY + 1;

    if (i_axis[0] == 1) {
        for (t_idx l_iy = 1; l_iy < l_yMax; l_iy++) {
            o_dataArray[getIndex(l_xMax, l_iy)] = i_value;
        }
    } else if (i_axis[0] == -1) {
        for (t_idx l_iy = 1; l_iy < l_yMax; l_iy++) {
            o_dataArray[getIndex(0, l_iy)] = i_value;
        }
    }

    if (i_axis[1] == 1) {
        for (t_idx l_ix = 1; l_ix < l_xMax; l_ix++) {
            o_dataArray[getIndex(l_ix, l_yMax)] = i_value;
        }
    } else if (i_axis[1] == -1) {
        for (t_idx l_ix = 1; l_ix < l_xMax; l_ix++) {
            o_dataArray[getIndex(l_ix, 0)] = i_value;
        }
    }

    copyCornerCells(o_dataArray);
}

void tsunami_lab::patches::WavePropagation2d::setGhostCells(e_boundary *i_boundary) {
    short l_axis[4][2] = {{1, 0},
                          {0, 1},
                          {-1, 0},
                          {0, -1}};

    for (t_idx l_i = 0; l_i < 4; l_i++) {
        if (i_boundary[l_i] == OUTFLOW) {
            copyGhostCellsOutflow(l_axis[l_i], m_h[m_step]);
            copyGhostCellsOutflow(l_axis[l_i], m_hu[m_step]);
            copyGhostCellsOutflow(l_axis[l_i], m_hv[m_step]);
            copyGhostCellsOutflow(l_axis[l_i], m_b);
        } else if (i_boundary[l_i] == REFLECTING) {
            copyGhostCellsReflecting(l_axis[l_i], 0, m_h[m_step]);
            copyGhostCellsReflecting(l_axis[l_i], 0, m_hu[m_step]);
            copyGhostCellsReflecting(l_axis[l_i], 0, m_hv[m_step]);
            copyGhostCellsReflecting(l_axis[l_i], 20, m_b);
        }
    }
}
