Tsunami Report 3 Bathemetry & Boundary Conditions
=============================================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: Implemented Bathymetry and some project documentation

Thorsten Kröhl: Implemented CSV reader and DEM

Julius Halank: Implemented DEM

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

Implemented a reflecting boundary on a wet dry interface in the :code:`FWave` Solver.

.. code:: cpp

    bool updateL = true;
    bool updateR = true;
    // if both dry do nothing
    if (i_hL <= 0 && i_hR <= 0)
    {
        o_netUpdateL[0] = 0;
        o_netUpdateL[1] = 0;
        o_netUpdateR[0] = 0;
        o_netUpdateR[1] = 0;
        return;
    } // if only left side is dry, apply reflecting boundary condition
    else if (i_hL <= 0)
    {
        i_hL = i_hR;
        i_huL = -i_huR;
        i_bL = i_bR;
        updateL = false;
    } // if only right side is dry, apply reflecting boundary condition
    else if (i_hR <= 0)
    {
        i_hR = i_hL;
        i_huR = -i_huL;
        i_bR = i_bL;
        updateR = false;
    }
  
:code:`updateL` and :code:`updateR` are used to determine if the cells should be updated or not (dry cells don't change).

Added boundary conditions to the command line parameters as :code:`-b 'WALL OPEN'` in the :code:`main` function.

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

with a helper function that translates strings to :code:`t_boundary` enum members

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

and switches the ghost cells depending on the boundary conditions in :code:`WavePropagation1d`.

.. code:: cpp

  // set left boundary
  switch (m_boundaryLeft)
  {
  case t_boundary::OPEN:
  {
    l_h[0] = l_h[1];
    l_hu[0] = l_hu[1];
    l_b[0] = l_b[1];
    break;
  }
  case t_boundary::WALL:
  {
    l_h[0] = 0;
    l_hu[0] = 0;
    l_b[m_nCells + 1] = 20;
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

In :math:`x \in [0,25]` the maximum Froude number is given by

.. math::

  F(x) &= \frac{u(x)}{\sqrt{g h(x)}} \\
  \\
  h_{sub}(x) &= -b_{sub}(x) = 
      \begin{cases}
        1.8 + 0.05 (x-10)^2 \quad   &\text{if } x \in (8,12) \\
        2 \quad &\text{else}
      \end{cases}\\
  u_{sub}(x) &= \frac{4.42}{h_{sub}(x)} \\
  F_{sub}(x) &= \frac{u_{sub}(x)}{\sqrt{g h_{sub}(x)}} = \frac{4.42}{\sqrt{g}\cdot h_{sub}(x)^{3/2}} \\
  x_{max(F_{sub}(x))} &= x_{min(h_{sub}(x))} = 10 \\
  F_{sub}(10) &= \frac{4.42}{\sqrt{g}\cdot h_{sub}(10)^{3/2}} = \frac{4.42}{\sqrt{g}\cdot 1.8^{3/2}} = 0.58446 \\
  \\
  h_{super}(x) &= -b_{super}(x) = 
      \begin{cases}
        0.13 + 0.05 (x-10)^2 \quad   &\text{if } x \in (8,12) \\
        0.33 \quad &\text{else}
      \end{cases}\\
  u_{super}(x) &= \frac{0.18}{h_{super}(x)} \\
  x_{max(F_{super}(x))} &= x_{min(h_{super}(x))} = 10 \\
  F_{super}(x) &= \frac{0.18}{\sqrt{g}\cdot h_{sub}(10)^{3/2}} = \frac{0.18}{\sqrt{g}\cdot 0.18^{3/2}} = 30.1125 \\

3.3.2 Implement both cases through the base class setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Implemented both setups and changed their endtime in the main function.

.. code:: cpp

  tsunami_lab::t_real tsunami_lab::setups::Supercritical1d::getBathymetry(t_real i_x,
                                                                        t_real) const
  {
  if (8 < i_x && i_x < 12)
  {
    return -0.13 - 0.05 * (i_x - 10) * (i_x - 10);
  }
  else
  {
    return -0.33;
  }
  }

.. code:: cpp

  else if (l_setupName == "SUPERCRIT1D")
      {
        l_width = 25.0;  // 25 m domain
        l_endTime = 200; // 200 s simulation time
        std::cout << "  using Supercritical1d() setup" << std::endl;
        l_setup = new tsunami_lab::setups::Supercritical1d();
      }

3.3.3 Determine the position of the hydraulic jump
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The hydraulic jump occurs between :math:`x_{id}=45` and :math:`x_{id}=47`, which would represent :math:`x=0.45 \cdot 25 = 11.25` and :math:`x=0.47 \cdot 25 = 11.75` respectively.
You can see a distinct spike in momentum around :math:`x_{id}=46` which is the failure of our f-wave solver to converge to the constant momentum.

.. video:: _static/SuperCrit1d.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

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

3.4.2 Extend CSV class with reader for bathymetry data
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4.3 Implement a setup that initializes 1d tsunamis
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4.4 Visualize the tsunami setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4.5 Impact of different initial displacements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




