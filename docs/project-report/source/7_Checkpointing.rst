7 Checkpointing
===============

Links:
------------

`Github Repo <https://github.com/MherMnatsakanyan03/tsunami_lab.git>`_


Individual Contributions:
-------------------------

Mher Mnatsakanyan and Maurice Herold did a similar amount of work.

Task 7.1: Checkpointing
-----------------------

7.1.1 Extension
^^^^^^^^^^^^^^^

We wrote a function that writes all nessecary parameters for our simulation into a new .nc file:

.. code:: c++

    void tsunami_lab::io::NetCdf::writeCheckpoint(t_idx i_nx,
                                                 t_idx i_ny,
                                                 t_real const *i_h,
                                                 t_real const *i_hu,
                                                 t_real const *i_hv,
                                                 t_real const *i_b,
                                                 t_real i_x_offset,
                                                 t_real i_y_offset,
                                                 int i_solver_choice,
                                                 int i_state_boundary_left,
                                                 int i_state_boundary_right,
                                                 int i_state_boundary_top,
                                                 int i_state_boundary_bottom,
                                                 t_real i_width,
                                                 t_real i_endTime,
                                                 t_idx i_timeStep,
                                                 t_real i_time,
                                                 t_idx i_nOut,
                                                 t_real i_hMax,
                                                 t_idx i_simulated_frame,
                                                 std::string i_filename)

Similarly, we wrote a read-function that reads a given checkpoint-file:

.. code:: c++

    void tsunami_lab::io::NetCdf::readCheckpoint(t_idx *o_nx,
                                                 t_idx *o_ny,
                                                 t_real **o_h,
                                                 t_real **o_hu,
                                                 t_real **o_hv,
                                                 t_real **o_b,
                                                 t_real *o_x_offset,
                                                 t_real *o_y_offset,
                                                 int *o_solver_choice,
                                                 int *o_state_boundary_left,
                                                 int *o_state_boundary_right,
                                                 int *o_state_boundary_top,
                                                 int *o_state_boundary_bottom,
                                                 t_real *o_width,
                                                 t_real *o_endTime,
                                                 t_idx *o_timeStep,
                                                 t_real *o_time,
                                                 t_idx *o_nOut,
                                                 t_real *o_hMax,
                                                 t_idx *o_simulated_frame,
                                                 std::string *o_filename,
                                                 const std::string filename)


7.1.2 Setup
^^^^^^^^^^^

We were not sure what the setup was supposed to do, so our guess was, that when using
different setups, we also wrote checkpoints and when using the `checkpoint`-setup
it loads the last checkpoint that was saved.

We implemented a get-function for each parameter that we are saving, i.e.:

.. code:: c++

    int tsunami_lab::setups::Checkpoint::getStateBoundaryLeft() const
    {
        return m_state_boundary_left;
    }


7.1.3 Test
^^^^^^^^^^

The test were somewhat sobering. While developping we were able to make the checkpoints write everything correctly,
including the bathymetry. The exceptions are the waterheight and both of the momenta. Which is unfortunate considering
these are the main data for the simulation.

When loading a checkpoint, the simulated time and frames in the console
are shown correctly and in paraview, the bathymetry looks alright. The issue
is, that the said values not written correctly are for whatever reason constant,
shown in paraview as one constant color.

We were not able to find the solution this week but we hope to find the problem in the near future.

7.1.4 Extension 2
^^^^^^^^^^^^^^^^^

Considering the usage of the :code:`setup::Checkpoint` this task left us somewhat confused, which is why the
checkpointing is still done via calling the setup, meaning that the same command in the commando-line will
start a new simulation which will by itself write new checkpoints, overwriting the old one.


Task 7.2: Coarse Output
-----------------------

7.2.1 Coarsing
^^^^^^^^^^^^^^

For this task we wrote a private help-function which scales down an input-array by a given integer `i_resolution_div`
and calculates the average number inbetween the downscaling to get an acurate representation of the original array
on a smaller size.

.. code:: c++

    tsunami_lab::t_real *tsunami_lab::io::NetCdf::scaleDownArray(t_real const *i_array,
                                                                 t_idx i_nx,
                                                                 t_idx i_ny,
                                                                 int i_resolution_div)
    {
        t_idx new_nx = i_nx / i_resolution_div; 
        t_idx new_ny = i_ny / i_resolution_div; 
        t_real *new_array = new t_real[new_nx * new_ny];    
        
        for (t_idx j = 0; j < new_ny; ++j)
        {
            for (t_idx i = 0; i < new_nx; ++i)
            {
                t_real sum = 0;
                for (t_idx y = j * i_resolution_div; y < (j + 1) * i_resolution_div; ++y)
                {
                    for (t_idx x = i * i_resolution_div; x < (i + 1) * i_resolution_div; ++x)
                    {
                        sum += i_array[y * i_nx + x];
                    }
                }
                new_array[j * new_nx + i] = sum / (i_resolution_div * i_resolution_div);
            }
        }

        return new_array;
    }


|pic1| |pic2|

.. |pic1| image:: _static/content/images/week7/original_1.png
   :width: 45%

.. |pic2| image:: _static/content/images/week7/downscaled_1.png
   :width: 45%

|pic3| |pic4|

.. |pic3| image:: _static/content/images/week7/original_2.png
   :width: 45%

.. |pic4| image:: _static/content/images/week7/downscaled_2.png
   :width: 45%

The pictures represent an artificial Tsunami-setup with the original scaling (:math:`k=1`)
and a downscaled version (:math:`k=10`). The difference in file-size is 100x.

7.2.2 Simulation
^^^^^^^^^^^^^^^^

We admit that we completely lost sight of this task and forgot to run the simulation.
Considering the assignments last week the simulation would run normal. We open and close
the file at every writing operation which saves the file, making a simulation possible
even after a crash. The only thing not working yet is the actuall checkpointing.