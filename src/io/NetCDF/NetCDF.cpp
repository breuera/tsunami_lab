/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for reading and writing NetCDF files.
 **/

#include "NetCDF.h"

#include <iostream>

int tsunami_lab::io::NetCDF::read(std::string i_nameBathymetry,
                                  std::string i_nameDisplacements,
                                  t_idx *o_bathymetryDimX,
                                  t_idx *o_bathymetryDimY,
                                  t_real *&o_bathymetryPosX,
                                  t_real *&o_bathymetryPosY,
                                  t_real *&o_bathymetry,
                                  t_idx *o_dispDimX,
                                  t_idx *o_dispDimY,
                                  t_real *&o_dispPosX,
                                  t_real *&o_dispPosY,
                                  t_real *&o_displacements) {
    // add res path
    i_nameBathymetry = "./res/" + i_nameBathymetry;
    i_nameDisplacements = "./res/" + i_nameDisplacements;
    int l_ncIDBathymetry, l_ncIDDisplacements;
    int l_nc_err = nc_open(i_nameBathymetry.c_str(), 0, &l_ncIDBathymetry);

    // open bathymetry file
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not open file: " << i_nameBathymetry << std::endl;
        return 1;
    }

    // read bathymetry
    // get dimensions
    std::size_t l_xDim, l_yDim;
    l_nc_err = nc_inq_dimlen(l_ncIDBathymetry, 0, &l_xDim);
    l_nc_err = nc_inq_dimlen(l_ncIDBathymetry, 1, &l_yDim);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could get the size of a dimension in bathymetry." << std::endl;
        return 1;
    }

    *o_bathymetryDimX = (t_idx)l_xDim;
    *o_bathymetryDimY = (t_idx)l_yDim;
    o_bathymetry = new tsunami_lab::t_real[l_xDim * l_yDim];
    o_bathymetryPosX = new tsunami_lab::t_real[l_xDim];
    o_bathymetryPosY = new tsunami_lab::t_real[l_yDim];

    // get variable ids
    int l_varIDx, l_varIDy, l_varIDz;
    l_nc_err = nc_inq_varid(l_ncIDBathymetry, "x", &l_varIDx);
    l_nc_err = nc_inq_varid(l_ncIDBathymetry, "y", &l_varIDy);
    l_nc_err = nc_inq_varid(l_ncIDBathymetry, "z", &l_varIDz);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could find variable in bathymetry." << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDBathymetry, l_varIDx, &o_bathymetryPosX[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable x" << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDBathymetry, l_varIDy, &o_bathymetryPosY[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable y" << std::endl;
        return 1;
    }

    // read bathymetry

    l_nc_err = nc_get_var_float(l_ncIDBathymetry, l_varIDz, o_bathymetry);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable z" << std::endl;
        return 1;
    }
    // read displacements

    l_nc_err = nc_open(i_nameDisplacements.c_str(), 0, &l_ncIDDisplacements);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not open file: " << i_nameBathymetry << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_dimlen(l_ncIDDisplacements, 0, &l_xDim);
    l_nc_err = nc_inq_dimlen(l_ncIDDisplacements, 1, &l_yDim);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could get the size of a dimension in displacements." << std::endl;
        return 1;
    }

    *o_dispDimX = (t_idx)l_xDim;
    *o_dispDimY = (t_idx)l_yDim;
    o_displacements = new tsunami_lab::t_real[l_xDim * l_yDim];
    o_dispPosX = new tsunami_lab::t_real[l_xDim];
    o_dispPosY = new tsunami_lab::t_real[l_yDim];

    // get variable ids
    l_nc_err = nc_inq_varid(l_ncIDDisplacements, "x", &l_varIDx);
    l_nc_err = nc_inq_varid(l_ncIDDisplacements, "y", &l_varIDy);
    l_nc_err = nc_inq_varid(l_ncIDDisplacements, "z", &l_varIDz);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could find variable in displacements." << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDDisplacements, l_varIDx, &o_dispPosX[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable x" << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDDisplacements, l_varIDy, &o_dispPosY[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable y" << std::endl;
        return 1;
    }

    // read displacements
    l_nc_err = nc_get_var_float(l_ncIDDisplacements, l_varIDz, &o_displacements[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable z" << std::endl;
        return 1;
    }

    return 0;
}

