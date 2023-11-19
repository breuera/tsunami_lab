.. _ch:Task_2_1:

Report Week 2
=============

.. _ch:Contribution:

Contribution
------------

Bohdan Babii and Phillip Rothenbeck both made equal and significant contributions to Assignment 1 at the Tsunami Lab. Their collaboration and dedication to the project were evident throughout the process.

.. _ch:Finite_Volume_Discretization:

Finite Volume Discretization
----------------------------

.. admonition:: Tasks

    #. Integrate your f-wave solver into the one-dimensional implementation of a wave propagation patch given in files ``WavePropagation1d.h``, ``WavePropagation1d.cpp``, ``WavePropagation1d.test.cpp``.
       Find a good solution to switch between the provided Roe solver and your f-wave solver.

    #. The CSV-file `middle_states\.csv <https://scalable.uni-jena.de/assets/tsunami_lab/middle_states.csv>`_ contains a collection of constant middle states which arise immediately in the Riemann solution at the initial discontinuity.
       Use these middle states as a sanity check.

    #. Embed your solver into a continuous integration tool.
       Ensure to run at least the solver's unit tests after every commit to your git repository.
       You may use any suitable tool for this task including `GitHub Actions <https://github.com/features/actions>`__, `GitLab Runner <https://docs.gitlab.com/runner/>`__, `Travis CI <https://www.travis-ci.com/>`__, `Buildkite <https://buildkite.com/>`__, `GoCD <https://www.gocd.org/>`__ and `Jenkins <https://www.jenkins.io/>`__.


Implemntation of the WavePropagation1d
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block::

  m_use_roe_solver = i_use_roe_solver;

  ... 

  if (m_use_roe_solver)
    {
      solvers::Roe::netUpdates(l_hOld[l_ceL],
                               l_hOld[l_ceR],
                               l_huOld[l_ceL],
                               l_huOld[l_ceR],
                               l_netUpdates[0],
                               l_netUpdates[1]);
    }
    else
    {
      solvers::FWave::netUpdates(l_hOld[l_ceL],
                                  l_hOld[l_ceR],
                                  l_huOld[l_ceL],
                                  l_huOld[l_ceR],
                                  l_netUpdates[0],
                                  l_netUpdates[1]);
    }

The code snippet is added to the WavePropagation1d class, allowing it to switch between the Roe and FWave solvers based on the value of the m_use_roe_solver variable, enhancing the class's flexibility in handling wave propagation problems.

.. code-block::

    if (i_argc == 3)
  {
    l_scenario = i_argv[1];
    l_nx = atoi(i_argv[2]);
    if (l_nx < 1)
    {
      std::cerr << "invalid number of cells" << std::endl;
      return EXIT_FAILURE;
    }
    std::cout << "solver defaults to f-wave solver" << std::endl;
    l_dxy = 10.0 / l_nx;
  }
  else if (i_argc == 4)
  {
    l_scenario = i_argv[1];
    l_nx = atoi(i_argv[2]);
    if (l_nx < 1)
    {
      std::cerr << "invalid number of cells" << std::endl;
      return EXIT_FAILURE;
    }
    l_dxy = 10.0 / l_nx;

    if (!(strcmp(i_argv[3], "-f") == 0 || strcmp(i_argv[3], "-r") == 0))
    {
      std::cerr << "invalid third argument(needs to be '-r' or '-f')" << std::endl;
      return EXIT_FAILURE;
    }

    l_use_roe_solver = (strcmp(i_argv[3], "-r") == 0);
    if (l_use_roe_solver)
    {
      std::cout << "solver was set to the roe solver" << std::endl;
    }
    else
    {
      std::cout << "solver was set to the f-wave solver" << std::endl;
    }
  }

The main.cpp has been extended to accept command-line arguments. If provided with 3 arguments, it expects a scenario and the number of cells, defaulting to the F-Wave solver. With 4 arguments, it also allows users to specify the solver choice (Roe or F-Wave). This extension enhances the program's adaptability to various simulation scenarios and solver preferences.

Middle state check
^^^^^^^^^^^^^^^^^^

**CustomSetup1d**

* CustomSetup1d constructor:
    Initializes the CustomSetup1d class with parameters representing a custom Roe problem, including height and x-momentum values on the left and right sides, and the location of the middle point.

* getHeight function:
    Returns the height value based on the x coordinate, distinguishing between the left and right sides of the middle point.

* getMomentumX function:
    Returns the x-momentum value based on the x coordinate, differentiating between the left and right sides of the middle point.

* getMomentumY function:
    Always returns a constant value of 0, indicating that the y-momentum is zero in this problem regardless of the location.

.. literalinclude:: ../../../src/setups/CustomSetup1d/CustomSetup1d.cpp
    :language: c++

