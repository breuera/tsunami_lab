.. _User_Documentation:

User Documentation
==================

.. _ch:introduction:

introduction
------------

Welcome to the Tsunami Lab Project! This user documentation will guide you through the process of downloading the project's source code from GitHub 
and compiling it so that you can start working with the software.

.. _ch:Getting_Started:

Getting Started
---------------

Prerequisites
^^^^^^^^^^^^^
Before you can begin, ensure that you have the following prerequisites installed on your system:

* Python3
* C++ (Version 11 or later)
* SCons
* CMake
* Doxygen
* git

Downloading the Code
^^^^^^^^^^^^^^^^^^^^
#. Open your terminal or command prompt.

#. Change to the directory where you want to store the project.

#. Run the following command to clone the project repository from GitHub:

    .. code-block:: bash
        
        git clone https://github.com/PhillipRothenbeck/tsunami_lab.git

#. Navigate into the directory
#. Download all submodules

    .. code-block:: bash
        
        cd tsunami_lab
        git submodules init
        git submodules update.

.. _ch:Compiling_the_Code:

Compiling the code
------------------

Compiling Doxygen
^^^^^^^^^^^^^^^^^

#. Open your terminal or command prompt.

#. Navigate to the project's root directory where the Doxygen configuration file (Doxyfile.in) is located.

#. Run the following command to generate the documentation:

    .. code-block::

        doxygen Doxyfile.in

#. Once the documentation generation is complete, you can open the documentation in your browser of choice by opening the following URL:

    .. code-block::

        file:///path/to/tsunami-lab-project/_build/html/index.html

Compiling the project
^^^^^^^^^^^^^^^^^^^^^
To compile the Tsunami Lab Project, you have various options and flags to choose from. 
The primary compilation command is scons, and you can specify flags to customize the build. Here are the available flags:
mode (Optional):

Use scons without specifying the mode flag to build with default settings.
You can use one of the following modes:

#. release: Optimized release mode.
#. release+san: Release mode with sanitizers.
#. debug: Debug mode.
#. debug+san: Debug mode with sanitizers.

To compile the project, navigate to the project's root directory and run the following command:

.. code-block::

    scons

To compile with a specific mode, use the mode flag as follows:

.. code-block::
 
    scons mode=release

.. _ch:Running_the_project:

Running the project
-------------------
Make sure that the current terminal is located in the /tsunami_lab/ directory.

To execute the test files, use the following command:

.. code-block::

    ./build/tests

To execute the project, use the following command with the appropriate flags:

.. code-block::

    ./build/tsunami_lab <config_file_name.json>

The ``<config_file_name.json>`` argument is used to pass the name of the JSON config 
file on to the program. The config needs to be located in the /tsunami_lab/res/configs/ 
directory.

Structure of a config file
^^^^^^^^^^^^^^^^^^^^^^^^^^

**List of arguments:**

- "dimension": integer, that indicates the dimensions of a simulation

- "nx": integer, that decides the number of cells in x-direction

- "ny": integer, that decides the number of cells in y-direction

- "xLen": float, that decides the length in x-direction 

- "yLen": float, that decides the length in y-direction 

- "thresholdX": float, that decides the changing point in x-direction for a setup (ex.: dam location)

- "thresholdY": float, that decides the changing point in y-direction for a setup

- "simTime": float, time length of a simulation

- "boundaryCond": string, that decides the boundary conditions

Options: 1d: "OO", "RR", "RO", "OR"; 2d: "OO"

- "setup": string, that decides the used setup

Options: 
1d: "DamBreak", "RareRare", "ShockShock", "SubcriticalFlow", "SupercriticalFlow", "TsunamiEvent", "Sanitize", "CustomSetup"; 
2d: "DamBreak"



.. _ch:Troubleshooting:

Troubleshooting
---------------

If you encounter any issues while working with the Tsunami Lab Project, please refer to the following common issues and contact information for assistance.

Common issues
^^^^^^^^^^^^^

* Compilation Errors:
    If you encounter compilation errors, ensure that you have all the necessary prerequisites installed, as mentioned in the Prerequisites section. Verify that you have the correct versions of Python, C++, SCons, CMake, and Doxygen.

    Double-check the compilation flags and options specified in the Compiling the Code section.

* Doxygen Documentation:
    If you face issues generating Doxygen documentation, make sure you have executed the correct command mentioned in the Compiling Doxygen section. Ensure that the Doxyfile.in is present in the project directory.

* Running the Project:
    If you encounter errors while running the project, ensure that you have provided the correct command-line flags as explained in the Compiling the Project section. Check for any typos or incorrect inputs.
    Verify that the required input files (e.g., Middle_states or dummy_middle_states) are present in the designated folders as mentioned in the project flags.

Contact Information
^^^^^^^^^^^^^^^^^^^

If you are unable to resolve your issue or face any other difficulties not mentioned here, please feel free to contact the Tsunami Lab Project maintainers for assistance. You can reach out to us at the following email addresses:

* Bohdan Babii: bohdan.babii@uni-jena.de
* Phillip Rothenbeck: phillip.rothenbeck@uni-jena.de

We are here to help you with any questions or problems you may encounter while using the Tsunami Lab Project. Please don't hesitate to reach out, and we will do our best to assist you.