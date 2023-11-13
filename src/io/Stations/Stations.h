/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#ifndef TSUNAMI_LAB_IO_STATIONS
#define TSUNAMI_LAB_IO_STATIONS

#include "../../constants.h"
#include "../../../plugins/json.hpp"
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
    int m_outputFrequency = 1;
    std::vector<Station_struct> m_stations;

public:
     void addStation(const std::string i_name, t_real i_x, t_real i_y);

     void writeStationOutput();

     void loadStationsFromJSON(const std::string &filename);

    Stations(const std::string &configFilePath);
};

#endif