CustomSetup1d allows us to fill the array with custom values.

**Csv.cpp**

.. code-block::

  void tsunami_lab::io::Csv::read_middle_states(std::ifstream &io_stream,
                                              t_real *&o_heightsL,
                                              t_real *&o_momentumsL,
                                              t_real *&o_heightsR,
                                              t_real *&o_momentumsR,
                                              t_real *&o_hStar)
  {
    tsunami_lab::t_idx l_length = 1000000;
    std::string l_line;
    std::stringstream l_lineStream;

    // skip header
    for (size_t i = 0; i < 8; i++)
    {
      std::getline(io_stream, l_line);
    }

    o_heightsL = (t_real *)malloc(l_length * sizeof(t_real));
    o_heightsR = (t_real *)malloc(l_length * sizeof(t_real));
    o_momentumsL = (t_real *)malloc(l_length * sizeof(t_real));
    o_momentumsR = (t_real *)malloc(l_length * sizeof(t_real));
    o_hStar = (t_real *)malloc(l_length * sizeof(t_real));

    for (t_idx i = 0; i < l_length; i++)
    {
      // read next line
      std::getline(io_stream, l_line);
      // std::cout << i << " : " << l_line << std::endl;
      l_lineStream << l_line;
      std::string l_cell;

      // load left height
      std::getline(l_lineStream, l_cell, ',');
      o_heightsL[i] = std::stof(l_cell);

      // load right height
      std::getline(l_lineStream, l_cell, ',');
      o_heightsR[i] = std::stof(l_cell);

      // load left momentum
      std::getline(l_lineStream, l_cell, ',');
      o_momentumsL[i] = std::stof(l_cell);

      // load right momentum
      std::getline(l_lineStream, l_cell, ',');
      o_momentumsR[i] = std::stof(l_cell);

      // load h*
      std::getline(l_lineStream, l_cell, ',');
      o_hStar[i] = std::stof(l_cell);

      l_lineStream.clear();
    }
  }

We extended the Csv.cpp with the read_middle_states function. The read_middle_states function reads specific data from a CSV file stream, storing it in arrays. It skips the header, allocates memory for arrays, and then reads and parses each line of the CSV file, extracting left heights, right heights, left momentums, right momentums, and h* values. The data is saved in separate arrays, and the function is designed to handle large datasets.

**main.cpp**

