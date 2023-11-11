Tsunami Report 2 Finite Volume Discretization
=============================================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: wrote project report and implemented extra command line argument

Thorsten Kröhl: implemented Doxygen integration in Sphinx

Julius Halank: added test cases for setups

2.0 Integrate FWave Solver
--------------------------

2.0.1 FWave Solver Integration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

| Extended main function to accept optional arguments :code:`-s SOLVER` and :code:`-u SETUP`.
| :code:`SOLVER = ROE or FWAVE`
| :code:`SETUP = 'DAMBREAK1D h_l h_r', 'RARERARE1D h hu' or 'SHOCKSHOCK1D h hu'`
| defaults are :code:`FWave` and :code:`'DamBreak1d 10 5'` respectively

.. code:: c++

    // get command line arguments
  opterr = 0; // disable error messages of getopt
  int opt;

  // defaults
  bool l_useFwave = true;
  tsunami_lab::setups::Setup *l_setup;
  l_setup = new tsunami_lab::setups::DamBreak1d(10,
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
      else
      {
        std::cout << "using FWave solver" << std::endl;
        l_useFwave = true;
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
      double l_arg1 = std::stod(l_arg1Str);
      double l_arg2 = std::stod(l_arg2Str);
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

    // stuff happens

    l_waveProp = new tsunami_lab::patches::WavePropagation1d(l_nx, l_useFwave);

and adjust WavePropagation1d constructor to accept a boolean for the solver type.

.. code:: c++

    tsunami_lab::patches::WavePropagation1d::WavePropagation1d(t_idx i_nCells, bool i_useFWave)
    {
    m_useFWave = i_useFWave;

    // stuff happens

    void tsunami_lab::patches::WavePropagation1d::timeStep(t_real i_scaling){

    // stuff happens

    if (m_useFWave)
    {
      solvers::FWave::netUpdates(l_hOld[l_ceL],
                                 l_hOld[l_ceR],
                                 l_huOld[l_ceL],
                                 l_huOld[l_ceR],
                                 l_netUpdates[0],
                                 l_netUpdates[1]);
    }
    else
    {
      solvers::Roe::netUpdates(l_hOld[l_ceL],
                               l_hOld[l_ceR],
                               l_huOld[l_ceL],
                               l_huOld[l_ceR],
                               l_netUpdates[0],
                               l_netUpdates[1]);
    }

2.0.2 middle_states.csv as sanity check
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Added new testcases for the setups with the values of middle_states.csv for example:

.. code:: c++

  TEST_CASE("Test the 1d wave propagation FWave solver shock-shock.", "[WaveProp1dFWaveShockShock]")
  {
  /**
   * @brief test steady state from middle_states.csv in the Shock-Shock Problem
   * (Riemann Solutions obtained by Alexander Breuer)
   *
   * h_l = 9894.065328676988
   * h_r = 9894.065328676988
   * hu_l = 763.616897222239
   * hu_r = -763.616897222239
   * h* = 9896.516538751875
   */

  // construct solver and setup a shock-shock problem
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, true);

  for (std::size_t l_ce = 0; l_ce < 50; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         9894.065328676988);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            763.616897222239);
  }
  for (std::size_t l_ce = 50; l_ce < 100; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         9894.065328676988);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            -763.616897222239);
  }

  // set outflow boundary condition
  m_waveProp.setGhostOutflow();

  // perform a time step
  for (int i = 0; i < 30; i++)
  {
    m_waveProp.timeStep(0.001);
  }

  // test for h*
  REQUIRE(m_waveProp.getHeight()[49] == Approx(9896.516538751875));
  REQUIRE(m_waveProp.getHeight()[50] == Approx(9896.516538751875));
  }

2.0.3 Continous Integration
^^^^^^^^^^^^^^^^^^^^^^^^^^^

We Activated Github Actions to run the tests on every push and pull request (literally just activated it, no changes to the yaml were made).
We also integrated Doxygen into our Sphinx Documentation and pushing it automatically to ReadTheDocs. 

2.1 Shock and Rarefaction Waves
-------------------------------

2.1.1 shock-shock and rare-rare setups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Implemented shock-shock and rare-rare Problems in /setups.
They are mainly the same as the Dam Break setup, but with the same waterheight and opposite momenta on both sides.

.. code:: c++

  tsunami_lab::t_real tsunami_lab::setups::ShockShock1d::getMomentumX(t_real i_x,
                                                                      t_real) const
  {
    if (i_x < m_middlePoint)
    {
      return m_momentum;
    }
    else
    {
      return -m_momentum;
    }
  } 

2.1.2 influence of parameters on shock-shock and rare-rare setups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Observations:

The higher the momenta the higher the middlestate height is. But it doesn't affect the wavespeeds whatsoever.
The higher the initial heights are, the higher the middlestate is and the faster the wavespeeds are.

