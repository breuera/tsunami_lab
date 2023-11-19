/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#include "Csv.h"

#include <cmath>
#include <iostream>
#include <sstream>

void tsunami_lab::io::Csv::write(t_real i_dxy,
                                 t_idx i_nx,
                                 t_idx i_ny,
                                 t_idx i_stride,
                                 t_real const *i_h,
                                 t_real const *i_hu,
                                 t_real const *i_hv,
                                 t_real const *i_b,
                                 std::ostream &io_stream) {
    // write the CSV header
    io_stream << "x,y";
    if (i_h != nullptr) io_stream << ",height";
    if (i_hu != nullptr) io_stream << ",momentum_x";
    if (i_hv != nullptr) io_stream << ",momentum_y";
    if (i_b != nullptr) io_stream << ",bathymetry";
    if (i_h != nullptr && i_b != nullptr) io_stream << ",h+b";
    if (i_hu != nullptr && i_hv != nullptr) io_stream << ",momentum_avg";
    if (i_b != nullptr) io_stream << ",bathymetry_scale";
    io_stream << "\n";

    // iterate over all cells
    for (t_idx l_iy = 0; l_iy < i_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < i_nx; l_ix++) {
            // derive coordinates of cell center
            t_real l_posX = (l_ix + 0.5) * i_dxy;
            t_real l_posY = (l_iy + 0.5) * i_dxy;

            t_idx l_id = l_iy * i_stride + l_ix;

            // write data
            io_stream << l_posX << "," << l_posY;
            if (i_h != nullptr) io_stream << "," << i_h[l_id];
            if (i_hu != nullptr) io_stream << "," << i_hu[l_id];
            if (i_hv != nullptr) io_stream << "," << i_hv[l_id];
            if (i_b != nullptr) io_stream << "," << i_b[l_id];
            if (i_h != nullptr && i_b != nullptr) io_stream << "," << i_h[l_id] + i_b[l_id];
            if (i_hu != nullptr && i_hv != nullptr) io_stream << "," << (fabs(i_hu[l_id]) + fabs(i_hv[l_id])) / 2;
            if (i_b != nullptr) io_stream << "," << i_b[l_id];
            io_stream << "\n";
        }
    }
    io_stream << std::flush;
}

void tsunami_lab::io::Csv::read_middle_states(std::ifstream &io_stream,
                                              t_real *&o_heightsL,
                                              t_real *&o_momentumsL,
                                              t_real *&o_heightsR,
                                              t_real *&o_momentumsR,
                                              t_real *&o_hStar) {
    tsunami_lab::t_idx l_length = 1000000;
    std::string l_line;
    std::stringstream l_lineStream;

    // skip header
    for (size_t i = 0; i < 8; i++) {
        std::getline(io_stream, l_line);
    }

    o_heightsL = (t_real *)malloc(l_length * sizeof(t_real));
    o_heightsR = (t_real *)malloc(l_length * sizeof(t_real));
    o_momentumsL = (t_real *)malloc(l_length * sizeof(t_real));
    o_momentumsR = (t_real *)malloc(l_length * sizeof(t_real));
    o_hStar = (t_real *)malloc(l_length * sizeof(t_real));

    for (t_idx i = 0; i < l_length; i++) {
        // read next line
        std::getline(io_stream, l_line);
        l_lineStream << l_line;
        std::string l_cell;

        // load left height
        std::getline(l_lineStream, l_cell, ',');
        o_heightsL[i] = std::stof(l_cell);

        // load right height
        std::getline(l_lineStream, l_cell, ',');
        o_heightsR[i] = std::stof(l_cell);

        // load left momentum
        std::getline(l_lineStream, l_cell, ',');
        o_momentumsL[i] = std::stof(l_cell);

        // load right momentum
        std::getline(l_lineStream, l_cell, ',');
        o_momentumsR[i] = std::stof(l_cell);

        // load h*
        std::getline(l_lineStream, l_cell, ',');
        o_hStar[i] = std::stof(l_cell);

        l_lineStream.clear();
    }
}
void tsunami_lab::io::Csv::read_gmt_states(std::ifstream &io_stream,
                                           t_real *&o_bathymetry,
                                           t_real *&o_x,
                                           t_real *&o_y,
                                           t_real *&o_distance) {
    tsunami_lab::t_idx l_length = 1763;
    std::string l_line;
    std::stringstream l_lineStream;

    o_bathymetry = new t_real[l_length];
    o_x = new t_real[l_length];
    o_y = new t_real[l_length];
    o_distance = new t_real[l_length];

    for (t_idx i = 0; i < l_length; i++) {
        // read next line
        std::getline(io_stream, l_line);
        // std::cout << i << " : " << l_line << std::endl;
        l_lineStream << l_line;
        std::string l_cell;

        // load x-coordinate
        std::getline(l_lineStream, l_cell, ',');
        o_x[i] = std::stof(l_cell);

        // load y-coordinate
        std::getline(l_lineStream, l_cell, ',');
        o_y[i] = std::stof(l_cell);

        // load distance
        std::getline(l_lineStream, l_cell, ',');
        o_distance[i] = std::stof(l_cell);

        // load bathymetry
        std::getline(l_lineStream, l_cell, ',');
        o_bathymetry[i] = std::stof(l_cell);

        l_lineStream.clear();
    }
}