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

.. literalinclude:: ../../../src/patches/WavePropagation1d.h
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

Implemntation of Shock-Shock setups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. RareRare1d: This is the constructor of the RareRare1d class, initializing the key parameters for the rare-rare problem, such as the initial height (i_h), initial x-momentum (i_hu), and the location of a discontinuity (i_dis).

#. getHeight: This function is used to retrieve the height value at a specific location (i_x, i_y). In this 1D problem, the height value is constant and equal to m_h.

#. getMomentumX: This function provides the x-momentum value at a specific location (i_x, i_y). The value depends on the location relative to the discontinuity (m_dis). If i_x is less than or equal to m_dis, the x-momentum is set to -m_hu, and otherwise, it is m_hu.

#. getMomentumY: This function is used to retrieve the y-momentum value at a specific location (i_x, i_y). In this specific problem, the y-momentum is always constant and equal to 0.

.. literalinclude:: ../../../src/setups/RareRare1d.cpp
    :language: c++

In this one-dimensional rare-rare problem represented by the RareRare1d class, the behavior of the wave is described by the distribution of momentum. Specifically, on the left side of the discontinuity point (m_dis), the x-momentum is positive, indicating that the wave is moving to the right. Conversely, on the right side of the discontinuity, the x-momentum is negative, signifying that the wave is moving to the left. These opposing momenta result in the two wave components colliding at the "smash position," which is the location of the discontinuity. 

Implemntation of rare-rare setups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. RareRare1d: This is the constructor of the RareRare1d class, initializing the key parameters for the rare-rare problem, such as the initial height (i_h), initial x-momentum (i_hu), and the location of a discontinuity (i_dis).

#. getHeight: This function is used to retrieve the height value at a specific location (i_x, i_y). In this 1D problem, the height value is constant and equal to m_h.

#. getMomentumX: This function provides the x-momentum value at a specific location (i_x, i_y). The value depends on the location relative to the discontinuity (m_dis). If i_x is less than or equal to m_dis, the x-momentum is set to -m_hu, and otherwise, it is m_hu.

#. getMomentumY: This function is used to retrieve the y-momentum value at a specific location (i_x, i_y). In this specific problem, the y-momentum is always constant and equal to 0.


.. literalinclude:: ../../../src/setups/ShockShock1d.cpp
    :language: c++

In the rare-rare problem represented by the RareRare1d class, the wave behavior is distinct from the previous example. Here, the wave components are moving apart from each other on either side of the discontinuity point (m_dis). On the left side, the x-momentum is positive, indicating that the wave is traveling to the right, while on the right side, the x-momentum is also positive, signifying a rightward motion. This results in the wave components moving away from the m_dis point, rather than colliding. 

Connection between h_l and u_l
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. math::
   :label: eq:shockcond

   q_l=
           \begin{bmatrix}
             h_l \\ (hu)_l
           \end{bmatrix}, \quad
         q_r =
           \begin{bmatrix}
             h_r \\ (hu)_r
           \end{bmatrix} =
           \begin{bmatrix}
             h_l \\ -(hu)_l
           \end{bmatrix}.

At first we have to calculate u.

.. math::
  :label: eq: particle velocity
  
  u^{\text{Roe}}(q_l, q_r) &=  \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l}+\sqrt{h_r}}

We know that 
.. math::

  h_r = h_r
  u_l = - u_r

So we can calculate u_l

.. math::

  \frac{u_l \sqrt{h} + (-u_l) \sqrt{h}}{2 \sqrt{h}}
  = \frac{ \sqrt{h} (u_l - u_l)}{ 2 \sqrt{h}}
  = \frac{0}{2 sqrt{h}}
  = 0

So the speeds

.. math::

  \lambda_{1,2}=u \pm \sqrt{g h}

only depend on the hight and the gravitational constant

.. math::

  \lambda_{1,2}= \pm \sqrt{g h}


.. _ch:Dam-Break:
Dam-Break
---------

.. admonition:: Tasks

  #. Apply your solver to the dam-break setup and play around with different sets of initial water heights :math:`h_l` and :math:`h_r`.
     What do you observe? How large is the impact of the particle velocity :math:`u_r` in the river?
  #. Assume a water reservoir of unlimited size and a village 25 km downstream with initial values :math:`q_l=[14, 0]^T` and :math:`q_r=[3.5, 0.7]^T`.
     How much time do you have to evacuate the village in our model before the shock wave arrives?