.. code-block::
    
  ...
    
    else if (l_scenario == "ShockShock") 
  {
    // initialize dam break scenario
    l_scenarioCount = 1;
    l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));

    l_hL[0] = 10;
    l_hR[0] = 10;
    l_huL[0] = 18;
    l_huR[0] = 18;
    l_hStar[0] = 0;
  }
  else if (l_scenario == "RareRare") 
  {
    l_scenarioCount = 1;
    l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));

    l_hL[0] = 10;
    l_hR[0] = 3;
    l_huL[0] = 0;
    l_huR[0] = 3;
    l_hStar[0] = 0;
  }
  else if (l_scenario == "CustomSetup") 
  {
    l_scenarioCount = 1;
    l_hL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_hR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_huL = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_huR = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
    l_hStar = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));

    l_locMiddle = tsunami_lab::t_real(0.004);
    l_hL[0] = tsunami_lab::t_real(1.4);
    l_hR[0] = tsunami_lab::t_real(0.35);
    l_huL[0] = 0;
    l_huR[0] = tsunami_lab::t_real(0.07);
    l_hStar[0] = 0;
  }
  else if (l_scenario == "Sanitize1d") 
  {
    // initialize middle state sanitization
    l_scenarioCount = 1000000;

    std::ifstream l_stream;
    // try to read middle states original file
    std::cout << "reading /res/middle_states.csv ..." << std::endl;
    l_stream.open("./res/middle_states.csv", std::fstream::in);

    if(l_stream.fail()) 
    {
      std::cout << "failed to read /res/middle_states.csv" << std::endl;
      l_stream.clear();

      // try to read dummy middle states file
      std::cout << "reading /res/dummy_middle_states.csv ..." << std::endl;
      l_stream.open("./res/dummy_middle_states.csv", std::fstream::in);
      l_scenarioCount = 10;
      if(l_stream.fail()) 
      {
        std::cerr << "failed to read /res/dummy_middle_states.csv" << std::endl;
        return EXIT_FAILURE;
      }
      std::cout << "finished reading /res/dummy_middle_states.csv" << std::endl;
    } 
    else 
    {
      std::cout << "finished reading /res/middle_states.csv" << std::endl;
    }

    tsunami_lab::io::Csv::read_middle_states( l_stream, 
                                              l_hL, 
                                              l_huL, 
                                              l_hR, 
                                              l_huR, 
                                              l_hStar);
  }
  else
  {
    std::cerr << "entered SCENARIO_MODE is unknown" << std::endl;
    return EXIT_FAILURE;
  }
  
  for(tsunami_lab::t_idx l_idx = 0; l_idx < l_scenarioCount; l_idx++) 
  {
    std::cout << "enter scenario: " << l_idx << std::endl;
    tsunami_lab::setups::Setup *l_setup;
    if(l_scenario == "DamBreak") 
    {
      l_setup = new tsunami_lab::setups::DamBreak1d(  l_hL[l_idx],
                                                      l_hR[l_idx],
                                                      l_locMiddle);
    }
    else if (l_scenario == "ShockShock") 
    {
      l_setup = new tsunami_lab::setups::ShockShock1d( l_hL[l_idx],
                                                       l_huL[l_idx],
                                                       l_locMiddle);
    }
    else if (l_scenario == "RareRare") 
    {
      l_setup = new tsunami_lab::setups::RareRare1d( l_hR[l_idx],
                                                     l_huR[l_idx],
                                                     l_locMiddle);
    }
    else if (l_scenario == "CustomSetup") 
    {
      l_setup = new tsunami_lab::setups::CustomSetup1d( l_hL[l_idx],
                                                        l_hR[l_idx],
                                                        l_huL[l_idx],
                                                        l_huR[l_idx],
                                                        l_locMiddle);
    }
    else if (l_scenario == "Sanitize1d") 
    {
      l_setup = new tsunami_lab::setups::CustomSetup1d( l_hL[l_idx],
                                                        l_hR[l_idx],
                                                        l_huL[l_idx],
                                                        l_huR[l_idx],
                                                        l_locMiddle);
    } 
    else 
    {
      std::cerr << "entered SCENARIO_MODE is unknown" << std::endl;
      return EXIT_FAILURE;
    }

    // construct solver
    tsunami_lab::patches::WavePropagation *l_waveProp;
    l_waveProp = new tsunami_lab::patches::WavePropagation1d(l_nx, l_use_roe_solver);

    // maximum observed height in the setup
    tsunami_lab::t_real l_hMax = std::numeric_limits<tsunami_lab::t_real>::lowest();
    ...

We added this code-block to the main. It reads the user-selected scenario, allocates memory for scenario parameters, and initializes those parameters based on the selected scenario. Then, it iterates over each scenario and constructs a corresponding setup and solver for further tsunami simulation. Finally, it calculates the maximum observed height in the chosen setup.
The function of this code is determined by the input scenario specified by the user. If the selected scenario is "Sanitize1d," it reads and calculates middle states from a CSV file. For other scenarios such as "DamBreak," "ShockShock," "RareRare," or "CustomSetup," it initializes parameters for these scenarios and constructs a solver for the tsunami simulation without reading middle states. 

.. _ch:Shock_and_Rarefaction_Waves:

Shock and Rarefaction Waves 
---------------------------

.. admonition:: Tasks

    #. Implement the shock-shock and rare-rare problems as setups.
    #. Play
       around with different sets of initial water heights :math:`h_l` and
       particles velocities :math:`u_l`. What do you observe? Is there a
       connection to the wave speeds :math:`\lambda_{1/2} = u \mp \sqrt{gh}`?

Implemntation of Shock-Shock setups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. RareRare1d: This is the constructor of the RareRare1d class, initializing the key parameters for the rare-rare problem, such as the initial height (i_h), initial x-momentum (i_hu), and the location of a discontinuity (i_dis).

#. getHeight: This function is used to retrieve the height value at a specific location (i_x, i_y). In this 1D problem, the height value is constant and equal to m_h.

#. getMomentumX: This function provides the x-momentum value at a specific location (i_x, i_y). The value depends on the location relative to the discontinuity (m_dis). If i_x is less than or equal to m_dis, the x-momentum is set to -m_hu, and otherwise, it is m_hu.

#. getMomentumY: This function is used to retrieve the y-momentum value at a specific location (i_x, i_y). In this specific problem, the y-momentum is always constant and equal to 0.

.. literalinclude:: ../../../src/setups/RareRare1d/RareRare1d.cpp
    :language: c++

In this one-dimensional rare-rare problem represented by the RareRare1d class, the behavior of the wave is described by the distribution of momentum. Specifically, on the left side of the discontinuity point (m_dis), the x-momentum is positive, indicating that the wave is moving to the right. Conversely, on the right side of the discontinuity, the x-momentum is negative, signifying that the wave is moving to the left. These opposing momenta result in the two wave components colliding at the "smash position," which is the location of the discontinuity. 

Implemntation of rare-rare setups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. RareRare1d: This is the constructor of the RareRare1d class, initializing the key parameters for the rare-rare problem, such as the initial height (i_h), initial x-momentum (i_hu), and the location of a discontinuity (i_dis).

#. getHeight: This function is used to retrieve the height value at a specific location (i_x, i_y). In this 1D problem, the height value is constant and equal to m_h.

#. getMomentumX: This function provides the x-momentum value at a specific location (i_x, i_y). The value depends on the location relative to the discontinuity (m_dis). If i_x is less than or equal to m_dis, the x-momentum is set to -m_hu, and otherwise, it is m_hu.

#. getMomentumY: This function is used to retrieve the y-momentum value at a specific location (i_x, i_y). In this specific problem, the y-momentum is always constant and equal to 0.


.. literalinclude:: ../../../src/setups/ShockShock1d/ShockShock1d.cpp
    :language: c++

In the rare-rare problem represented by the RareRare1d class, the wave behavior is distinct from the previous example. Here, the wave components are moving apart from each other on either side of the discontinuity point (m_dis). On the left side, the x-momentum is positive, indicating that the wave is traveling to the right, while on the right side, the x-momentum is also positive, signifying a rightward motion. This results in the wave components moving away from the m_dis point, rather than colliding. 

Connection between h_l and u_l
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. math::
   :label: eq:shockcond

   q_l=
           \begin{bmatrix}
             h_l \\ (hu)_l
           \end{bmatrix}, \quad
         q_r =
           \begin{bmatrix}
             h_r \\ (hu)_r
           \end{bmatrix} =
           \begin{bmatrix}
             h_l \\ -(hu)_l
           \end{bmatrix}.

At first we have to calculate u.

.. math::
  :label: eq: particle velocity

  u^{\text{Roe}}(q_l, q_r) =  \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l}+\sqrt{h_r}}

