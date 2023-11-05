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
   #. While in the repository, enter the building command into your console: :code:`scons`
   #. In the console, use :code:`./build/tsunami_lab [-v SOLVER] [-s SETUP] <number-of-cells>` (Tip: to be sure that you are in the correct console, you can write ./b and press the "tab"-button and see, if the console completes the path automatically)
   #. The csv-tables with the output should be generated in the `csv-dump`-folder

..  tip::
   #. possible inputs for :code:`SOLVER` are "fwave" and "roe". Not using this parameter will use "fwave" by default.
   #. possible inputs for :code:`SETUP` are :code:`'dambreak [height-left] [height-right]'`, :code:`'shockshock [height] [momentum]'` or :code:`'rarerare [height] [momentum]'`