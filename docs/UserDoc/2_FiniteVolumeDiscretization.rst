Tsunami Report 2 Finite Volume Discretization
=============================================

Links:
------

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions:
-------------------------

Justus Dreßler: Wrote Projekt Report and implemented extra command line argument

Thorsten Kröhl: Implemented Doxygen Integration in Sphinx

Julius Halank: Added Test Cases for Setups

2.0 Integrate FWave Solver
--------------------------

extended main function to accept a second argument for the solver type optionally

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

and adjust WavePropagation1d constructor to accept a bool for the solver type

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

.. 
  TODO MiddleStates.csv

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

..
  TODO Time to Evacuate (guess roughly 42 minutes)