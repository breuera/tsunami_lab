.. _ch:Task_4:

Week Report 4
=============

.. _ch:Task_4_1:

Adding two-dimensional support
------------------------------

.. admonition:: Tasks

    #. Add support for two-dimensional problems to the solver. Implement dimensional splitting through a new class ``patches::WavePropagation2d``. Change other parts of the software as required but keep supporting one-dimensional settings.

    #. Implement a circular dam break setup in the computational domain :math:`[-50,50]^2` by using the following initial values:

    .. math::
    
        \begin{cases}
            [h, hu, hv]^T = [10, 0, 0]^T & \text{ if } \sqrt{x^2 + y^2} < 10 \\
            [h, hu, hv]^T = [5, 0, 0]^T &\text{else}.
        \end{cases}
    
    #. Illustrate your support for bathymetry in two dimensions by adding an obstacle to the computational domain of the circular dam break setup.

Implementation of dimensional splitting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To implement the dimensional splitting I needed to write the class ``patches::WavePropagation2d``. It has an additional member variable that holds 
an array containing the momentum in y-direction. Each array is the size of 
:math:`(n+2)\cdot (m+2)` elements with :math:`n` being the number of cells in x-direction
and :math:`m` the number of cells in y-direction.

The timestep needs to first do the x-sweep and then do the y-sweep. In the x-sweep
the momentum in x-direction is fed into the solver, while in the y-sweep the momentum in y-direction is used.

.. code-block::

    void tsunami_lab::patches::WavePropagation2d::timeStep(t_real i_scalingX,
                                                           t_real i_scalingY) {
        t_real *l_hOld = m_h[m_step];
        t_real *l_huOld = m_hu[m_step];
        t_real *l_hvOld = m_hv[m_step];

        m_step = (m_step + 1) % 2;
        t_real *l_hNew = m_h[m_step];
        t_real *l_huNew = m_hu[m_step];
        t_real *l_hvNew = m_hv[m_step];

        t_real *l_hStar = new t_real[m_mnCells];
        t_real *l_huStar = new t_real[m_mnCells];
        t_real *l_hvStar = new t_real[m_mnCells];

        for (t_idx l_ceY = 0; l_ceY < m_mCellsY + 2; l_ceY++) {
            for (t_idx l_ceX = 0; l_ceX < m_nCellsX + 2; l_ceX++) {
                t_idx l_idx = getIndex(l_ceX, l_ceY);
                l_hStar[l_idx] = l_hOld[l_idx];
                l_huStar[l_idx] = l_huOld[l_idx];
                l_hvStar[l_idx] = l_hvOld[l_idx];
            }
        }

        for (t_idx l_edY = 0; l_edY < m_mCellsY + 2; l_edY++) {
            for (t_idx l_edX = 0; l_edX < m_nCellsX + 1; l_edX++) {
                t_idx l_ceL = getIndex(l_edX, l_edY);
                t_idx l_ceR = getIndex(l_edX + 1, l_edY);

                t_real l_netUpdates[2][2];

                solvers::FWave::netUpdates(l_hOld[l_ceL],
                                        l_hOld[l_ceR],
                                        l_huOld[l_ceL],
                                        l_huOld[l_ceR],
                                        m_b[l_ceL],
                                        m_b[l_ceR],
                                        l_netUpdates[0],
                                        l_netUpdates[1]);

                l_hStar[l_ceL] -= i_scalingX * l_netUpdates[0][0];
                l_huStar[l_ceL] -= i_scalingX * l_netUpdates[0][1];

                l_hStar[l_ceR] -= i_scalingX * l_netUpdates[1][0];
                l_huStar[l_ceR] -= i_scalingX * l_netUpdates[1][1];
            }
        }

        for (t_idx l_ceY = 1; l_ceY < m_mCellsY + 1; l_ceY++) {
            for (t_idx l_ceX = 1; l_ceX < m_nCellsX + 1; l_ceX++) {
                t_idx l_idx = getIndex(l_ceX, l_ceY);
                l_hNew[l_idx] = l_hStar[l_idx];
                l_huNew[l_idx] = l_huStar[l_idx];
                l_hvNew[l_idx] = l_hvStar[l_idx];
            }
        }

        for (t_idx l_edX = 1; l_edX < m_nCellsX + 1; l_edX++) {
            for (t_idx l_edY = 0; l_edY < m_mCellsY + 1; l_edY++) {
                t_idx l_ceU = getIndex(l_edX, l_edY);
                t_idx l_ceD = getIndex(l_edX, l_edY + 1);

                t_real l_netUpdates[2][2];

                solvers::FWave::netUpdates(l_hStar[l_ceU],
                                        l_hStar[l_ceD],
                                        l_hvStar[l_ceU],
                                        l_hvStar[l_ceD],
                                        m_b[l_ceU],
                                        m_b[l_ceD],
                                        l_netUpdates[0],
                                        l_netUpdates[1]);

                l_hNew[l_ceU] -= i_scalingY * l_netUpdates[0][0];
                l_hvNew[l_ceU] -= i_scalingY * l_netUpdates[0][1];

                l_hNew[l_ceD] -= i_scalingY * l_netUpdates[1][0];
                l_hvNew[l_ceD] -= i_scalingY * l_netUpdates[1][1];
            }
        }

        delete[] l_hStar;
        delete[] l_huStar;
        delete[] l_hvStar;
    }   