.. video:: _static/2_ShockShock1d_10_50.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Shock-Shock problem with h=10 and u=5

.. video:: _static/2_ShockShock1d_10_100.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Shock-Shock problem with h=10 and u=10

.. video:: _static/2_ShockShock1d_40_200.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Shock-Shock problem with h=40 and u=5

.. video:: _static/2_RareRare1d_10_25.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Rare-Rare problem with h=10 and u=2.5

.. video:: _static/2_RareRare1d_10_50.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Rare-Rare problem with h=10 and u=5

.. video:: _static/2_RareRare1d_40_200.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Rare-Rare problem with h=40 and u=5

So we see the waves move twice as fast in the setup with quadruple the height and are unaffected by initial momentum.
This matches our expectation derived from the math below of the Wavespeeds being proportional to the square root of the height and independent of the initial momentum.

.. math::
  h_r &= h_l \\
  hu_r &= -hu_l \\
  u_r &= -u_l \\
  h &= \frac{1}{2}(h_l+h_r) = h_l = h_r \\
  u &= \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l}+\sqrt{h_r}} = \frac{u_l \sqrt{h} - u_l \sqrt{h}}{2\sqrt{h}} = 0 \\
  \lambda_{1,2} &= \mp \sqrt{gh}

2.2 Dam-Break
-------------

2.2.1 influence of parameters on dam-break setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Observations:

The higher the initial height difference is, the larger is the momentum in the middle state.
The wavespeed of the shock wave is seemingly unaffected by the right height while the rarefaction wave seems slower the larger the initial height difference is.
The wavespeed of the shock wave seems to be proportional to the square root of the left height.
The wavespeed of the shockwave does get faster the higher the initial momentum on the right side is, but it seems to be an overall minor impact.

.. video:: _static/3_2_DamBreak1d_10_2.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam-Break problem with h_l=10 and h_r=2 and hu = 0

.. video:: _static/2_DamBreak1d_10_6.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam-Break problem with h_l=10 and h_r=6 and hu = 0

.. video:: _static/2_DamBreak1d_40_8.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam-Break problem with h_l=40 and h_r=8 and hu = 0

.. video:: _static/2_DamBreak1d_40_32.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam-Break problem with h_l=40 and h_r=32 and hu = 0

.. video:: _static/2_DamBreak1d_14_3.5_0_0.7.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:


Dam-Break problem with h_l=14 and h_r=3.5 and hu_l = 0 and hu_r = 0.7

.. video:: _static/2_DamBreak1d_14_3.5_0_4.mp4
  :width: 700
  :autoplay:
  :loop:
  :nocontrols:
  :muted:

Dam-Break problem with h_l=14 and h_r=3.5 and hu_l = 0 and hu_r = 4

2.2.2 Village Evacuation Time
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

First we try to approximate the shock wavespeed with the simulation as sanity check for the calculation later.
In solution_40 of in total 0-117 solution csv's the shock wave reaches 9.75m which means it moved 4.75m.
The total simulation takes 1.25s which means solution_40 is roughly at :math:`t = \frac{41}{118} \cdot 1.25s = 0.43s`.
That makes the speed roughly :math:`v_{shock wave} = \frac{4.75m}{0.43s} = 11.05 \frac{m}{s} = 39.77 \frac{km}{h}`.
And it should arrive at the village after :math:`t_{evacuation} = \frac{25km}{39.77 \frac{km}{h}} = 0.628 h \approx 38 min`.

Now we calculate it theoretically and compare results:

.. math::

  s_{village} &= 25km \\
  q_l &= \begin{bmatrix} 14 \\ 0 \end{bmatrix}\\
  q_r &= \begin{bmatrix} 3.5 \\ 0.7 \end{bmatrix}\\
  u_r &= \frac{hu_r}{h_r} = \frac{0.7}{3.5} = 0.2 \frac{m}{s}\\
  h^{Roe} &= \frac{1}{2} (h_l + h_r) = \frac{1}{2} (14 + 3.5) = 8.75 m \\
  u^{Roe} &= \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l}+\sqrt{h_r}} = \frac{0 \cdot \sqrt{14} + 0.2 \cdot \sqrt{3.5}}{\sqrt{14}+\sqrt{3.5}} = 0.06667 \frac{m}{s}\\
  \lambda_r^{Roe} &= u^{Roe} + \sqrt{gh^{Roe}} = 0.06667 + \sqrt{9.80665 \cdot 8.75} = 9.32994 \frac{m}{s} = 33.587784 \frac{km}{h} \\	
  t_{evacuation} &= \frac{s_{village}}{\lambda_r^{Roe}} = \frac{25}{33.587784} = 0.744 h = 44.64 min

The calculated time is a bit higher than the simulation suggests, but still in the same order of magnitude, so it seems the Roe Eigenvalues are a pretty decent approximation.