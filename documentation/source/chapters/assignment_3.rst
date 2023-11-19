.. _ch:Task_3:

Week Report 3
=============

.. _ch:Task_3_1:

Adding bathymetry support
-------------------------

.. admonition:: Tasks

    #. Extend the f-wave solver with support for bathymetry according to Eq. 3.1.1 and Eq. 3.1.2.

    #. Implement an example which illustrates the effect of bathymetry in your extended solver. 
       **Note:** You have to add bathymetry to the respective patches implementing the abstract class ``patches::WavePropagation`` as well. 
       Also, ghost cells require a valid value for the bathymetry, i.e., :math:`b_0 := b_1` set and :math:`b_{n+1} := b_n`.

Implementation in F-Wave solver
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Adding the implementation for bathymetry in the f-wave solver comes down to changing the computation of the wave strengths from:

.. math::
    
    \begin{bmatrix} \alpha_1 \\ \alpha_2 \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ \lambda_1 & \lambda_2 \end{bmatrix} \cdot \Delta f 

to the following, which was taken from Eq. 3.1.2:

.. math::

    \begin{bmatrix} \alpha_1 \\ \alpha_2 \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ \lambda_1 & \lambda_2 \end{bmatrix} \cdot (\Delta f  - \Delta x \Psi_{i + 1/2})

In the code this meant, that we only made changes in ``solvers::FWave::waveStrengths``:

.. code-block::

    ...

    t_real l_delta_x_psi[2];
    l_delta_x_psi[0] = 0;
    l_delta_x_psi[1] = (-tsunami_lab::solvers::FWave::c_g) * (i_bR - i_bL) * ((i_hL + i_hR) / 2);

    t_real l_decomposition_flux[2];
    l_decomposition_flux[0] = l_delta_flux[0] - l_delta_x_psi[0];
    l_decomposition_flux[1] = l_delta_flux[1] - l_delta_x_psi[1];

    // calculate reversed determinant
    t_real l_rev_det = 1 / (i_waveSpeedR - i_waveSpeedL);

    // calculate the inverse of the matrix R
    t_real l_R_inv[2][2] = {0};
    l_R_inv[0][0] = l_rev_det * i_waveSpeedR;
    l_R_inv[0][1] = -l_rev_det;
    l_R_inv[1][0] = -l_rev_det * i_waveSpeedL;
    l_R_inv[1][1] = l_rev_det;

    // calculate wave strengths
    o_strengthL = l_R_inv[0][0] * l_decomposition_flux[0];
    o_strengthL += l_R_inv[0][1] * l_decomposition_flux[1];
    o_strengthR = l_R_inv[1][0] * l_decomposition_flux[0];
    o_strengthR += l_R_inv[1][1] * l_decomposition_flux[1];

We added the variable ``l_delta_x_psi`` that holds the vector :math:`\Delta x \Psi_{i + 1/2}` and ``l_decomposition_flux``
holding :math:`\Delta f - \Delta x \Psi_{i + 1/2}`.

Implementation in WavePropagation1d
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We added an array as a ``m_b`` private member variable, since the bathymetry needs to be stored for every cell. In addition, 
we needed the getter function ``patches::WavePropagation::getBathymetry`` to be able to access the bathymetry of each cell.

.. code-block::

   ...

   /**
   * Sets the bathymetry to the given value.
   * 
   * @param i_ix id of the cell in x-direction.
   * @param i_b bathymetry.
   **/
  void setBathymetry( t_idx i_ix,
                      t_real i_b) 
  {
    m_b[i_ix + 1] = i_b;
  }

  ...

For demonstration, we constructed a created a DamBreak setup, that has bathymetry of 0 in all cells but 
from 50% to 75% where it has a value of -3.75. This had the following result:

.. figure:: ../_static/video_folder/assignment_3/only_hill.mp4
  :width: 600px

.. _ch:part_3_2:

Boundary Conditions
-------------------

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


.. _ch:part_3_3:

Maximum Froude value
--------------------

.. admonition:: Tasks

    #. Compute the location and value of the maximum Froude number for the subcritical setting given in Eq. 3.3.1 and the supercritical setting given in Eq. 3.3.2 at the initial time :math:`t = 0`.

    #. Implement both cases through the base class setup::Setup.h. :math:`t \in [0, 200]` is a reasonable time window for your simulation.

    #. Determine the position of the hydraulic jump (stationary discontinuity) in your supercritical solution and show that our f-wave solver fails to converge to the analytically expected constant momentum over the entire domain.

First we look upon the equation to calculate the Froude number:

.. math::

    F = \frac{(\frac{hu}{h})}{\sqrt{g \cdot h}} = \frac{hu}{h} \cdot \frac{1}{\sqrt{g \cdot h}} = \frac{hu}{\sqrt{g} \cdot \sqrt{h}^3}

Since for both cases :math:`hu` and :math:`g` are constant we only need to look at the height. :math:`F` will be the highest, when :math:`h` is the lowest.

Subcritical Flow
^^^^^^^^^^^^^^^^

For the height function:

.. math::

    h(x, 0) = 1.8 + 0.05(10 - x)^2

