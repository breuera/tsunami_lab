.. _ch:Task_1_1:

Report Week 2
=============

.. _ch:Contribution:
Contribution
------------

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



.. literalinclude:: ../../../src/patches/WavePropagation1d.cpp
    :language: c++

.. literalinclude:: ../../../src/main.cpp
    :language: c++

.. literalinclude:: ../../../src/setups/CustomSetup1d.cpp
    :language: c++

.. literalinclude:: ../../../src/patches/WavePropagation1d.hidden
    :language: c++

.. literalinclude:: ../../../src/io/Csv.cpp
    :language: c++

.. _ch:Shock_and_Rarefaction_Waves:
Shock and Rarefaction Waves 
---------------------------

.. admonition:: Tasks

    #. Implement the shock-shock and rare-rare problems as setups.
    #. Play
       around with different sets of initial water heights :math:`h_l` and
       particles velocities :math:`u_l`. What do you observe? Is there a
       connection to the wave speeds :math:`\lambda_{1/2} = u \mp \sqrt{gh}`
       in :numref:`ch:fwave`?

.. literalinclude:: ../../../src/setups/RareRare1d.cpp
    :language: c++
    
.. literalinclude:: ../../../src/setups/ShockShock1d.cpp
    :language: c++

.. _ch:Dam-Break:
Dam-Break
---------

.. admonition:: Tasks

  #. Apply your solver to the dam-break setup and play around with different sets of initial water heights :math:`h_l` and :math:`h_r`.
     What do you observe? How large is the impact of the particle velocity :math:`u_r` in the river?
  #. Assume a water reservoir of unlimited size and a village 25 km downstream with initial values :math:`q_l=[14, 0]^T` and :math:`q_r=[3.5, 0.7]^T`.
     How much time do you have to evacuate the village in our model before the shock wave arrives?