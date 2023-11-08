Tsunami Report 3 Bathemetry & Boundary Conditions
=============================================

Links
-----

`Github Repo <https://github.com/Minutenreis/tsunami_lab>`_

`User Doc <https://tsunami-lab.readthedocs.io/en/latest/>`_

Individual Contributions
------------------------

Justus Dreßler: 

Thorsten Kröhl: 

Julius Halank: 

3.1 Non-zero Source Term
------------------------

3.1.1 Extend FWave  Solver with Bathemetry
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.1.2 Implent an example which illistrates the effect of bathemetry
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.2 Reflecting boundary conditions
----------------------------------

3.2.1 Implement the reflecting boundary conditions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.2.2 Show the implementation with the shock shock setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.3 Hydraulic Jumps
-------------------

3.3.1 Compute the location and value of the maximum Froude number
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.3.2 Implement both cases through the base class setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.3.3 Determine the position of the hydraulic jump
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.4 Tsunami simulation
----------------------

We will use for our csv reader a already existing one.
https://github.com/d99kris/rapidcsv
Is a simple csv reader that you can include by just adding the header file to your project.

Usage:
.. :code: csv

  Date,Open,High,Low,Close,Volume,Adj Close
  2017-02-24,64.529999,64.800003,64.139999,64.620003,21705200,64.620003
  2017-02-23,64.419998,64.730003,64.190002,64.620003,20235200,64.620003
  2017-02-22,64.330002,64.389999,64.050003,64.360001,19259700,64.360001
  2017-02-21,64.610001,64.949997,64.449997,64.489998,19384900,64.489998
  2017-02-17,64.470001,64.690002,64.300003,64.620003,21234600,64.620003

.. :code: cpp

  #include <iostream>
  #include <vector>
  #include "rapidcsv.h"

  int main()
  {
    rapidcsv::Document doc("examples/colrowhdr.csv", rapidcsv::LabelParams(0, 0));

    std::vector<float> close = doc.GetRow<float>("2017-02-22");
    std::cout << "Read " << close.size() << " values." << std::endl;

    long long volume = doc.GetCell<long long>("Volume", "2017-02-22");
    std::cout << "Volume " << volume << " on 2017-02-22." << std::endl;
  }

3.4.1




