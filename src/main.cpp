/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Entry-point for simulations.
 **/
#include "patches/WavePropagation1d.h"
#include "setups/damBreak1d/DamBreak1d.h"
#include "setups/rareRare1d/RareRare1d.h"
#include "setups/shockShock1d/ShockShock1d.h"
#include "setups/custom1d/Custom1d.h"
#include "setups/supercritical1d/Supercritical1d.h"
#include "setups/subcritical1d/Subcritical1d.h"
#include "setups/tsunamiEvent1d/TsunamiEvent1d.h"
#include "io/Csv.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <limits>
#include <algorithm>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <filesystem>

// converts a string to a boundary condition (tsunami_lab::t_boundary)
void getBoundary(std::string i_name, tsunami_lab::t_boundary *o_boundary)
{
  if (i_name == "WALL")
  {
    *o_boundary = tsunami_lab::t_boundary::WALL;
  }
  else if (i_name == "OPEN")
  {
    *o_boundary = tsunami_lab::t_boundary::OPEN;
  }
  else
  {
    std::cerr << "unknown boundary condition " << i_name << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(int i_argc,
         char *i_argv[])
{
  // number of cells in x- and y-direction
  tsunami_lab::t_idx l_nx = 0;
  tsunami_lab::t_idx l_ny = 1;

  std::cout << "####################################" << std::endl;
  std::cout << "### Tsunami Lab                  ###" << std::endl;
  std::cout << "###                              ###" << std::endl;
  std::cout << "### https://scalable.uni-jena.de ###" << std::endl;
  std::cout << "####################################" << std::endl;

  // missing n_cells_x or getting -key as last argument (f.E. -h)
  if ((i_argc < 2) || (i_argv[i_argc - 1] == 0) || (i_argv[i_argc - 1][0] == '-'))
  {
    // removed invalid number of arguments message for -h option
    std::cerr << "usage:" << std::endl;
    std::cerr << "  ./build/tsunami_lab [-s SOLVER] [-u SETUP] N_CELLS_X" << std::endl;
    std::cerr << "  N_CELLS_X = the number of cells in x-direction." << std::endl;
    std::cerr << "  -s SOLVER = 'Roe','FWave', default is 'FWave'" << std::endl;
    std::cerr << "  -u SETUP  = 'DamBreak1d h_l h_r','RareRare1d h hu','ShockShock1d h hu', default is 'DamBreak1d 10 5'" << std::endl;
    std::cerr << "  example: ./build/tsunami_lab -s roe -u 'ShockShock1d 10 100' 100" << std::endl;
    return EXIT_FAILURE;
  }

  // set cell size
  l_nx = atoi(i_argv[i_argc - 1]);
  if (l_nx < 1)
  {
    std::cerr << "invalid number of cells" << std::endl;
    return EXIT_FAILURE;
  }

  // get command line arguments
  opterr = 0; // disable error messages of getopt
  int opt;

  // defaults
  bool l_useFwave = true;
  tsunami_lab::setups::Setup *l_setup = nullptr;
  tsunami_lab::t_boundary l_boundaryL = tsunami_lab::t_boundary::OPEN;
  tsunami_lab::t_boundary l_boundaryR = tsunami_lab::t_boundary::OPEN;
  tsunami_lab::t_real l_endTime = 1.25;
  tsunami_lab::t_real l_width = 10.0;

  std::cout << "runtime configuration" << std::endl;
  std::cout << "  number of cells in x-direction: " << l_nx << std::endl;
  std::cout << "  number of cells in y-direction: " << l_ny << std::endl;

  while ((opt = getopt(i_argc, i_argv, "u:s:b:")) != -1)
  {
    switch (opt)
    {
    // solver
    case 's':
    {
      std::string l_arg(optarg);
      std::transform(l_arg.begin(), l_arg.end(), l_arg.begin(), ::toupper);
      if (l_arg == "ROE")
      {
        l_useFwave = false;
      }
      else if (l_arg == "FWAVE")
      {
        l_useFwave = true;
      }
      else
      {
        std::cerr << "unknown solver " << l_arg << std::endl;
        return EXIT_FAILURE;
      }
      break;
    }
    // setup
    case 'u':
    {
      std::string l_arg(optarg);

      // split string by space
      std::stringstream l_stream(l_arg);
      std::string l_setupName, l_arg1Str, l_arg2Str, l_arg3Str, l_arg4Str, l_arg5Str;
      l_stream >> l_setupName >> l_arg1Str >> l_arg2Str >> l_arg3Str >> l_arg4Str >> l_arg5Str;

      // convert to upper case
      std::transform(l_setupName.begin(), l_setupName.end(), l_setupName.begin(), ::toupper);

      // 'Dambreak1d h_l h_r' setup
      if (l_setupName == "DAMBREAK1D")
      {
        double l_arg1 = std::stof(l_arg1Str);
        double l_arg2 = std::stof(l_arg2Str);
        std::cout << "  using DamBreak1d(" << l_arg1 << "," << l_arg2 << ",5) setup" << std::endl;
        l_setup = new tsunami_lab::setups::DamBreak1d(l_arg1,
                                                      l_arg2,
                                                      5);
      }
      // 'RareRare1d h hu' setup
      else if (l_setupName == "RARERARE1D")
      {
        double l_arg1 = std::stof(l_arg1Str);
        double l_arg2 = std::stof(l_arg2Str);
        std::cout << "  using RareRare1d(" << l_arg1 << "," << l_arg2 << ",5) setup" << std::endl;
        l_setup = new tsunami_lab::setups::RareRare1d(l_arg1,
                                                      l_arg2,
                                                      5);
      }
      // 'ShockShock1d h hu' setup
      else if (l_setupName == "SHOCKSHOCK1D")
      {
        double l_arg1 = std::stof(l_arg1Str);
        double l_arg2 = std::stof(l_arg2Str);
        std::cout << "  using ShockShock1d(" << l_arg1 << "," << l_arg2 << ",5) setup" << std::endl;
        l_setup = new tsunami_lab::setups::ShockShock1d(l_arg1,
                                                        l_arg2,
                                                        5);
      }
      // 'Custom1d h_l h_r hu_l hu_r middle' setup
      else if (l_setupName == "CUSTOM1D")
      {
        double l_arg1 = std::stof(l_arg1Str);
        double l_arg2 = std::stof(l_arg2Str);
        double l_arg3 = std::stof(l_arg3Str);
        double l_arg4 = std::stof(l_arg4Str);
        double l_arg5 = std::stof(l_arg5Str);
        std::cout << "  using Custom1d(" << l_arg1 << "," << l_arg2 << "," << l_arg3 << "," << l_arg4 << "," << l_arg5 << ") setup" << std::endl;
        l_setup = new tsunami_lab::setups::Custom1d(l_arg1,
                                                    l_arg2,
                                                    l_arg3,
                                                    l_arg4,
                                                    l_arg5);
      }
      // 'Supercrit1d' setup
      else if (l_setupName == "SUPERCRIT1D")
      {
        l_width = 25.0;  // 25 m domain
        l_endTime = 200; // 200 s simulation time
        std::cout << "  using Supercritical1d() setup" << std::endl;
        l_setup = new tsunami_lab::setups::Supercritical1d();
      }
      // 'Subcrit1d' setup
      else if (l_setupName == "SUBCRIT1D")
      {
        l_width = 25.0;  // 25 m domain
        l_endTime = 200; // 200 s simulation time
        std::cout << "  using Subcritical1d() setup" << std::endl;
        l_setup = new tsunami_lab::setups::Subcritical1d();
      }
      // 'Tsunami1d pathToCsv time' setup
      else if (l_setupName == "TSUNAMI1D")
      {
        // assumptions: headerless csv, 4 columns, 3rd being length along path and 4th being height
        std::string i_filePath = l_arg1Str;
        rapidcsv::Document l_doc;
        size_t l_rowCount;

        tsunami_lab::io::Csv::openCSV(i_filePath, l_doc, l_rowCount);

        l_setup = new tsunami_lab::setups::TsunamiEvent1d(l_doc, l_rowCount);
        l_width = 250 * l_rowCount;
        l_endTime = stof(l_arg2Str);
      }
      else
      {
        std::cerr << "unknown setup " << l_setupName << std::endl;
        return EXIT_FAILURE;
      }
      break;
    }
    // boundary
    case 'b':
    {
      std::string l_arg(optarg);

      // convert to upper case
      std::transform(l_arg.begin(), l_arg.end(), l_arg.begin(), ::toupper);

      // split string by space
      std::stringstream l_stream(l_arg);
      std::string l_boundaryLName, l_boundaryRName;
      l_stream >> l_boundaryLName >> l_boundaryRName;

      std::cout << "  using boundary conditions " << l_boundaryLName << " " << l_boundaryRName << std::endl;

      // convert to t_boundary
      getBoundary(l_boundaryLName, &l_boundaryL);
      getBoundary(l_boundaryRName, &l_boundaryR);
      break;
    }
    // unknown option
    case '?':
    {
      std::cerr << "unknown option: " << char(optopt) << std::endl;
      break;
    }
    }
  }

  // command line prints

  if (l_setup == nullptr)
  {
    std::cout << "  using DamBreak1d(10,5,5) setup" << std::endl;
    l_setup = new tsunami_lab::setups::DamBreak1d(10,
                                                  5,
                                                  5);
  }
  if (l_useFwave == false)
  {
    std::cout << "  using Roe solver" << std::endl;
  }
  else
  {
    std::cout << "  using FWave solver" << std::endl;
  }
  // calculate cell size
  tsunami_lab::t_real l_dxy = l_width / l_nx;
  std::cout << "  cell size:       " << l_dxy << " m" << std::endl;
  std::cout << "  width simulated: " << l_width << " m" << std::endl;
  std::cout << "  time simulated:  " << l_endTime << " s" << std::endl;

  // construct solver
  tsunami_lab::patches::WavePropagation *l_waveProp;
  l_waveProp = new tsunami_lab::patches::WavePropagation1d(l_nx, l_useFwave, l_boundaryL, l_boundaryR);

  // maximum observed height in the setup
  tsunami_lab::t_real l_hMax = std::numeric_limits<tsunami_lab::t_real>::lowest();

  // set up solver
  for (tsunami_lab::t_idx l_cy = 0; l_cy < l_ny; l_cy++)
  {
    tsunami_lab::t_real l_y = l_cy * l_dxy;

    for (tsunami_lab::t_idx l_cx = 0; l_cx < l_nx; l_cx++)
    {
      tsunami_lab::t_real l_x = l_cx * l_dxy;

      // get initial values of the setup
      tsunami_lab::t_real l_h = l_setup->getHeight(l_x,
                                                   l_y);
      l_hMax = std::max(l_h, l_hMax);

      tsunami_lab::t_real l_hu = l_setup->getMomentumX(l_x,
                                                       l_y);
      tsunami_lab::t_real l_hv = l_setup->getMomentumY(l_x,
                                                       l_y);
      tsunami_lab::t_real l_b = l_setup->getBathymetry(l_x,
                                                       l_y);

      // set initial values in wave propagation solver
      l_waveProp->setHeight(l_cx,
                            l_cy,
                            l_h);

      l_waveProp->setMomentumX(l_cx,
                               l_cy,
                               l_hu);

      l_waveProp->setMomentumY(l_cx,
                               l_cy,
                               l_hv);

      l_waveProp->setBathymetry(l_cx,
                                l_cy,
                                l_b);
    }
  }

  // derive maximum wave speed in setup; the momentum is ignored
  tsunami_lab::t_real l_speedMax = std::sqrt(9.81 * l_hMax);

  // derive constant time step; changes at simulation time are ignored
  tsunami_lab::t_real l_dt = 0.5 * l_dxy / l_speedMax;

  // derive scaling for a time step
  tsunami_lab::t_real l_scaling = l_dt / l_dxy;

  // set up time and print control
  tsunami_lab::t_idx l_timeStep = 0;
  tsunami_lab::t_idx l_nOut = 0;
  tsunami_lab::t_real l_simTime = 0;

  std::cout << "entering time loop" << std::endl;

  // iterate over time

  // delete old solutions
  if (std::filesystem::exists("solutions"))
  {
    std::filesystem::remove_all("solutions");
  }
  std::filesystem::create_directory("solutions");

  while (l_simTime < l_endTime)
  {
    if (l_timeStep % 25 == 0)
    {
      std::cout << "  simulation time / #time steps: "
                << l_simTime << " / " << l_timeStep << std::endl;

      std::string l_path = "solutions/solution_" + std::to_string(l_nOut) + ".csv";
      std::cout << "  writing wave field to " << l_path << std::endl;

      std::ofstream l_file;
      l_file.open(l_path);

      tsunami_lab::io::Csv::write(l_dxy,
                                  l_nx,
                                  1,
                                  1,
                                  l_waveProp->getHeight(),
                                  l_waveProp->getMomentumX(),
                                  nullptr,
                                  l_waveProp->getBathymetry(),
                                  l_file);
      l_file.close();
      l_nOut++;
    }

    l_waveProp->setGhostOutflow();
    l_waveProp->timeStep(l_scaling);

    l_timeStep++;
    l_simTime += l_dt;
  }

  std::cout << "finished time loop" << std::endl;

  // free memory
  std::cout << "freeing memory" << std::endl;
  delete l_setup;
  delete l_waveProp;

  std::cout << "finished, exiting" << std::endl;
  return EXIT_SUCCESS;
}
