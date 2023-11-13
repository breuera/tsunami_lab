#include "Stations.h"
#include <vector>
#include <string>
#include <fstream>

void tsunami_lab::io::Stations::addStation(const std::string i_name, t_real i_x, t_real i_y)
{
    m_stations.emplace_back(i_name, i_x, i_y);
}

void tsunami_lab::io::Stations::writeOutput()
{
    std::vector<Station_struct> l_structs;

    for (const auto &station : m_stations)
    {
        std::ofstream file(station.m_name + ".csv");
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
