/**
/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for reading and writing NetCDF files.
 **/
#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../../constants.h"
#define private public
#include "Csv.h"
#undef public