int tsunami_lab::io::NetCDF::init(t_real i_dxy,
                                  t_idx i_nx,
                                  t_idx i_ny,
                                  t_idx i_stride,
                                  t_real const *i_b,
                                  std::string i_outFileName) {
    m_dxy = i_dxy;
    m_nx = i_nx;
    m_ny = i_ny;
    m_stride = i_stride;
    m_b = i_b;
    m_fileName = i_outFileName;

    int l_dimXId,
        l_dimYId, l_dimTimeId;
    int l_varXId, l_varYId, l_varTimeId, l_varBathymetryId, l_varHeightId, l_varMomentumXId, l_varMomentumYId;
    int l_nc_err;

    // create netCDF file
    l_nc_err = nc_create(m_fileName.c_str(), NC_CLOBBER, &m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    // define dimensions
    l_nc_err = nc_def_dim(m_ncId, "x", i_nx, &l_dimXId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_def_dim(m_ncId, "y", i_ny, &l_dimYId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_def_dim(m_ncId, "time", NC_UNLIMITED, &l_dimTimeId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    // define variables
    l_nc_err = nc_def_var(m_ncId, "x", NC_FLOAT, 1, &l_dimXId, &l_varXId);
    l_nc_err += nc_put_att_text(m_ncId, l_varXId, "units", 6, "meters");
    l_nc_err += nc_put_att_text(m_ncId, l_varXId, "axis", 1, "X");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_def_var(m_ncId, "y", NC_FLOAT, 1, &l_dimYId, &l_varYId);
    l_nc_err += nc_put_att_text(m_ncId, l_varYId, "units", 6, "meters");
    l_nc_err += nc_put_att_text(m_ncId, l_varXId, "axis", 1, "Y");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_def_var(m_ncId, "time", NC_FLOAT, 1, &l_dimTimeId, &l_varTimeId);
    l_nc_err += nc_put_att_text(m_ncId, l_varTimeId, "units", 7, "seconds");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    int l_dimBathymetryIds[2] = {l_dimXId, l_dimYId};
    l_nc_err = nc_def_var(m_ncId, "bathymetry", NC_FLOAT, 2, l_dimBathymetryIds, &l_varBathymetryId);
    l_nc_err += nc_put_att_text(m_ncId, l_varBathymetryId, "units", 6, "meters");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    int l_dimHeightIds[3] = {l_dimTimeId, l_dimXId, l_dimYId};
    l_nc_err = nc_def_var(m_ncId, "height", NC_FLOAT, 3, l_dimHeightIds, &l_varHeightId);
    l_nc_err += nc_put_att_text(m_ncId, l_varHeightId, "units", 6, "meters");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    int l_dimMomentumXIds[3] = {l_dimTimeId, l_dimXId, l_dimYId};
    l_nc_err = nc_def_var(m_ncId, "momentum_x", NC_FLOAT, 3, l_dimMomentumXIds, &l_varMomentumXId);
    l_nc_err += nc_put_att_text(m_ncId, l_varMomentumXId, "units", 11, "meters*kg/s");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    int l_dimMomentumYIds[3] = {l_dimTimeId, l_dimXId, l_dimYId};
    l_nc_err = nc_def_var(m_ncId, "momentum_y", NC_FLOAT, 3, l_dimMomentumYIds, &l_varMomentumYId);
    l_nc_err += nc_put_att_text(m_ncId, l_varMomentumYId, "units", 11, "meters*kg/s");
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_enddef(m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    // write x coordinates
    t_real *l_dataX = new t_real[m_nx];
    for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
        l_dataX[l_ix] = (l_ix + 0.5) * m_dxy;
    }
    l_nc_err = nc_put_var_float(m_ncId, l_varXId, l_dataX);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    // write y coordinates
    t_real *l_dataY = new t_real[m_ny];
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        l_dataY[l_iy] = (l_iy + 0.5) * m_dxy;
    }
    l_nc_err = nc_put_var_float(m_ncId, l_varYId, l_dataY);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    // write bathymetry
    t_real *l_bathymetry = new t_real[m_nx * m_ny];
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
            l_bathymetry[l_ix + l_iy * m_nx] = i_b[(l_iy + 1) * m_stride + (l_ix + 1)];
        }
    }
    l_nc_err = nc_put_var_float(m_ncId, l_varBathymetryId, l_bathymetry);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_close(m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    delete[] l_dataY;
    delete[] l_dataX;
    delete[] l_bathymetry;

    return 0;
}

int tsunami_lab::io::NetCDF::write(t_real i_time,
                                   t_idx i_timeStep,
                                   t_real const *i_h,
                                   t_real const *i_hu,
                                   t_real const *i_hv) {
    int l_varTimeId, l_varHeightId, l_varMomentumXId, l_varMomentumYId;
    int l_nc_err;

    l_nc_err = nc_open(m_fileName.c_str(), NC_WRITE, &m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(m_ncId, "time", &l_varTimeId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(m_ncId, "height", &l_varHeightId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(m_ncId, "momentum_x", &l_varMomentumXId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(m_ncId, "momentum_y", &l_varMomentumYId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    l_nc_err = nc_put_var1_float(m_ncId, l_varTimeId, &i_timeStep, &i_time);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    size_t l_startp[3] = {i_timeStep, 0, 0};
    size_t l_countp[3] = {1, m_nx, m_ny};

    t_real *l_height = new t_real[m_nx * m_ny];
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
            l_height[l_ix + l_iy * m_nx] = i_h[(l_iy + 1) * m_stride + (l_ix + 1)] + m_b[(l_iy + 1) * m_stride + (l_ix + 1)];
        }
    }
    l_nc_err = nc_put_vara_float(m_ncId, l_varHeightId, l_startp, l_countp, l_height);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    t_real *l_momentumX = new t_real[m_nx * m_ny];
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
            l_momentumX[l_ix + l_iy * m_nx] = i_hu[(l_iy + 1) * m_stride + (l_ix + 1)];
        }
    }
    l_nc_err = nc_put_vara_float(m_ncId, l_varMomentumXId, l_startp, l_countp, l_momentumX);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    t_real *l_momentumY = new t_real[m_nx * m_ny];
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
            l_momentumY[l_ix + l_iy * m_nx] = i_hv[(l_iy + 1) * m_stride + (l_ix + 1)];
        }
    }
    l_nc_err = nc_put_vara_float(m_ncId, l_varMomentumYId, l_startp, l_countp, l_momentumY);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    delete[] l_height;
    delete[] l_momentumX;
    delete[] l_momentumY;

    l_nc_err = nc_close(m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "Error: " << nc_strerror(l_nc_err) << std::endl;
        return 1;
    }

    return 0;
}

tsunami_lab::io::NetCDF::NetCDF() {
}

tsunami_lab::io::NetCDF::~NetCDF() {
}