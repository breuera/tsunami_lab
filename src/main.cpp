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
  tsunami_lab::t_real l_dxy = 1;
  l_nx = atoi(i_argv[i_argc - 1]);
  if (l_nx < 1)
  {
    std::cerr << "invalid number of cells" << std::endl;
    return EXIT_FAILURE;
  }
  l_dxy = 10.0 / l_nx;

  // get command line arguments
  opterr = 0; // disable error messages of getopt
  int opt;

  // defaults
  bool l_useFwave = true;
  tsunami_lab::setups::Setup *l_setup = new tsunami_lab::setups::DamBreak1d(10,
                                                                            5,
                                                                            5);

  while ((opt = getopt(i_argc, i_argv, "u:s:")) != -1)
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
        std::cout << "using Roe solver" << std::endl;
        l_useFwave = false;
      }
      else if (l_arg == "FWAVE")
      {
        std::cout << "using FWave solver" << std::endl;
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
      std::string l_setupName, l_arg1Str, l_arg2Str;
      std::getline(l_stream, l_setupName, ' ');
      std::getline(l_stream, l_arg1Str, ' ');
      std::getline(l_stream, l_arg2Str, ' ');

      // convert to upper case and t_real
      std::transform(l_setupName.begin(), l_setupName.end(), l_setupName.begin(), ::toupper);
      double l_arg1 = std::stof(l_arg1Str);
      double l_arg2 = std::stof(l_arg2Str);
      if (l_setupName == "DAMBREAK1D")
      {
        std::cout << "using DamBreak1d(" << l_arg1 << "," << l_arg2 << ",5) setup" << std::endl;
        l_setup = new tsunami_lab::setups::DamBreak1d(l_arg1,
                                                      l_arg2,
                                                      5);
      }
      else if (l_setupName == "RARERARE1D")
      {
        std::cout << "using RareRare1d(" << l_arg1 << "," << l_arg2 << ",5) setup" << std::endl;
        l_setup = new tsunami_lab::setups::RareRare1d(l_arg1,
                                                      l_arg2,
                                                      5);
      }
      else if (l_setupName == "SHOCKSHOCK1D")
      {
        std::cout << "using ShockShock1d(" << l_arg1 << "," << l_arg2 << ",5) setup" << std::endl;
        l_setup = new tsunami_lab::setups::ShockShock1d(l_arg1,
                                                        l_arg2,
                                                        5);
      }
      else
      {
        std::cerr << "unknown setup " << l_setupName << std::endl;
        return EXIT_FAILURE;
      }
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

  std::cout << "runtime configuration" << std::endl;
  std::cout << "  number of cells in x-direction: " << l_nx << std::endl;
  std::cout << "  number of cells in y-direction: " << l_ny << std::endl;
  std::cout << "  cell size:                      " << l_dxy << std::endl;

  // construct solver
  tsunami_lab::patches::WavePropagation *l_waveProp;
  l_waveProp = new tsunami_lab::patches::WavePropagation1d(l_nx, l_useFwave);

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
  tsunami_lab::t_real l_endTime = 1.25;
  tsunami_lab::t_real l_simTime = 0;

  std::cout << "entering time loop" << std::endl;

  // iterate over time
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
