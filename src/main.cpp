/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 * @author Mher Mnatsakanyan (mher.mnatsakanyan AT uni-jena.de)
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Entry-point for simulations.
 **/
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <limits>
#include <algorithm>
#include <unistd.h>
#include <vector>
#include <sstream>

#include "io/Csv.h"
#include "patches/WavePropagation1d.h"
#include "setups/dambreak1d/DamBreak1d.h"
#include "setups/shockshock1d/ShockShock1d.h"
#include "setups/rarerare1d/RareRare1d.h"

// declaration of variables
std::string solver_choice = "fwave";

int main(int i_argc,
         char *i_argv[])
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path targetPath;

    if (currentPath.filename() == "build")
    {
        targetPath = currentPath.parent_path() / "csv_dump";
    }
    else
    {
        targetPath = currentPath / "csv_dump";
    }

    if (!std::filesystem::exists(targetPath))
    {
        std::filesystem::create_directory(targetPath);
    }

    // number of cells in x- and y-direction
    tsunami_lab::t_idx l_nx = 0;
    tsunami_lab::t_idx l_ny = 1;

    // set cell size
    tsunami_lab::t_real l_dxy = 1;

    std::cout << "####################################" << std::endl;
    std::cout << "### Tsunami Lab                  ###" << std::endl;
    std::cout << "###                              ###" << std::endl;
    std::cout << "### https://scalable.uni-jena.de ###" << std::endl;
    std::cout << "####################################" << std::endl;

    if ((i_argc < 2) || (i_argv[i_argc - 1][0] == '-'))
    {
        std::cerr << "invalid number of arguments OR wrong order, usage:" << std::endl;
        std::cerr << "  ./build/tsunami_lab [-v SOLVER] [-s SETUP] N_CELLS_X" << std::endl;
        std::cerr << "where N_CELLS_X is the number of cells in x-direction." << std::endl;
        std::cerr << "-v SOLVER = 'roe','fwave', default is 'fwave'" << std::endl;
        std::cerr << "-s SETUP  = 'dambreak h_l h_r','rarerare h hu','shockshock h hu', default is 'dambreak 15 7'" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        l_nx = atoi(i_argv[i_argc - 1]);
        if (l_nx < 1)
        {
            std::cerr << "invalid number of cells" << std::endl;
            return EXIT_FAILURE;
        }
        l_dxy = 10.0 / l_nx;
    }

    // construct setup with default value
    tsunami_lab::setups::Setup *l_setup;
    l_setup = new tsunami_lab::setups::DamBreak1d(15,
                                                  7,
                                                  5);

    // get command line arguments
    opterr = 0; // disable error messages of getopt
    int opt;

    while ((opt = getopt(i_argc, i_argv, "s:v:")) != -1)
    {
        switch (opt)
        {
        case 'v':
        {
            if (std::string(optarg) == "roe")
            {
                std::cout << "using roe-solver" << std::endl;
                solver_choice = "roe";
            }
            else if (std::string(optarg) == "fwave")
            {
                std::cout << "using fwave-solver" << std::endl;
                solver_choice = "fwave";
            }
            else
            {
                std::cerr
                    << "unknown solver "
                    << std::string(optarg) << std::endl
                    << "possible options are: 'roe' or 'fwave'" << std::endl
                    << "be sure to only type in lower-case" << std::endl;
                return EXIT_FAILURE;
            }
            break;
        }
        case 's':
        {
            std::string argument(optarg);
            std::vector<std::string> tokens;
            std::string intermediate;

            // Create a stringstream object
            std::stringstream check1(argument);

            // Tokenizing w.r.t. the delimiter ' '
            while (getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
                std::cout << intermediate << std::endl;
            }

            // ensure that segmentation fault is not caused
            if (tokens.size() == 3)
            {
                // convert to t_real
                double l_arg1, l_arg2;
                try
                {
                    l_arg1 = std::stof(tokens[1]);
                    l_arg2 = std::stof(tokens[2]);
                }
                // if input after the name isn't a number, then throw an error
                catch (const std::invalid_argument &ia)
                {
                    std::cerr
                        << "Invalid argument: " << ia.what() << std::endl
                        << "be sure to only type numbers after the solver-name" << std::endl;
                    return EXIT_FAILURE;
                }

                if (tokens[0] == "dambreak")
                {
                    std::cout << "using DamBreak1d(" << l_arg1 << ", " << l_arg2 << ", 5) setup" << std::endl;
                    l_setup = new tsunami_lab::setups::DamBreak1d(l_arg1,
                                                                  l_arg2,
                                                                  5);
                }
                else if (tokens[0] == "shockshock")
                {
                    std::cout << "using ShockShock1d(" << l_arg1 << ", " << l_arg2 << ", 5) setup" << std::endl;
                    l_setup = new tsunami_lab::setups::ShockShock1d(l_arg1,
                                                                    l_arg2,
                                                                    5);
                }
                else if (tokens[0] == "rarerare")
                {
                    std::cout << "using RareRare1d(" << l_arg1 << "," << l_arg2 << ", 5) setup" << std::endl;
                    l_setup = new tsunami_lab::setups::RareRare1d(l_arg1,
                                                                  l_arg2,
                                                                  5);
                }
                // if input isn't a defined setup, throw an error
                else
                {
                    std::cerr
                        << "Undefined setup: " << tokens[0] << std::endl
                        << "possible options are: 'dambreak', 'shockshock' or 'rarerare'" << std::endl
                        << "be sure to only type in lower-case" << std::endl;
                    return EXIT_FAILURE;
                }
            }
            else
            {
                // if input doesn't follow the regulations "<name> <arg1> <arg2>"
                std::cerr
                    << "False number of arguments for setup: " << tokens.size() << std::endl
                    << "Expected: 3" << std::endl;
                return EXIT_FAILURE;
            }
            break;
        }
        // unknown option
        case '?':
        {
            std::cerr
                << "Undefinded option: " << char(optopt) << std::endl
                << "possible options are:" << std::endl
                << "  -v SOLVER = 'roe','fwave', default is 'fwave'" << std::endl
                << "  -s SETUP  = 'dambreak h_l h_r','rarerare h hu','shockshock h hu', default is 'dambreak 15 7'" << std::endl;
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
    l_waveProp = new tsunami_lab::patches::WavePropagation1d(l_nx);

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

            std::string l_path = targetPath.string() + "/" + "solution_" + std::to_string(l_nOut) + ".csv";
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
        l_waveProp->timeStep(l_scaling, solver_choice);

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
