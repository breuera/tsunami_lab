.. _ch:Task_3_bohdan:

Report Bohdan
=============


.. _ch:reflecting_boundary_conditions:


Reflecting Boundary conditions
------------------------------

.. admonition:: Tasks

  #. Implement reflecting boundary conditions.

  #. Show that you obtain the shock-shock's one-sided solution of the shock-shock setup if you set :math:`q_l` everywhere initially and use reflecting boundary conditions at the right boundary, and outflow boundary conditions at the left boundary.
     **Note:** Reflecting boundary conditions for the right boundary can be implemented through a ghost cell :math:`\mathcal{C}_{n+1}` that is dry.

Added new Boundary Conditions to WavePropagation1d so that

.. math::
   :label: eq:reflecting_bc

   h_{i} &:= h_{i-1} \\
   (hu)_{i} &:= -(hu)_{i-1} \\
   b_{i} &:= b_{i-1}

the condition is met. Four different methods for setting ghost cells:

**Case 1: Both ghost cells have the reflicting boundary condition.**

.. code-block:: c++

    void tsunami_lab::patches::WavePropagation1d::setGhostReflectingBoundaryConditions()
    {
        t_real *l_h = m_h[m_step];
        t_real *l_hu = m_hu[m_step];

        // set left boundary
        l_h[0] = l_h[1];
        l_hu[0] = -l_hu[1];

        // set right boundary
        l_h[m_nCells + 1] = l_h[m_nCells];
        l_hu[m_nCells + 1] = -l_hu[m_nCells];
    }

**Case 2: Left ghost cell has the reflecting boundary condition and the right one has the outflow boundary condition**

.. code-block:: c++

    void tsunami_lab::patches::WavePropagation1d::setGhostLeftReflectingBoundaryCondition()
    {
        t_real *l_h = m_h[m_step];
        t_real *l_hu = m_hu[m_step];

        // set left boundary
        l_h[0] = l_h[1];
        l_hu[0] = -l_hu[1];

        // set right boundary
        l_h[m_nCells + 1] = l_h[m_nCells];
        l_hu[m_nCells + 1] = l_hu[m_nCells];
    }

**Case 3: Right ghost cell has the reflecting boundary condition and the left one has the outflow boundary condition**

.. code-block:: c++

    void tsunami_lab::patches::WavePropagation1d::setGhostRightReflectingBoundaryCondition()
    {
        t_real *l_h = m_h[m_step];
        t_real *l_hu = m_hu[m_step];

        // set left boundary
        l_h[0] = l_h[1];
        l_hu[0] = l_hu[1];

        // set right boundary
        l_h[m_nCells + 1] = l_h[m_nCells];
        l_hu[m_nCells + 1] = -l_hu[m_nCells];
    }

**Case 4: Both ghost cells have the outflow condition**

.. code-block:: c++

    void tsunami_lab::patches::WavePropagation1d::setGhostOutflow()
    {
        t_real *l_h = m_h[m_step];
        t_real *l_hu = m_hu[m_step];

        // set left boundary
        l_h[0] = l_h[1];
        l_hu[0] = l_hu[1];
        m_b[0] = m_b[1];

        // set right boundary
        l_h[m_nCells + 1] = l_h[m_nCells];
        l_hu[m_nCells + 1] = l_hu[m_nCells];
        m_b[m_nCells + 1] = m_b[m_nCells];
    }

**Added new Flag for the Boundary conditions for the boundary conditions in the main.cpp**

.. code-block:: c++


    ...

    if (!(strcmp(i_argv[3], "-f") == 0 || strcmp(i_argv[3], "-r") == 0))
    {
      std::cerr << "invalid third argument(needs to be '-r' or '-f')" << std::endl;
      return EXIT_FAILURE;
    }

    if (!(strcmp(i_argv[4], "-oo") == 0 || strcmp(i_argv[4], "-rr") || strcmp(i_argv[4], "-or") || strcmp(i_argv[4], "-ro") == 0))
    {
      std::cerr << "invalid fourth argument(needs to be '-rr', '-oo', '-or' or '-ro')" << std::endl;
      return EXIT_FAILURE;
    }
    if (strcmp(i_argv[4], "-rr") == 0)
    {
      std::cout << "Boundery condition of both ghost cells were set to reflecting condition" << std::endl;
    }
    else if (strcmp(i_argv[4], "-oo") == 0)
    {
      std::cout << "Boundery condition of both ghost cells were set to outflow condition" << std::endl;
    }
    else if (strcmp(i_argv[4], "-or") == 0)
    {
      std::cout << "Left boundery condition was set to outflow condition and right boundery condition to reflecting condition" << std::endl;
    }
    else if (strcmp(i_argv[4], "-ro") == 0)
    {
      std::cout << "Right boundery condition was set to outflow condition and left boundery condition to reflecting condition" << std::endl;
    }
    
    ...
    
    if (l_boundary_conditions == "-rr") 
    {
        l_waveProp->setGhostOutflow();
    } 
    else if (l_boundary_conditions == "-ro") 
    {
        l_waveProp->setGhostOutflow();
    } 
    else if (l_boundary_conditions == "-or") 
    {
        l_waveProp->setGhostOutflow();
    } 
    else 
    {
        l_waveProp->setGhostOutflow();
    }
    l_waveProp->timeStep(l_scaling);

    ...

**Visualization of left ghost cell with reflecting boundary condition and right ghost cell with outflow condition.**


.. figure:: ../_static/video_folder/assignment_3/boundary_condition.mp4
  :width: 600px

.. figure:: ../_static/video_folder/assignment_3/boundary_condition_mom.mp4
  :width: 600px


.. _ch:1d_Tsunami_Simulation:

1D Tsunami Simulation
---------------------

.. admonition:: Tasks

  #. Extract bathymetry data for the 1D domain, from the GEBCO_2021 Grid. Use a 250m sampling between the two points :math:`p_1` and :math:`p_2`.
  #. Extend the class ``tsunami_lab::io::Csv`` such that it can read your extracted bathymetry data.
  #. Add a new setup ``setups::TsunamiEvent1d`` which uses your CSV reader and the artificial displacement to initialize your quantities as defined in :eq:`eq:tsunami_event_1d`.
  #. Run and visualize the setup. What runup do you observe?
 
**Bathymetry Data**

We extracted the data with the following commands:

.. code-block::

    //get the data 
    wget linkgmt drdinfor data_in/GC0_2021.nc

    //cut part of the map
    gmt grdcut -R138/147/35/39 data_in/DEBC0_2021.nc -Gdata_temp/GEBC0_2021_cut.nc

    //extract 1d data from cut
    mt drdtrack -Gdata_temp/GEBC0_2021_cut.nc -E141/37.31/146/37.31+i250e+d -Ar > data_temp/dem.csv

    //replace whitespaces with ,
    cat data_tem/dem.csv | tr -s '[:blank:]' ',' > dem.csv

We created the read_gmt_states() function to extract information from the dem.csv file.

.. code-block:: c++

    void tsunami_lab::io::Csv::read_gmt_states(std::ifstream &io_stream,
                                           t_real *&o_bathymetry,
                                           t_real *&o_x,
                                           t_real *&o_y,
                                           t_real *&o_distance) {
    tsunami_lab::t_idx l_length = 1763;
    std::string l_line;
    std::stringstream l_lineStream;

    o_bathymetry = (t_real *)malloc(l_length * sizeof(t_real));
    o_x = (t_real *)malloc(l_length * sizeof(t_real));
    o_y = (t_real *)malloc(l_length * sizeof(t_real));
    o_distance = (t_real *)malloc(l_length * sizeof(t_real));

    for (t_idx i = 0; i < l_length; i++) {
        // read next line
        std::getline(io_stream, l_line);
        // std::cout << i << " : " << l_line << std::endl;
        l_lineStream << l_line;
        std::string l_cell;

        // load x-coordinate
        std::getline(l_lineStream, l_cell, ',');
        o_x[i] = std::stof(l_cell);

        // load y-coordinate
        std::getline(l_lineStream, l_cell, ',');
        o_y[i] = std::stof(l_cell);

        // load distance
        std::getline(l_lineStream, l_cell, ',');
        o_distance[i] = std::stof(l_cell);

        // load bathymetry
        std::getline(l_lineStream, l_cell, ',');
        o_bathymetry[i] = std::stof(l_cell);
    
        l_lineStream.clear();
        }
    }

This function, tsunami_lab::io::Csv::read_gmt_states, reads data from a CSV file represented by the input file stream (io_stream). It extracts information such as x-coordinates, y-coordinates, distances, and bathymetry values, and stores them in separate arrays (o_x, o_y, o_distance, o_bathymetry). The function assumes a fixed length of 1763 for these arrays, because we extracted exact 1763 data points.


Now we calculate the height, momentum and bathymetry based on the following formulas:

.. math::
   :label: eq:tsunami_event_1d

   \begin{split}
       h  &= \begin{cases}
               \max( -b_\text{in}, \delta), &\text{if } b_\text{in} < 0 \\
               0, &\text{else}
             \end{cases}\\
       hu &= 0\\
       b  &= \begin{cases}
               \min(b_\text{in}, -\delta) + d, & \text{ if } b_\text{in} < 0\\
               \max(b_\text{in}, \delta) + d, & \text{ else}.
             \end{cases}
   \end{split}

and

.. math::

  d(x) = \begin{cases}
           10\cdot\sin(\frac{x-175000}{37500} \pi + \pi), & \text{ if } 175000 < x < 250000 \\
           0, &\text{else}.
         \end{cases}

we assume, that :math:`\delta := 20\,\text{m}.

So the implementation of the formulas are given in the following program.

.. code-block:: c++

    #include "TsunamiEvent1d.h"
    #include <algorithm>
    #include <cmath>
    #include <iostream>

    tsunami_lab::setups::TsunamiEvent1d::TsunamiEvent1d(t_real *i_bathymetry) {
        m_bathymetry = i_bathymetry;
    }

    tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getHeight(t_real i_x,
                                                                    t_real) const {
        if (m_bathymetry[(t_idx)std::floor(i_x / 250)] < 0) {
            return (-m_bathymetry[(t_idx)std::floor(i_x / 250)] < 20) ? 20 : -m_bathymetry[(t_idx)std::floor(i_x / 250)];
        }

        return 0;
    }

    tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumX(t_real,
                                                                        t_real) const {
        return 0;
    }

    tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getMomentumY(t_real,
                                                                        t_real) const {
        return 0;
    }

    tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetry(t_real i_x,
                                                                        t_real) const {
        float d = 0;
        if ((175000 < i_x) && (i_x < 250000)) {
            t_real pi = 3.14159265358979323846;
            d = 10 * sin(((i_x - 175000) / 37500) * pi + pi);
        }

        if (m_bathymetry[(t_idx)i_x] < 0) {
            return !(m_bathymetry[(t_idx)std::floor(i_x / 250)] < -20) ? -20 + d : m_bathymetry[(t_idx)std::floor(i_x / 250)] + d;
        } else {
            return (m_bathymetry[(t_idx)std::floor(i_x / 250)] < 20) ? 20 + d : m_bathymetry[(t_idx)std::floor(i_x / 250)] + d;
        }
    }