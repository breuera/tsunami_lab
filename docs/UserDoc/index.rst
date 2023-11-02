.. Tsunami-Simulation documentation master file, created by
   sphinx-quickstart on Mon Oct 23 20:12:43 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. toctree::
   :maxdepth: 2
   :hidden:

   self
   1_RiemannSolver
   2_FiniteVolumeDiscretization
   doxygen

  



Tsunami-Simulation User Documentation
=====================================

Installing and Running
----------------------

:: 
   todo: mehr Commandline Optionen hinzufügen?

* clone the project with :code:`git clone https://github.com/Minutenreis/tsunami_lab.git` 
* add the submodules with :code:`git submodule init` and :code:`git submodule update`
* build with :code:`scons`
* execute the Dam Break Problem with :code:`./build/tsunami_lab <number of cells> <opt: solver>` 
* execute the tests with :code:`./build/tests`

The output of the Dam Break Problem is in :code:`/solutions`

Command Line Parameters
-----------------------

<number of cells>: number of cells the simulation gets broken up in.
<opt: solver>: choose between 'roe' and 'fWave' solver, default is 'fWave'