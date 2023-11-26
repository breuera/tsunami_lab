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

void tsunami_lab::io::NetCDF::read(std::string i_pathBathymetry,
                                   std::string i_pathDisplacements,
                                   t_real *&o_bathymetry,
                                   t_real *&o_displacements) {
    std::cout << i_pathBathymetry << i_pathDisplacements << o_bathymetry[0] << o_displacements[0] << std::endl;
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