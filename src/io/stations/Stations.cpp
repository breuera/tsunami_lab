/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional dam break problem.
 **/

#include "Stations.h"
#include <vector>
#include <string>
#include <fstream>

void tsunami_lab::io::Stations::addStation(const std::string i_name, t_real i_x, t_real i_y)
{
    m_stations.emplace_back(i_name, i_x, i_y);
}

int tsunami_lab::io::Stations::getOutputFrequency()
{
    return m_outputFrequency;
}

std::vector<Station_struct> tsunami_lab::io::Stations::getStations()
{
    return m_stations;
}

void tsunami_lab::io::Stations::writeStationOutput(t_real i_dxy,
                                                   t_idx i_nx,
                                                   t_idx i_ny,
                                                   t_real i_x_offset,
                                                   t_real i_y_offset,
                                                   t_idx i_stride,
                                                   t_real const *i_h,
                                                   t_real const *i_hu,
                                                   t_real const *i_hv,
                                                   t_real const *i_b,
                                                   t_real i_time)
{

    for (const auto &station : m_stations)
    {
        t_idx l_ix = (station.m_x + i_x_offset) / i_dxy;
        t_idx l_iy = (station.m_y + i_y_offset) / i_dxy;
        t_idx l_id = l_ix + l_iy * i_stride;

        if (l_ix < i_nx && l_iy < i_ny)
        {
            std::ofstream file("station_data/" + station.m_name + ".csv", std::ios::app);
            if (file.is_open())
            {
                file << i_time;
                if (i_h != nullptr)
                    file << "," << i_h[l_id];
                if (i_hu != nullptr)
                    file << "," << i_hu[l_id];
                if (i_hv != nullptr)
                    file << "," << i_hv[l_id];
                if (i_b != nullptr)
                    file << "," << i_b[l_id];
                file << std::endl
                     << std::flush;
            }
        }
    }
}

tsunami_lab::io::Stations::Stations(const std::string &filePath)
{
    loadStationsFromJSON(filePath);
}

void tsunami_lab::io::Stations::loadStationsFromJSON(const std::string &filePath)
{
    std::ifstream file(filePath);
    nlohmann::json j;
    file >> j;

    m_outputFrequency = j["outputfrequency"];

    for (const auto &station : j["stations"])
    {
        std::string name = station["name"];
        t_real x = station["x"];
        t_real y = station["y"];
        addStation(name, x, y);
    }
}
