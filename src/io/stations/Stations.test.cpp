/**
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Test-cases for stations.
 **/

#include <catch2/catch.hpp>
#include "Stations.h"

TEST_CASE("Test Reading the test.json", "[StationsRead]")
{
    tsunami_lab::io::Stations l_stations("data/test.json");

    REQUIRE(l_stations.getOutputFrequency() == 1);
    REQUIRE(l_stations.getStations().size() == 2);
    REQUIRE(l_stations.getStations()[0].m_name == "Station_1");
    REQUIRE(l_stations.getStations()[0].m_x == 10);
    REQUIRE(l_stations.getStations()[0].m_y == 15);
    REQUIRE(l_stations.getStations()[1].m_name == "Station_2");
    REQUIRE(l_stations.getStations()[1].m_x == 15);
    REQUIRE(l_stations.getStations()[1].m_y == 20);
}

TEST_CASE("Test creating CSVs for all Stations", "[StationsWrite]")
{
    tsunami_lab::io::Stations l_stations("data/test.json");

    // Create directory for station data
    std::string data_dir = "station_data";
    if (std::filesystem::exists(data_dir))
    {
        std::filesystem::remove_all(data_dir);
    }
    std::filesystem::create_directory(data_dir);

    tsunami_lab::t_real l_h[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tsunami_lab::t_real l_hu[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tsunami_lab::t_real l_hv[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tsunami_lab::t_real l_b[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    l_stations.writeStationOutput(1, 200, 200, 0, 0, 0, l_h, l_hu, l_hv, l_b, 1);
    l_stations.writeStationOutput(1, 200, 200, 0, 0, 0, l_h, l_hu, l_hv, l_b, 2);
    l_stations.writeStationOutput(1, 200, 200, 0, 0, 0, l_h, l_hu, l_hv, l_b, 3);

    auto stations = l_stations.getStations();
    for (const auto &station : stations)
    {
        std::string filename = data_dir + "/" + station.m_name + ".csv";
        REQUIRE(std::filesystem::exists(filename));
    }
}