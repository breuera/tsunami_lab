/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Test-cases for stations.
 **/

#include <catch2/catch.hpp>
#include "Stations.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

tsunami_lab::io::Stations l_stations("data/test.json");
std::string data_dir = "station_data";
auto stations = l_stations.getStations();

TEST_CASE("Test Reading the test.json", "[StationsRead]")
{
    tsunami_lab::io::Stations l_stations("data/test.json");

    REQUIRE(l_stations.getOutputFrequency() == 1);
    REQUIRE(l_stations.getStations()[0].m_name == "Station_1");
    REQUIRE(l_stations.getStations()[0].m_x == 1);
    REQUIRE(l_stations.getStations()[0].m_y == 2);
    REQUIRE(l_stations.getStations()[1].m_name == "Station_2");
    REQUIRE(l_stations.getStations()[1].m_x == 3);
    REQUIRE(l_stations.getStations()[1].m_y == 4);
}

TEST_CASE("Test creating CSVs for all Stations", "[StationsWrite]")
{
    // Create directory for station data
    if (std::filesystem::exists(data_dir))
    {
        std::filesystem::remove_all(data_dir);
    }
    std::filesystem::create_directory(data_dir);

    tsunami_lab::t_real l_h[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tsunami_lab::t_real l_hu[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tsunami_lab::t_real l_hv[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tsunami_lab::t_real l_b[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    l_stations.writeStationOutput(1, 20, 20, 0, 0, 0, l_h, l_hu, l_hv, l_b, 1);
    l_stations.writeStationOutput(1, 20, 20, 0, 0, 0, l_h, l_hu, l_hv, l_b, 2);
    l_stations.writeStationOutput(1, 20, 20, 0, 0, 0, l_h, l_hu, l_hv, l_b, 3);

    for (const auto &station : stations)
    {
        std::string filePath = data_dir + "/" + station.m_name + ".csv";
        REQUIRE(std::filesystem::exists(filePath));
    }
}

TEST_CASE("Test CSV File data", "[StationsData]")
{

    std::vector<tsunami_lab::t_real> l_csvData;

    for (const auto &station : stations)
    {
        std::string filePath = data_dir + "/" + station.m_name + ".csv";

        std::ifstream file(filePath);
        std::string line, cell;

        std::getline(file, line);

        while (std::getline(file, line))
        {
            std::stringstream lineStream(line);

            for (int i = 0; i < 5; ++i)
            {
                std::getline(lineStream, cell, ',');
                l_csvData.push_back(std::stof(cell));
            }
        }
    }

    std::vector<tsunami_lab::t_real> out{1, 2, 2, 2, 2,
                                         2, 2, 2, 2, 2,
                                         3, 2, 2, 2, 2,
                                         1, 4, 4, 4, 4,
                                         2, 4, 4, 4, 4,
                                         3, 4, 4, 4, 4};
    REQUIRE(l_csvData == out);
}