Tsunami Report 3 Bathemetry & Boundary Conditions
=============================================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: 

Thorsten Kröhl: 

Julius Halank: 

3.1 Non-zero Source Term
------------------------

3.1.1 Extend FWave Solver with Bathemetry
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Now calculating the :math:`\Delta x \Psi _{i-1/2}` term

.. code:: cpp

  void tsunami_lab::solvers::FWave::deltaXPsi(t_real i_bL,
                                            t_real i_bR,
                                            t_real i_hL,
                                            t_real i_hR,
                                            t_real &o_deltaXPsi)
  {
    // compute deltaXPsi
    o_deltaXPsi = -m_g * (i_bR - i_bL) * (i_hL + i_hR) / 2;
  }

and subtracting it from the flux jump.

.. code:: cpp

  deltaXPsi(i_bL, i_bR, i_hL, i_hR, l_deltaXPsi);

    // compute jump in fluxes
    t_real l_flux0Jump = l_flux0R - l_flux0L;
    t_real l_flux1Jump = l_flux1R - l_flux1L - l_deltaXPsi;

3.1.2 Implent an example which illistrates the effect of bathemetry
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. video:: _static/DamBreak1d_10_2_bathymetry.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam break with h_l=10 and h_r=2 and a bathymetry that increases from -2 to -1 and goes back to -2 at x=0, x=5 and x=10 respectively.

.. video:: _static/DamBreak1d_10_2.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam break with h_l=10 and h_r=2 as reference.

3.2 Reflecting boundary conditions
----------------------------------

3.2.1 Implement the reflecting boundary conditions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Added boundary conditions to the command line parameters as :code:`-b 'WALL OPEN'`

.. code:: cpp

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

      std::cout << "using boundary conditions " << l_boundaryLName << " " << l_boundaryRName << std::endl;

      // convert to t_boundary
      getBoundary(l_boundaryLName, &l_boundaryL);
      getBoundary(l_boundaryRName, &l_boundaryR);
      break;
    }

with a helper function that translates strings to t_boundary enum members

.. code:: cpp

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

and switches the ghost cells depending on the boundary conditions.

.. code:: cpp

  // set left boundary
  switch (m_boundaryLeft)
  {
  case t_boundary::OPEN:
  {
    l_h[0] = l_h[1];
    l_hu[0] = l_hu[1];
    break;
  }
  case t_boundary::WALL:
  {
    l_h[0] = l_h[1];
    l_hu[0] = -l_hu[1];
    break;
  }
  }




3.2.2 Show the implementation with the shock shock setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Added new setup to easier simulate tasks (with user controlled h_l h_r hu_l hu_r and middle position)

.. code:: cpp

  else if (l_setupName == "CUSTOM1D")
      {
        double l_arg3 = std::stof(l_arg3Str);
        double l_arg4 = std::stof(l_arg4Str);
        double l_arg5 = std::stof(l_arg5Str);
        std::cout << "using Custom1d(" << l_arg1 << "," << l_arg2 << "," << l_arg3 << "," << l_arg4 << "," << l_arg5 << ") setup" << std::endl;
        l_setup = new tsunami_lab::setups::Custom1d(l_arg1,
                                                    l_arg2,
                                                    l_arg3,
                                                    l_arg4,
                                                    l_arg5);
      }

.. video:: _static/WallBoundary.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

reflecting right boundary condition with open left boundary condition, h=10 and u=10

.. video:: _static/ShockShock1d_10_100.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Shock-Shock problem with h=10 and u=10

3.3 Hydraulic Jumps
-------------------

3.3.1 Compute the location and value of the maximum Froude number
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.3.2 Implement both cases through the base class setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.3.3 Determine the position of the hydraulic jump
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4 Tsunami simulation
----------------------

..
  todo: einordnen in den allgemeinen Aufbau

We will use for our csv reader a already existing one.
https://github.com/d99kris/rapidcsv
Is a simple csv reader that you can include by just adding the header file to your project.

Usage:

.. code:: cpp

  Date,Open,High,Low,Close,Volume,Adj Close
  2017-02-24,64.529999,64.800003,64.139999,64.620003,21705200,64.620003
  2017-02-23,64.419998,64.730003,64.190002,64.620003,20235200,64.620003
  2017-02-22,64.330002,64.389999,64.050003,64.360001,19259700,64.360001
  2017-02-21,64.610001,64.949997,64.449997,64.489998,19384900,64.489998
  2017-02-17,64.470001,64.690002,64.300003,64.620003,21234600,64.620003

.. code:: cpp

  #include <iostream>
  #include <vector>
  #include "rapidcsv.h"

  int main()
  {
    rapidcsv::Document doc("examples/colrowhdr.csv", rapidcsv::LabelParams(0, 0));

    std::vector<float> close = doc.GetRow<float>("2017-02-22");
    std::cout << "Read " << close.size() << " values." << std::endl;

    long long volume = doc.GetCell<long long>("Volume", "2017-02-22");
    std::cout << "Volume " << volume << " on 2017-02-22." << std::endl;
  }

3.4.1 Extract bathymetry data with 250m sampling
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Looks like this ..:

.. code:: cpp
  141.024949,37.316569,0,-8.39972685779
  141.027770389,37.31662806,250.000325724,-5.16040036612
  141.030591782,37.316687053,500.000650342,-5.84086714415
  141.033413179,37.316745979,750.000973849,-7.00688893922
  141.036234581,37.3168048381,1000.00129625,-8.38284211645
  141.039055988,37.3168636301,1250.00161755,-9.72846385298
  141.041877398,37.3169223552,1500.00193774,-11.2960085675
  141.044698813,37.3169810133,1750.00225683,-12.8667556012
  141.047520233,37.3170396044,2000.00257482,-14.2734481817
  141.050341657,37.3170981285,2250.0028917,-14.2909657429
  141.053163085,37.3171565857,2500.00320749,-14.8680894347
  141.055984517,37.3172149758,2750.00352218,-16.8438090957
  141.058805954,37.317273299,3000.00383578,-18.3854575741

3.4.2 Extend CSV class with reader for bathymetry data
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



3.4.3 Implement a setup that initializes 1d tsunamis
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4.4 Visualize the tsunami setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4.5 Impact of different initial displacements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




