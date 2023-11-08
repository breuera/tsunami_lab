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
   3_BathymetryBoundaryConditions
   doxygen

  



Tsunami-Simulation User Documentation
=====================================

Installing and Running
----------------------


* clone the project with :code:`git clone https://github.com/Minutenreis/tsunami_lab.git` 
* add the submodules with :code:`git submodule init` and :code:`git submodule update`
* build with :code:`scons`
* execute the Dam Break Problem with :code:`./build/tsunami_lab [-s Solver] [-u "setup arg1 arg2"] [-b "boundary_left boundary_right"] number_of_cells` 
* execute the tests with :code:`./build/tests`

The output of the Dam Break Problem is in :code:`/solutions`

Command Line Parameters
-----------------------

| :code:`number of cells` = number of cells the simulation gets broken up in.
| :code:`[-s solver]` = choose between :code:`roe` and :code:`fWave` solver, default is :code:`fWave`
| :code:`[-u setup]` = choose between :code:`'DamBreak1d h_l h_r'`, :code:`'ShockShock1d h hu'`, :code:`'RareRare1d h hu'`, :code:`Custom1d h_l h_r hu_l hu_r middle`, default is :code:`'DamBreak1d 10 5'`, args are to be input as floats
| :code:`[-b "boundary_left boundary_right"]` = choose each boundary between :code:`wall`, :code:`open`, default is :code:`'open open'`