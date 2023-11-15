#include "Stations.h"
#include <vector>
#include <string>
#include <fstream>

void tsunami_lab::io::Stations::addStation(const std::string i_name, t_real i_x, t_real i_y) {
    m_stations.emplace_back(i_name, i_x, i_y);
}


void tsunami_lab::io::Stations::writeStationOutput()
{
    std::vector<Station_struct> l_structs;

    for (const auto &station : m_stations)
    {
        std::ofstream file("data/station_data/" + station.m_name + ".csv");
        if (file.is_open())
        {
            file << "Time,Data\n";
            for (int t = 0; t < 100; t += m_outputFrequency)
            {
                file << t << ","
                     << "SampleData\n";
            }
        }
        file.close();
    }
}

tsunami_lab::io::Stations::Stations(const std::string &configFilePath)
{
    loadStationsFromJSON(configFilePath);
}

void tsunami_lab::io::Stations::loadStationsFromJSON(const std::string &filename)
{
    std::ifstream file(filename);
    nlohmann::json j;
    file >> j;

    for (const auto &station : j["stations"])
    {
        std::string name = station["name"];
        t_real x = station["x"];
        t_real y = station["y"];
        addStation(name, x, y);
    }
}
