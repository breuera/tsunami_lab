# 4 Two Dimensional solver

## Links:

`Github Repo <https://github.com/MherMnatsakanyan03/tsunami_lab.git>`\_

## Individual Contributions:

Mher Mnatsakanyan and Maurice Herold did a similar amount of work.

## Task 4.1:

4.1.1 2D support
^^^^^^^^^^^^^^^^
We started by trying to implement a solution using 2d-arrays in c++ ie. :code:`t_real **m_b`.
This soon showed to be rather difficult because a lot of implementation thus far
were based on one-dimensional arrays, for instance the :code:`WavePropagation.h` needed
to be rewritten and :code:`Csv.cpp` would also require a complete overhaul.

There is an easier way, which is to flatten the 2d-grid onto a 1d-array. This just
requires a way to map x-y coordinates to a numeric value. Luckly this is easy because
we just need to jump for every y-coordinate one x-axis amout in the array. We achieved
this by writing a helper-function that does the calculation for us:

.. code:: c++

    t_idx getCoordinates(t_idx i_x, t_idx i_y)
    {
        // when trying to move on a flattend 2d plane, for each y-coordinate
        // we need to "jump" one x-axis worth of a distance in the 1d-array
        return i_x + i_y * getStride();
    };

This way we could also guarantee the compatibility of our code with 1d-setups.

Now, you have to use the :code:`DIMENSION` and :code:`SETUP` options, because
setting default values is hard, considering that there is the possibility of
mismatching dimension and setup.

Another change that had to be done was the inclusion of the y-parameter in :code:`Csv.cpp`
with consideration to the given dimension.

.. code:: c++

    int x_ghost_cell = 0;
    int y_ghost_cell = 0;
    // write the CSV header
    io_stream << "x,y";
    if (i_h != nullptr)
        io_stream << ",height";
    if (i_hu != nullptr)
    {
        io_stream << ",momentum_x";
        x_ghost_cell = 1;
    }
    if (i_hv != nullptr)
    {
        io_stream << ",momentum_y";
        y_ghost_cell = 1;
    }
    if (i_b != nullptr)
        io_stream << ",bathymetry";
    io_stream << "\n";

    // iterate over all cells
    for (t_idx l_iy = y_ghost_cell; l_iy < i_ny + y_ghost_cell; l_iy++)
    {
        for (t_idx l_ix = x_ghost_cell; l_ix < i_nx + x_ghost_cell; l_ix++)
        {
        // derive coordinates of cell center
        t_real l_posX = (l_ix + 0.5 - x_ghost_cell) * i_dxy + i_x_offset;
        t_real l_posY = (l_iy + 0.5 - y_ghost_cell) * i_dxy + i_y_offset;

        t_idx l_id = l_iy * i_stride + l_ix;

        // ...
    }

.. code:: c++
 
    {
        // move circle by amount
        t_real x_offset = i_x - 10;
        t_real y_offset = i_y - 25;
        if (std::sqrt(x_offset * x_offset + y_offset * y_offset) < 3)
        {
            return 10;
        }
        else
        {
            return -10;
        }
    }