exists one minimum at :math:`x = 10`, which was derived from the first derivation. Concluding in a Froude number of ::math:`F = \frac{(\frac{hu}{h})}{\sqrt{g \cdot h}} = 0.59`

Supercritical Flow:
^^^^^^^^^^^^^^^^^^^

For the height function:

.. math::

    h(x, 0) = 0.13 + 0.05(10 - x)^2

also exists a minimum at :math:`x = 10`. This concludes in the Froude number: ::math:`F = \frac{(\frac{hu}{h})}{\sqrt{g \cdot h}} = 1.22`

Implementing the setups
^^^^^^^^^^^^^^^^^^^^^^^

For the subcritical case we implemented a class ``setups::SubcriticalFlow1d`` that inherits from the class in the file ``setup::Setup.h``. The constructor has only one parameter ``i_hu``, that is suposed
to hold the momentum value used in the setup. The other function are implementing the class just like Eq. 3.3.1 dictates them to be.

.. code-block::

    tsunami_lab::setups::SubcriticalFlow1d::SubcriticalFlow1d(t_real i_hu) {
    m_hu = i_hu;
    }

    tsunami_lab::t_real tsunami_lab::setups::SubcriticalFlow1d::getHeight(t_real i_x,
                                                                          t_real) const {
        return -tsunami_lab::setups::SubcriticalFlow1d::getBathymetry(i_x, 0);
    }

    tsunami_lab::t_real tsunami_lab::setups::SubcriticalFlow1d::getMomentumX(t_real,
                                                                             t_real) const {
        return m_hu;
    }

    tsunami_lab::t_real tsunami_lab::setups::SubcriticalFlow1d::getMomentumY(t_real,
                                                                             t_real) const {
        return 0;
    }

    tsunami_lab::t_real tsunami_lab::setups::SubcriticalFlow1d::getBathymetry(t_real i_x,
                                                                              t_real) const {
        if ((i_x > 8) & (i_x < 12)) {
            return -1.8 - 0.05 * pow((i_x - 10), 2);
        } else {
            return -2;
        }
    }

Similar to this the class ``setup::SupercriticalFlow1d`` was implemented. 

.. code-block::

    tsunami_lab::setups::SupercriticalFlow1d::SupercriticalFlow1d(t_real i_hu) {
    m_hu = i_hu;
    }

    tsunami_lab::t_real tsunami_lab::setups::SupercriticalFlow1d::getHeight(t_real i_x,
                                                                            t_real) const {
        return -tsunami_lab::setups::SupercriticalFlow1d::getBathymetry(i_x, 0);
    }

    tsunami_lab::t_real tsunami_lab::setups::SupercriticalFlow1d::getMomentumX(t_real,
                                                                               t_real) const {
        return m_hu;
    }

    tsunami_lab::t_real tsunami_lab::setups::SupercriticalFlow1d::getMomentumY(t_real,
                                                                               t_real) const {
        return 0;
    }

    tsunami_lab::t_real tsunami_lab::setups::SupercriticalFlow1d::getBathymetry(t_real i_x,
                                                                                t_real) const {
        if ((i_x > 8) & (i_x < 12)) {
            return -0.13 - 0.05 * pow((i_x - 10), 2);
        } else {
            return -0.33;
        }
    }

When simulating these setups for 200 timesteps on 25 meters we got the following results.

Subcritical Flow:

.. figure:: ../_static/video_folder/assignment_3/subcritical_flow.mp4
  :width: 600px

Supercritical Flow:

.. figure:: ../_static/video_folder/assignment_3/supercritical_flow.mp4
  :width: 600px

Supercritical Flow momentum:

.. figure:: ../_static/video_folder/assignment_3/supercritical_flow_mom.mp4
  :width: 600px

Stationary Discontinuity
^^^^^^^^^^^^^^^^^^^^^^^^

The stationary discontinuity is located in the 115 cell or in at 11.5 meters. 
At the end all cells have a momentum around 0.12, but the 115-th cell has a 
momentum of 0.14. This makes shows, that the momentum does not converge to a constant. 

.. _ch:part_3_4:

TsunamiEvent simulation
-----------------------

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

we assume, that :math:`\delta := 20\,\text{m}`.

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

Changes in main.cpp for support of knew functionalities.

.. code-block:: c++


    ...
    } else if (l_scenario == "TsunamiEvent1d") {
        // initialize middle state sanitization
        l_scenarioCount = 100000;
        std::string filePath = "./res/dem.csv";

        std::ifstream l_stream;
        // try to read middle states original file
        std::cout << "reading /res/dem.csv ..." << std::endl;
        l_stream.open(filePath, std::fstream::in);

        std::cout << "finished reading /res/dem.csv" << std::endl;


        l_distance = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
        l_bathymetry = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
        l_x = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));
        l_y = (tsunami_lab::t_real *)malloc(l_scenarioCount * sizeof(l_scenarioCount));

        tsunami_lab::io::Csv::read_gmt_states(l_stream,
                                              l_bathymetry,
                                              l_x,
                                              l_y,
                                              l_distance);
    }
    ...

.. code-block:: c++

    ...
    } else if (l_scenario == "TsunamiEvent1d") {
        l_setup = new tsunami_lab::setups::TsunamiEvent1d(l_bathymetry);
    }
    ...