.. Tsunami WS23 documentation master file, created by
   sphinx-quickstart on Sun Oct 29 19:23:37 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Tsunami WS23's documentation!
========================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:



Dependencies
============

To use the Tsunami-Simulator you need to install a number of programms into your system:

-  `SCons
   <https://www.scons.org/doc/production/HTML/scons-user.html>`_

-  `ParaView <https://www.paraview.org/>`_

Installation
============

Installing the project is very simple. All you need to do is:

.. admonition:: Guide

   #. Clone the project via the command line :code:`git clone https://github.com/MherMnatsakanyan03/tsunami_lab.git` 
   #. Installing the submodule using :code:`git sumbodule init` and :code:`git sumbodule update`
   #. While in the repository, enter the building command into your console: :code:`scons`
   #. In the console, use :code:`./build/tsunami_lab <number-of-cells>` (Tip: to be sure that you are in the correct console, you can write ./b and press the "tab"-button and see, if the console completes the path automatically)
   #. The csv-tables with the output should be generated in the `csv-dump`-folder