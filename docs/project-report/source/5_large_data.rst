5 Large Data
============

Links:
------------

`Github Repo <https://github.com/MherMnatsakanyan03/tsunami_lab.git>`_


Individual Contributions:
-------------------------

Mher Mnatsakanyan and Maurice Herold did a similar amount of work.

Task 5.1: NetCDF Output
------------------------

5.1.2 NetCdf Class
^^^^^^^^^^^^^^^^^^

The :code:`tsunami_lab::io::NetCdf` class has been implemented as a fundamental interface for interacting
with netCDF files in our tsunami simulation project. This class provides functionalities for writing
simulation data to netCDF files and reading from binary netCDF files.

**Note to Alex Breuer**

Right from the get-go it has to be stated, that we struggled a lot during the developement phase and
ran across a multitude of issues. To get everything running, one of our fellow students (Justus) helped
us out along the way. We mention this because we are aware that some of our code may seem similar to
his teams. We want to make it very clear that we did not see their code directly. Justus explained
their approaches towards several problems and looked over our errors which is why some of the
calculations or functions in the :code:`NetCdf` class will be similar to theirs.



Class Implementation
^^^^^^^^^^^^^^^^^^^^

1. **Initialization Method**:

   The :code:`initialize` method sets up the netCDF file by defining dimensions (x, y, time) and variables
   (height, momentum_x, momentum_y, bathymetry). It also assigns appropriate units to each variable.
   This methode is not nessecary for the :code:`read` function but is essential for :code:`write`.

   .. code-block:: cpp

      void tsunami_lab::io::NetCdf::initialize(const std::string &filename,
                                               t_real i_dxy,
                                               t_idx i_nx,
                                               t_idx i_ny,
                                               t_real i_x_offset,
                                               t_real i_y_offset,
                                               t_real const *i_b)
    {
        handleNetCdfError(nc_create(filename.c_str(), NC_CLOBBER, &m_ncid), "Error creat the NetCDF file: ");

        // Define the dimensions
        handleNetCdfError(nc_def_dim(m_ncid, "x", i_nx, &m_x_dimid), "Error define x dimension: ");
        handleNetCdfError(nc_def_dim(m_ncid, "y", i_ny, &m_y_dimid), "Error define y dimension: ");
        handleNetCdfError(nc_def_dim(m_ncid, "time", NC_UNLIMITED, &m_time_dimid), "Error define time dimension: ");

        // Define variables
        int dims[3] = {m_time_dimid, m_y_dimid, m_x_dimid};
        handleNetCdfError(nc_def_var(m_ncid, "x", NC_FLOAT, 1, &m_x_dimid, &m_x_varid), "Error define x variable: ");
        handleNetCdfError(nc_def_var(m_ncid, "y", NC_FLOAT, 1, &m_y_dimid, &m_y_varid), "Error define y variable: ");
        handleNetCdfError(nc_def_var(m_ncid, "time", NC_FLOAT, 1, &m_time_dimid, &m_time_varid), "Error define y variable: ");

        handleNetCdfError(nc_def_var(m_ncid, "height", NC_FLOAT, 3, dims, &m_h_varid), "Error define height variable:");
        handleNetCdfError(nc_def_var(m_ncid, "momentum_x", NC_FLOAT, 3, dims, &m_hu_varid), "Error define momentum_x variable:");
        handleNetCdfError(nc_def_var(m_ncid, "momentum_y", NC_FLOAT, 3, dims, &m_hv_varid), "Error define momentum_y variable:");

        int bathy_dims[2] = {m_y_dimid, m_x_dimid};
        handleNetCdfError(nc_def_var(m_ncid, "bathymetry", NC_FLOAT, 2, bathy_dims, &m_b_varid), "Error define bathymetry variable:");

        handleNetCdfError(nc_put_att_text(m_ncid, m_x_varid, "units", 5, "meter"), "Error adding text x dimension");
        handleNetCdfError(nc_put_att_text(m_ncid, m_y_varid, "units", 5, "meter"), "Error adding text y dimension");
        handleNetCdfError(nc_put_att_text(m_ncid, m_time_varid, "units", 7, "seconds"), "Error adding text x dimension");
        handleNetCdfError(nc_put_att_text(m_ncid, m_h_varid, "units", 5, "meter"), "Error adding text height dimension");
        handleNetCdfError(nc_put_att_text(m_ncid, m_hu_varid, "units", 14, "newton-seconds"), "Error adding text momentum_x dimension");
        handleNetCdfError(nc_put_att_text(m_ncid, m_hv_varid, "units", 14, "newton-seconds"), "Error adding text momentum_y dimension");
        handleNetCdfError(nc_put_att_text(m_ncid, m_b_varid, "units", 5, "meter"), "Error adding text bathymetry dimension");

        handleNetCdfError(nc_enddef(m_ncid), "Error end defining: ");

        // put y
        t_real *l_y = new t_real[i_ny];
        for (t_idx l_iy = 0; l_iy < i_ny; l_iy++)
        {
            l_y[l_iy] = (l_iy + 0.5) * i_dxy - i_y_offset;
        }
        handleNetCdfError(nc_put_var_float(m_ncid, m_y_varid, l_y), "Error put y variables: ");

        // put x
        t_real *l_x = new t_real[i_nx];
        for (t_idx l_ix = 0; l_ix < i_nx; l_ix++)
        {
            l_x[l_ix] = (l_ix + 0.5) * i_dxy - i_x_offset;
        }
        handleNetCdfError(nc_put_var_float(m_ncid, m_x_varid, l_x), "Error put x variables: ");

        handleNetCdfError(nc_put_var_float(m_ncid, m_b_varid, i_b), "Error put bathymetry variables: ");

        delete[] l_x;
        delete[] l_y;
        delete[] i_b;
    }