We know that 

.. math::

  h_r = h_r
  u_l = - u_r

So we can calculate u_l

.. math::

  \frac{u_l \sqrt{h} + (-u_l) \sqrt{h}}{2 \sqrt{h}}
  = \frac{ \sqrt{h} (u_l - u_l)}{ 2 \sqrt{h}}
  = \frac{0}{2 sqrt{h}}
  = 0

So the speeds

.. math::

  \lambda_{1,2}=u \pm \sqrt{g h}

only depend on the hight and the gravitational constant

.. math::

  \lambda_{1,2}= \pm \sqrt{g h}

Visualization
^^^^^^^^^^^^^

.. figure:: ../_static/video_folder/assignment_2/RareRare_10_5_mom.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/RareRare_10_18.mp4
  :width: 600px
  
.. figure:: ../_static/video_folder/assignment_2/RareRare_10_5.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/RareRare_20_5.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/ShockShock_10_18.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/ShockShock_10_5.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/ShockShock_20_5.mp4
  :width: 600px

Dam-Break
---------

.. admonition:: Tasks

  #. Apply your solver to the dam-break setup and play around with different sets of initial water heights :math:`h_l` and :math:`h_r`.
     What do you observe? How large is the impact of the particle velocity :math:`u_r` in the river?
  #. Assume a water reservoir of unlimited size and a village 25 km downstream with initial values :math:`q_l=[14, 0]^T` and :math:`q_r=[3.5, 0.7]^T`.
     How much time do you have to evacuate the village in our model before the shock wave arrives?


If the water in behind the dam is higher than the river it creates a shock wave, that floods the river. The higher the water the higher
created shockwave. When the water is lower than the river a rare wave is created moving in the direction of the river. The faster the water
in the river is, the faster will the created shock or rare wave travel along the river.


Since simulating the whole travel of the shock wave would take longer than 1.25 of simulation time, we downscaled every length by 10. This
would decrease the accuracy but make the problem calculatable.

We set up the finite volume solver as following: we have a reservoir with the height of :math:`1.4 \frac{m}{10}` a river height of :math:`0.37 \frac{m}{10}` and a distance to the village of :math:`2500 \frac{m}{10}`. The river has a momentum of 
:math:`0.07 kg\frac{m}{10s}`

After letting the simulation run for 2300 seconds the shock wave traveled for :math:`1100 \frac{m}{10}` in the direction of the village. 
If the wave travels on with the same speed, it reaches the village after 5227 seconds. Calculated to hours, we have 1.45 hours to evacuate 
the village. 


.. figure:: ../_static/video_folder/assignment_2/DamBreak_10_0_3_3_mom.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/DamBreak_10_0_3_3.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/db_10_0_3_15.mp4
  :width: 600px



.. figure:: ../_static/video_folder/assignment_2/Dam_and_river_mom.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_2/Dam_and_river.mp4
  :width: 600px