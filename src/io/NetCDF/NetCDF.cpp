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

void checkNcErr(int i_err) {
    if (i_err) {
        std::cerr << "Error: "
                  << nc_strerror(i_err)
                  << std::endl;
        exit(2);
    }
}

void tsunami_lab::io::NetCDF::write(t_real i_dxy,
                                    t_idx i_nx,
                                    t_idx i_ny,
                                    t_idx i_stride,
                                    // t_real const *i_h,
                                    // t_real const *i_hu,
                                    // t_real const *i_hv,
                                    t_real const *i_b) {
    int l_ncId, l_dimXId, l_dimYId, l_dimTimeId;
    int l_varXId, l_varYId, l_varBathymetryId, l_varHeightId, l_varMomentumXId, l_varMomentumYId;
    int l_err;

    // create netCDF file
    l_err = nc_create("./out/solution.nc", NC_CLOBBER, &l_ncId);
    checkNcErr(l_err);

    // define dimensions
    l_err = nc_def_dim(l_ncId, "x", i_nx, &l_dimXId);
    checkNcErr(l_err);

    l_err = nc_def_dim(l_ncId, "y", i_ny, &l_dimYId);
    checkNcErr(l_err);

    l_err = nc_def_dim(l_ncId, "time", NC_UNLIMITED, &l_dimTimeId);
    checkNcErr(l_err);

    // define variables
    l_err = nc_def_var(l_ncId, "x", NC_FLOAT, 1, &l_dimXId, &l_varXId);
    checkNcErr(l_err);

    l_err = nc_def_var(l_ncId, "y", NC_FLOAT, 1, &l_dimYId, &l_varYId);
    checkNcErr(l_err);

    int l_dimBDimIds[2];
    l_dimBDimIds[0] = l_dimXId;
    l_dimBDimIds[1] = l_dimYId;
    //  int l_dimBathymetryIds[2] = {l_dimXId, l_dimYId};
    l_err = nc_def_var(l_ncId, "bathymetry", NC_FLOAT, 2, l_dimBDimIds, &l_varBathymetryId);
    checkNcErr(l_err);

    int l_dimHeightIds[3] = {l_dimTimeId, l_dimXId, l_dimYId};
    l_err = nc_def_var(l_ncId, "height", NC_FLOAT, 3, l_dimHeightIds, &l_varHeightId);
    checkNcErr(l_err);

    int l_dimMomentumXIds[3] = {l_dimTimeId, l_dimXId, l_dimYId};
    l_err = nc_def_var(l_ncId, "momentum_x", NC_FLOAT, 3, l_dimMomentumXIds, &l_varMomentumXId);
    checkNcErr(l_err);

    int l_dimMomentumYIds[3] = {l_dimTimeId, l_dimXId, l_dimYId};
    l_err = nc_def_var(l_ncId, "momentum_y", NC_FLOAT, 3, l_dimMomentumYIds, &l_varMomentumYId);
    checkNcErr(l_err);

    l_err = nc_enddef(l_ncId);
    checkNcErr(l_err);

    // write data
    float *l_dataX = new float[i_nx];
    for (t_idx l_ix = 0; l_ix < i_nx; l_ix++) {
        l_dataX[l_ix] = (l_ix + 0.5) * i_dxy;
    }
    l_err = nc_put_var_float(l_ncId, l_varXId, l_dataX);
    checkNcErr(l_err);

    float *l_dataY = new float[i_ny];
    for (t_idx l_iy = 0; l_iy < i_ny; l_iy++) {
        l_dataY[l_iy] = (l_iy + 0.5) * i_dxy;
    }
    l_err = nc_put_var_float(l_ncId, l_varYId, l_dataY);
    checkNcErr(l_err);

    t_real **l_bathymetry = new t_real *[i_nx];
    for (t_idx l_ix = 0; l_ix < i_nx; l_ix++) {
        l_bathymetry[l_ix] = new t_real[i_ny];
    }

    for (t_idx l_iy = 0; l_iy < i_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < i_nx; l_ix++) {
            l_bathymetry[l_ix][l_iy] = i_b[(l_iy + 1) * i_stride + (l_ix + 1)];
        }
    }
    l_err = nc_put_var_float(l_ncId, l_varBathymetryId, &l_bathymetry[0][0]);
    checkNcErr(l_err);

    // close file
    l_err = nc_close(l_ncId);  // ncid
    checkNcErr(l_err);
}