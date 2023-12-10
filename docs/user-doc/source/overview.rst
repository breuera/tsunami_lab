Overview
========

Dependencies
------------

To use the Tsunami-Simulator you need to install a number of programms into your system:

-  `SCons
   <https://www.scons.org/doc/production/HTML/scons-user.html>`_

-  `ParaView <https://www.paraview.org/>`_

Installation
------------

Installing the project is very simple. All you need to do is:

.. admonition:: Guide

   #. Clone the project via the command line :code:`git clone https://github.com/MherMnatsakanyan03/tsunami_lab.git` 
   #. Installing the submodule using :code:`git sumbodule init` and :code:`git sumbodule update`
   #. Installing the requirements using :code:`sudo apt-get install libnetcdf-c++4-dev` and :code:`sudo apt-get install netcdf-bin`
   #. While in the repository, enter the building command into your console: :code:`scons`
   #. In the console, use :code:`./build/tsunami_lab [-d DIMENSION] [-s SETUP] [-v SOLVER] [-l STATE_LEFT] [-r STATE_RIGHT] [-t STATE_TOP] [-b STATE_BOTTOM] [-i STATION] [-k RESOLUTION] <number-of-cells>` (Tip: to be sure that you are in the correct console, you can write ./b and press the "tab"-button and see, if the console completes the path automatically)
   #. The output-files should be generated in either in the `csv-dump`-folder or in `netCDF_dump` (depending if you use 1d or 2d)

..  tip::
   #. possible inputs for :code:`DIMENSION` are "1d" and "2d". This parameter has to be used. When using 2d, the grid will be square with the y-axis being equal to the x-axis
   #. possible inputs for :code:`SETUP` if :code:`DIMENSION` is 1d are 

      * :code:`'dambreak1d [height-left] [height-right]'`
      * :code:`'shockshock1d [height] [momentum]'`
      * :code:`'rarerare1d [height] [momentum]'`
      * :code:`'subcritical1d'`
      * :code:`'supercritical1d'`
      * :code:`'tsunami1d'`
   #. possible inputs for :code:`SETUP` if :code:`DIMENSION` is 2d are 
   
      * :code:`'dambreak2d'` 
      * :code:`'artificial2d'` 
      * :code:`'tsunami2d'` 
      * :code:`'checkpoint'` This setup will load the last checkpoint which was generated, depending on what 2d-simulation was started before.
   #. possible inputs for :code:`SOLVER` are "fwave" and "roe". Not using this parameter will use "fwave" by default.
   #. possible inputs for :code:`STATE_LEFT` are "open" or "closed"
   #. possible inputs for :code:`STATE_RIGHT` are "open" or "closed"
   #. possible inputs for :code:`STATE_TOP` are "open" or "closed"
   #. possible inputs for :code:`STATE_BOTTOM` are "open" or "closed"
   #. input for :code:`STAION` is the path, where you want the station-data to be saved to
   #. input for :code:`RESOLUTION` is a number by which the size of all arrays will be divided by to save some space while writing