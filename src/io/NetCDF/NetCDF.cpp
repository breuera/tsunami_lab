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