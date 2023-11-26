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