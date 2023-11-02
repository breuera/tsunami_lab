Tsunami Report 2 Finite Volume Discretization
=============================================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: Wrote Projekt Report and implemented extra command line argument

Thorsten Kröhl: Implemented Doxygen Integration in Sphinx

Julius Halank: Added Test Cases for Setups

2.0 Integrate FWave Solver
--------------------------

Extended main function to accept a second argument for the solver type optionally

.. code:: c++

    // bool if using FWave Solver
    bool l_useFwave = true;

    // stuff happens

    if (i_argc == 2)
    {
      std::cout << "using FWave solver" << std::endl;
      l_useFwave = true;
    }
    else
    {
      std::string l_arg(i_argv[2]);
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
    }

    // stuff happens

    l_waveProp = new tsunami_lab::patches::WavePropagation1d(l_nx, l_useFwave);

and adjust WavePropagation1d constructor to accept a bool for the solver type.

.. code:: c++

    tsunami_lab::patches::WavePropagation1d::WavePropagation1d(t_idx i_nCells, bool i_useFWave)
    {
      m_nCells = i_nCells;

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

Added new Testcases for the Setups with the values of middle_states.csv for Example:

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

We Activated Github Actions to run the tests on every push and pull request (literally just activated it, no changes to the yaml were made).
We also integrated Doxygen into our ReadTheDocs Documentation.

2.1 Shock and Rarefaction Waves
-------------------------------

Implemented shock-shock and rare-rare Problems in /setups.
They are mainly the same as the Dam Break setup, but with the same waterheight on both sides but different momentums.

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

Regarding the Wavespeeds:

We know that :math:`h_r = h_l` and :math:`hu_r = -hu_l` so :math:`u_r = -u_l` and :math:`h = \frac{1}{2}(h_l+h_r) = h_l = h_r`  and
:math:`u = \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l}+\sqrt{h_r}} = \frac{u_l \sqrt{h} - u_l \sqrt{h}}{2\sqrt{h}} = 0` follow

which means the lambdas are :math:`\lambda_{1,2} = \mp \sqrt{gh}` only dependent on the height of the water column.

2.2 Dam-Break
-------------

..
  TODO Impact of Waterheights and Particle Velocity in the river

Village Evacuation Time:

.. math::

  s_{village} &= 25km \\
  q_l &= \begin{bmatrix} 14 \\ 0 \end{bmatrix}\\
  q_r &= \begin{bmatrix} 3.5 \\ 0.7 \end{bmatrix}\\
  h^{Roe} &= \frac{1}{2} (h_l + h_r) = \frac{1}{2} (14 + 3.5) = 8.75 m \\
  u^{Roe} &= \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l}+\sqrt{h_r}} = \frac{0 \cdot \sqrt{14} + 0.7 \cdot \sqrt{3.5}}{\sqrt{14}+\sqrt{3.5}} = 0.23333 \frac{m}{s}\\
  \lambda_r^{Roe} &= u^{Roe} + \sqrt{gh^{Roe}} = 0.23333 + \sqrt{9.80665 \cdot 8.75} = 9.49660 \frac{m}{s} = 34.18776 \frac{km}{h} \\	
  t_{evacuation} &= \frac{s_{village}}{\lambda_r^{Roe}} = \frac{25}{34.18776} = 0.731 h = 43.86 min