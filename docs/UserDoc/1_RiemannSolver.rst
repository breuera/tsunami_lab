Tsunami Report 1 Riemann Solver
===============================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: Wrote Code and Unit Test

Thorsten Kröhl: Assisted Code and hosted User documentation

Julius Halank: Assisted Code and wrote Project Report

1.2 Riemann-Solver
------------------

Created the doxygen Documentation with :code:`doxygen Doxyfile`

.. image:: _static/1_doxygen.png
  :width: 700

Initial Unittests are successful and the results are visualized as:

.. video:: _static/1_height.mp4
   :width: 700

Height over Time after Dambreak

.. video:: _static/1_momentum.mp4
   :width: 700

Momentum over Time after Dambreak

added new Catch2 Tests for example:

.. code-block:: c++

   /**
   * Test case supersonic problem
   *
   *      left | right
   *  h:   1   | 1
   *  u:   100 | 10
   *  hu:  100 | 10
   *
   *  FWave speeds are given as:
   *
   *  s1 = 55 - sqrt(9.80665 * 1) = 51.868443
   *  s2 = 55 + sqrt(9.80665 * 1) = 58.131557
   *
   *  * Inversion of the matrix of right Eigenvectors:
   *
   *   wolframalpha.com query: invert {{1, 1}, {55 - sqrt(9.80665 * 1), 55 + sqrt(9.80665 * 1)}}
   *
   *          | 9.28157  -0.159665  |
   *   Rinv = |                     |
   *          | -8.28157  0.159665  |
   *
   * Multiplicaton with the jump in quantities gives the wave strengths:
   *
   *        |   0 -  0 |   |  14.3699 |   | a1 |
   * Rinv * |          | = |          | = |    |
   *        |  10 - 100|   | -14.3699 |   | a2 |
   *
   * The net-updates are given through the scaled eigenvectors added for #2 and 0 for #1 because both are greater than 0:
   *
   * update #1:     0
   *
   *                      |  1 |        |  1 |    | 0              |
   * update #2:      a2 * |    | + a1 * |    |  = |                |
   *                      | s2 |        | s1 |    | -90.0006609343 |
   */

  tsunami_lab::solvers::FWave::netUpdates(1,
                                          1,
                                          100,
                                          10,
                                          l_netUpdatesL,
                                          l_netUpdatesR);

  REQUIRE(l_netUpdatesL[0] == Approx(0));
  REQUIRE(l_netUpdatesL[1] == Approx(0));

  REQUIRE(l_netUpdatesR[0] == Approx(0));
  REQUIRE(l_netUpdatesR[1] == -Approx(90.0006609343));

1.3 Riemann-Solver
------------------

the Riemann-Solver is similar to the roe Solver (same results in tests for Dambreak), but:

* instead of a jump in quantities a jump in fluxes gets input
* the netupdates don't get multiplied by `l_sL` / `l_sR` respectively
* the wave updates get added together instead of overriding each other (see supersonic case)

.. code-block:: c++

    void tsunami_lab::solvers::FWave::flux(t_real i_h,
                                       t_real i_hu,
                                       t_real &o_flux0,
                                       t_real &o_flux1)
    {
        // f(q) = [hu, h*u^2 + 1/2*g*h^2]
        o_flux0 = i_hu;
        o_flux1 = i_hu * i_hu / i_h + 0.5f * m_g * i_h * i_h;
    }


.. code-block:: c++

       // compute waves
    t_real l_waveL[2] = {0};
    t_real l_waveR[2] = {0};

    l_waveL[0] = l_aL;
    l_waveL[1] = l_aL * l_sL;

    l_waveR[0] = l_aR;
    l_waveR[1] = l_aR * l_sR;

    // set net-updates depending on wave speeds
    for (unsigned short l_qt = 0; l_qt < 2; l_qt++)
    {
        // init
        o_netUpdateL[l_qt] = 0;
        o_netUpdateR[l_qt] = 0;

        // 1st wave
        if (l_sL < 0)
        {
            o_netUpdateL[l_qt] += l_waveL[l_qt];
        }
        else
        {
            o_netUpdateR[l_qt] += l_waveL[l_qt];
        }

        // 2nd wave
        if (l_sR > 0)
        {
            o_netUpdateR[l_qt] += l_waveR[l_qt];
        }
        else
        {
            o_netUpdateL[l_qt] += l_waveR[l_qt];
        }