2. **Data Writing Method**:

   The `write` method writes the current simulation data to the netCDF file. It handles the
   dimensions and writes data excluding ghost cells.

   .. code-block:: cpp

      void tsunami_lab::io::NetCdf::write(t_idx i_nx,
                                          t_idx i_ny,
                                          t_real const *i_h,
                                          t_real const *i_hu,
                                          t_real const *i_hv,
                                          t_idx timeStep,
                                          t_real i_time)
    {

        size_t start[3] = {timeStep, 0, 0};
        size_t count[3] = {1, i_ny, i_nx};

        handleNetCdfError(nc_put_vara_float(m_ncid, m_h_varid, start, count, i_h), "Error put height variables: ");
        handleNetCdfError(nc_put_vara_float(m_ncid, m_hu_varid, start, count, i_hu), "Error put momentum_x variables: ");
        handleNetCdfError(nc_put_var1_float(m_ncid, m_time_varid, &timeStep, &i_time), "Error put time variables: ");

        handleNetCdfError(nc_put_vara_float(m_ncid, m_hv_varid, start, count, i_hv), "Error put momentum_y variables: ");

        delete[] i_h;
        delete[] i_hu;
        delete[] i_hv;
    }

3. **Error Handling Method**:

   `handleNetCdfError` ensures robust error checking and handling during file operations, enhancing
   the reliability of data writing.

   .. code-block:: cpp

      void tsunami_lab::io::NetCdf::handleNetCdfError(int status, const std::string &errorMessage)
        {
        if (status != NC_NOERR)
        {
            std::cerr << errorMessage << nc_strerror(status) << std::endl;
            exit(-1);
        }

4. **Ghost Cell Removal Method**:

   The `removeGhostCells` function is specifically designed to exclude ghost cells from the data written to the file.

   .. code-block:: cpp

        tsunami_lab::t_real *tsunami_lab::io::NetCdf::removeGhostCells(const t_real *i_d,
                                                                       t_idx i_nx,
                                                                       t_idx i_ny,
                                                                       t_idx i_ghostCellsX,
                                                                       t_idx i_ghostCellsY,
                                                                       t_idx i_stride)
        {
            t_real *l_o = new t_real[i_nx * i_ny];

            for (t_idx l_x = 0; l_x < i_nx; l_x++)
            {
                for (t_idx l_y = 0; l_y < i_ny; l_y++)
                {
                t_idx l_id = (l_y + i_ghostCellsY) * i_stride + (l_x + i_ghostCellsX);

                l_o[l_y * i_nx + l_x] = i_d[(l_id)];
                }
            }
            return l_o;
        }


Task 5.2: NetCDF Input
----------------------

5.2.1 Artificial Tsunami
^^^^^^^^^^^^^^^^^^^^^^^^

The artificial tsunami-setup was implemented in a static way, just like the mathematical
formulas demand it to be. The notable functions are:

.. code:: c++

    tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getHeight(t_real,
                                                                            t_real) const
    {
        return 100;
    }

    tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getBathymetry(t_real i_x,
                                                                                t_real i_y) const
    {
        return -100 + getDisplacement(i_x, i_y);
    }

    tsunami_lab::t_real tsunami_lab::setups::ArtificialTsunami2d::getDisplacement(t_real i_x,
                                                                                t_real i_y) const
    {
        if (i_x >= -500 && i_x <= 500 && i_y >= -500 && i_y <= 500)
        {
            return 5 * f(i_x, i_y) * g(i_x, i_y);
        }
        return 0;
    }



5.2.2 NetCDF File-reader
^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    void tsunami_lab::io::NetCdf::read(t_idx *o_nx,
                                       t_idx *o_ny,
                                       t_real **o_x,
                                       t_real **o_y,
                                       t_real **o_z,
                                       const std::string filename)
    {

        std::cout << "NetCDF:: Looking for file: " << filename << std::endl;
        t_idx l_nx, l_ny;

        int l_ncid_read;

        handleNetCdfError(nc_open(filename.data(), NC_NOWRITE, &l_ncid_read), "Error open file: ");

        int l_x_dimid_read, l_y_dimid_read;

        handleNetCdfError(nc_inq_dimid(l_ncid_read, "x", &l_x_dimid_read), "Error getting y dimension id: ");
        handleNetCdfError(nc_inq_dimid(l_ncid_read, "y", &l_y_dimid_read), "Error getting y dimension id: ");

        handleNetCdfError(nc_inq_dimlen(l_ncid_read, l_x_dimid_read, &l_nx), "Error getting x dimension length: ");
        handleNetCdfError(nc_inq_dimlen(l_ncid_read, l_y_dimid_read, &l_ny), "Error getting y dimension length: ");

        int l_x_varid_read, l_y_varid_read, l_z_varid_read;

        handleNetCdfError(nc_inq_varid(l_ncid_read, "x", &l_x_varid_read), "Error getting x value id: ");
        handleNetCdfError(nc_inq_varid(l_ncid_read, "y", &l_y_varid_read), "Error getting y value id:");
        handleNetCdfError(nc_inq_varid(l_ncid_read, "z", &l_z_varid_read), "Error getting z value id:");

        t_real *l_xv, *l_yv, *l_zv;
        l_xv = new t_real[l_nx];
        l_yv = new t_real[l_ny];
        l_zv = new t_real[l_nx * l_ny];

        handleNetCdfError(nc_get_var_float(l_ncid_read, l_x_varid_read, l_xv), "Error getting x value: ");
        handleNetCdfError(nc_get_var_float(l_ncid_read, l_y_varid_read, l_yv), "Error getting y value: ");
        handleNetCdfError(nc_get_var_float(l_ncid_read, l_z_varid_read, l_zv), "Error getting z value: ");

        *o_nx = l_nx;
        *o_ny = l_ny;
        *o_x = l_xv;
        *o_y = l_yv;
        *o_z = l_zv;

        handleNetCdfError(nc_close(l_ncid_read), "Error closing file: ");
    }

This method first opens the specified netCDF file for reading. It then inquires about the
dimensions and variables (x, y, z), reads their lengths and values, and stores them in the
provided pointers. The method ensures that all data is accurately read and stored,
facilitating further processing or visualization.

Here we ran into a (stupid) problem that we tried to save memory by using a globally declared
variable for the file-IDs. You can imagine that using the same IDs to read AND write is not
the best idea. Again, it was here mainly where Justus helped us out a lot.


5.2.3 Tsunami Event 2d
^^^^^^^^^^^^^^^^^^^^^^

For the first time, we used the new :code:`NetCFD`-class to read values of bathymetry and
displacement for our simulation. We accomplished that by calling the :code:`read` function
inside the constructor of the setup:

.. code:: c++

    tsunami_lab::setups::TsunamiEvent2d::TsunamiEvent2d()
    {
        tsunami_lab::io::NetCdf *netCDF = nullptr;

        netCDF = new tsunami_lab::io::NetCdf();

        std::cout << "Entering TsunamiEvent2d" << std::endl;

        std::string bat_path = "data/artificialtsunami/artificialtsunami_bathymetry_1000.nc";
        std::string dis_path = "data/artificialtsunami/artificialtsunami_displ_1000.nc";

        netCDF->read(&m_bathymetry_length_x,
                    &m_bathymetry_length_y,
                    &m_bathymetry_values_x,
                    &m_bathymetry_values_y,
                    &m_bathymetry,
                    bat_path);

        netCDF->read(&m_displacement_length_x,
                    &m_displacement_length_y,
                    &m_displacement_values_x,
                    &m_displacement_values_y,
                    &m_displacement,
                    dis_path);

        delete netCDF;
    }

To not run into memory-leak issues, we needed to delete several arrays in a seperate
destructor-function:

.. code:: c++

    tsunami_lab::setups::TsunamiEvent2d::~TsunamiEvent2d()
    {
        delete[] m_bathymetry_values_x;
        delete[] m_bathymetry_values_y;
        delete[] m_bathymetry;
        delete[] m_displacement_values_x;
        delete[] m_displacement_values_y;
        delete[] m_displacement;
    }

5.2.4 Tsunami-Comparison
^^^^^^^^^^^^^^^^^^^^^^^^

The simulation showed a clear reseblance betweem the two setups. Our simulation
had little (unknown) differences between the two, but they looked very similar.

We won't include any pictures this time, because we lack the time, sorry. :P