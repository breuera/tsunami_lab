Tsunami Report 3 Bathemetry & Boundary Conditions
=============================================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: all members contributed equally

Thorsten Kröhl: all members contributed equally

Julius Halank: all members contributed equally

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

.. video:: _static/3_DamBreak1d_10_2_bathymetry.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam break with h_l=10 and h_r=2 and a bathymetry that increases from -2 to -1 and goes back to -2 at x=0, x=5 and x=10 respectively.

.. video:: _static/3_2_DamBreak1d_10_2.mp4
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

.. video:: _static/3_WallBoundary.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

reflecting right boundary condition with open left boundary condition, h=10 and u=10

.. video:: _static/3_ShockShock1d_10_100.mp4
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

.. video:: _static/3_SuperCrit1d.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

3.4 Tsunami simulation
----------------------

We will use a csvReader library `rapidcsv <https://github.com/d99kris/rapidcsv>`_ in our reader.
Is a header only library that you can include by just adding the header file to your project.


3.4.1 Extract bathymetry data with 250m sampling
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

after applying the following commands to the cut bathymetry grid we get the following csv (only excerpt shown)

.. code:: console

  gmt grdtrack -GGeco.nc -E141.024949/37.316569/146.0/37.316569+i250e+d -Ar > data.csv
  cat data.csv | tr -s '[:blank:]'' ',' > data.csv

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

Use rapidcsv to read the csv file and access the fourth column of it.
The param :code:`rapidcsv::LabelParams(-1, -1)` is used to tell the reader that the csv file has no header and no index column.

.. code:: cpp

  void tsunami_lab::io::Csv::openCSV(const std::string &i_filePath, rapidcsv::Document &o_doc, size_t &o_rowCount)
  {
  // assume headless csv
  o_doc = rapidcsv::Document(i_filePath, rapidcsv::LabelParams(-1, -1));
  o_rowCount = o_doc.GetRowCount();
  }

  tsunami_lab::t_real tsunami_lab::io::Csv::readLine(const rapidcsv::Document &i_doc, size_t i_row)
  {
  float o_row = i_doc.GetRow<float>(i_row)[3];
  return o_row;
  }

3.4.3 Implement a setup that initializes 1d tsunamis
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Added a TsunamiEvent1d setup that uses a :code:`rapidcsv::document` csv file to read the bathymetry data and a function to calculate the displacement.

.. code:: cpp

  tsunami_lab::setups::TsunamiEvent1d::TsunamiEvent1d(rapidcsv::Document i_doc, size_t i_rowCount)
  {
  m_doc = i_doc;
  m_rowCount = i_rowCount;
  }

The displacement function is just a simple sine function between 175km and 225km.

.. code:: cpp

  tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getDisplacement(t_real i_x) const
  {
  if (175000 < i_x && i_x < 225000)
  {
    return 10 * std::sin(M_PI * (i_x - 175000) / 37500 + M_PI);
  }
  else
  {
    return 0;
  }
  }

And the bathymetry gets read of the csv file and the displacement is added to it.
A :math:`\delta` (minimum offset from 0m height) of 20m is used so we don't run into numeric problems with cells wetting and drying.

.. code:: cpp

  tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetry(t_real i_x,
                                                                       t_real) const
  {
  t_real l_bin = getBathymetryBin(i_x);
  if (l_bin < 0)
  {
    // min(bin, -delta) + d
    if (l_bin < -m_delta)
      return l_bin + getDisplacement(i_x);
    else
      return -m_delta + getDisplacement(i_x);
  }
  // max(bin, delta) + d
  if (l_bin > m_delta)
    return l_bin + getDisplacement(i_x);
  else
    return m_delta + getDisplacement(i_x);
  }

  tsunami_lab::t_real tsunami_lab::setups::TsunamiEvent1d::getBathymetryBin(t_real i_x) const
  {
  // convert i_x to cell index (assuming 250m cells)
  int l_row = i_x / 250;
  return io::Csv::readLine(m_doc, l_row);
  }

3.4.4 Visualize the tsunami setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. video:: _static/3_Tsunami1d.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

.. video:: _static/3_Tsunami1d_onlyHeight.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

The Tsunami Setup simulated over an hour of time.

3.4.5 Impact of different initial displacements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. video:: _static/3_Tsunami1d_2.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

A version with twice the initial displacement.
(instead of :math:`10 \sin(\frac{(x - 175000)}{37500}\pi+ \pi)` we used :math:`20 \sin(\frac{(x - 175000)}{37500}\pi  + \pi)`).
The momentum traveling to both sides of the simulations are roughly twice as high. 
Maybe a linear relationship between the initial displacement and the momentum is present?

.. video:: _static/3_Tsunami1d_20.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

.. video:: _static/3_Tsunami1d_20_onlyHeight.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

A version with a static 20 meter displacement in between 175km and 225km and a left reflective boundary.
It seems to travel as a single big wave towards japan mainland hitting it with roughly 15m height and getting reflected to roughly half the height.
This is basically our dambreak problem in 2 directions without an infinite water source
The lower video is just the height of the water without the momentum and bathymetry.
