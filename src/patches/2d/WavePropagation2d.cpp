/**
 * @author Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * Two-dimensional wave propagation patch.
 **/

#include "WavePropagation2d.h"

tsunami_lab::patches::WavePropagation2d::WavePropagation2d(t_idx i_nCellsX,
                                                           t_idx i_mCellsY) {
    m_nCellsX = i_nCellsX;
    m_mCellsY = i_mCellsY;
}

tsunami_lab::patches::WavePropagation2d::~WavePropagation2d() {
    for (unsigned short l_st = 0; l_st < 2; l_st++) {
        delete[] m_h[l_st];
        delete[] m_hu[l_st];
        delete[] m_hv[l_st];
    }

    delete[] m_b;
}