Additionally I needed to calculate the sizes of the time step and the cells. For 
the former the CFL-criterion needs to be true.

.. code-block::

    ...

    // check if delta x is smaller than delta y
    bool l_isXStepSmaller = (l_dx <= l_dy);

    // choose l_dxy as l_dx if it is smaller or l_dy if it is smaller
    tsunami_lab::t_real l_dxy = l_dx * l_isXStepSmaller + l_dy * !l_isXStepSmaller;

    std::cout << "runtime configuration" << std::endl;
    std::cout << "  number of cells in x-direction: " << l_nx << std::endl;
    std::cout << "  number of cells in y-direction: " << l_ny << std::endl;
    std::cout << "  cell size:                      " << l_dxy << std::endl;

    // derive constant time step; changes at simulation time are ignored
    tsunami_lab::t_real l_dt = 0.5 * l_dxy / l_speedMax;

    // derive scaling for a time step
    tsunami_lab::t_real l_scalingX = l_dt / l_dx;
    tsunami_lab::t_real l_scalingY = l_dt / l_dy;

    ...

Implementation of 2D dam break setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Only the ``setups::DamBreak2d::getHeight`` need to be shown since the rest 
ar returning 0 for each position.

.. code-block::

    tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getHeight(t_real i_x,
                                                                   t_real i_y) const {
        t_real l_x = i_x - (m_simLenX / 2);
        t_real l_y = i_y - (m_simLenY / 2);
        if (sqrt(pow(l_x, 2) + pow(l_y, 2)) < m_damLimit) {
            return 10 + fabs(getBathymetry(i_x, i_y));
        } else {
            return 5 + fabs(getBathymetry(i_x, i_y));
        }
    }

The resulting simulation:

.. figure:: ../_static/video_folder/assignment_4/dambreak_2d.mp4
  :width: 600px

Adding an obstacle 
^^^^^^^^^^^^^^^^^^

Finally for adding an obstacle. The method ``setups::DamBreak2d::getBathymetry`` was edited.

.. code-block::

    tsunami_lab::t_real tsunami_lab::setups::DamBreak2d::getBathymetry(t_real i_x,
                                                                       t_real i_y) const {
        bool l_inRangeX = 0.3 * m_simLenX < i_x && 0.4 * m_simLenX > i_x;
        bool l_inRangeY = 0.3 * m_simLenY < i_y && 0.4 * m_simLenY > i_y;

        if (l_inRangeX && l_inRangeY) {
            return -2;
        } else {
            return -10;
        }
    }

The influence of this can be seen in the resulting animation.

.. figure:: ../_static/video_folder/assignment_4/dambreak_2d_obs.mp4
  :width: 600px
