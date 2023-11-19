/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#ifndef TSUNAMI_LAB_IO_STATIONS
#define TSUNAMI_LAB_IO_STATIONS

#include "../../constants.h"
#include "../../plugins/json.hpp"
#include <cstring>
#include <iostream>
#include <vector>
namespace tsunami_lab
{
    namespace io
    {
        class Stations;
    }
}

struct Station_struct
{
    std::string m_name;
    tsunami_lab::t_real m_x, m_y;

    Station_struct(const std::string i_name, tsunami_lab::t_real i_x, tsunami_lab::t_real i_y)
    {
        m_name = i_name;
        m_x = i_x;
        m_y = i_y;
    }
};

class tsunami_lab::io::Stations
{
private:
    int m_outputFrequency;
    std::vector<Station_struct> m_stations;

public:
    /**
     * add station to the station vector.
     *
     * @param i_name station name.
     * @param i_x x-coordinate of station.
     * @param i_y y-coordinate of station.
     **/
    void addStation(const std::string i_name, t_real i_x, t_real i_y);

    int getOutputFrequency();

    /**
     * Writes the data as CSV to the given stream.
     *
     * @param i_dxy cell width in x- and y-direction.
     * @param i_nx number of cells in x-direction.
     * @param i_ny number of cells in y-direction.
     * @param i_stride stride of the data arrays in y-direction (x is assumed to be stride-1).
     * @param i_h water height of the cells; optional: use nullptr if not required.
     * @param i_hu momentum in x-direction of the cells; optional: use nullptr if not required.
     * @param i_hv momentum in y-direction of the cells; optional: use nullptr if not required.
     * @param i_b bathymetry of the cells; optional: use nullptr if not required.
     * @param i_time time of the output.
     **/

    void writeStationOutput(t_real i_dxy,
                            t_idx i_nx,
                            t_idx i_ny,
                            t_real i_x_offset,
                            t_real i_y_offset,
                            t_idx i_stride,
                            t_real const *i_h,
                            t_real const *i_hu,
                            t_real const *i_hv,
                            t_real const *i_b,
                            t_real i_time);

    /**
     * load Station file.
     *
     * @param filePath path of the station file
     **/

    void loadStationsFromJSON(const std::string &filePath);

    /**
     * Constructs the stations.
     *
     * @param filePath path of the station file
     */
    Stations(const std::string &filePath);
};

#endif