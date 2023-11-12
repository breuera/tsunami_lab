.. _ch:Task_3_phillip:

Report Phillip
##############

Adding bathymetry support
*************************

.. admonition:: Tasks

    #. Extend the f-wave solver with support for bathymetry according to Eq. 3.1.1 and Eq. 3.1.2.

    #. Implement an example which illustrates the effect of bathymetry in your extended solver. 
       **Note:** You have to add bathymetry to the respective patches implementing the abstract class ``patches::WavePropagation`` as well. 
       Also, ghost cells require a valid value for the bathymetry, i.e., :math:`b_0 := b_1` set and :math:`b_{n+1} := b_n`.

Implementation in F-Wave solver
===============================

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
===================================

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

Hydraulic Jumps
***************

.. admonition:: Tasks

    #. Compute the location and value of the maximum Froude number for the subcritical setting given in Eq. 3.3.1 and the supercritical setting given in Eq. 3.3.2 at the initial time :math:`t = 0`.

    #. Implement both cases through the base class ``setup::Setup.h``. :math:`t \in [0, 200]` is a reasonable time window for your simulation.

    #. Determine the position of the hydraulic jump (stationary discontinuity) in your supercritical solution and show that our f-wave solver fails to converge to the analytically expected constant momentum over the entire domain.

Maximum Froude value
====================

First we look upon the equation to calculate the Froude number:

.. math::

    F = \frac{(\frac{hu}{h})}{\sqrt{g \cdot h}} = \frac{hu}{h} \cdot \frac{1}{\sqrt{g \cdot h}} = \frac{hu}{\sqrt{g} \cdot \sqrt{h}^3}

Since for both cases :math:`hu` and :math:`g` are constant we only need to look at the height. :math:`F` will be the highest, when :math:`h` is the lowest.

Subcritical Flow:
^^^^^^^^^^^^^^^^^

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
=======================

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
========================

The stationary discontinuity is located in the 115 cell or in at 11.5 meters. 
At the end all cells have a momentum around 0.12, but the 115-th cell has a 
momentum of 0.14. This makes shows, that the momentum does not converge to a constant. 