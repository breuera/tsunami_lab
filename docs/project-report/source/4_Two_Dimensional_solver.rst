# 4 Two Dimensional solver

## Links:

`Github Repo <https://github.com/MherMnatsakanyan03/tsunami_lab.git>`\_

## Individual Contributions:

Mher Mnatsakanyan and Maurice Herold did a similar amount of work.

## Task 4.1:

4.1.1 2D support
^^^^^^^^^^^^^^^^
´


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