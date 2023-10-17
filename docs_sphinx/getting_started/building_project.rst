.. _getting_started_building_project:

.. role:: raw-html(raw)
    :format: html

Building the Project
====================


Requirements
------------

To use this project ``CMake`` is required.
You can check if ``CMake`` is installed by running

.. code-block:: bash

    cmake --version

.. note::
    ``CMake`` can be `downloaded <https://cmake.org/download/#latest>`_ or installed OS Specific through other methods

    *Windows*
        There are several ways to install ``CMake`` on Windows.

        Using `Windows Package Manager <https://learn.microsoft.com/de-de/training/modules/explore-windows-package-manager-tool/>`_
            ``CMake`` can be installed using the following command

            .. code-block:: bash

                winget install kitware.cmake

        Using `Chocolatey <https://chocolatey.org>`_
            ``CMake`` can be installed using the following command

            .. code-block:: bash

                choco install cmake

        Using `Visual Studio <https://visualstudio.microsoft.com>`_
            `Official Installation Guid <https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation>`_

            .. image:: ../images/VisualStudio_CMake_Installation.png
                :align: right
                :scale: 75%

            1. Therefore you need to `download Visual Studio <https://visualstudio.microsoft.com/de/downloads/>`_. The Community Edition is free.

            2. Starting the Visual Studio Installer

            3. Select ``Desktop development with C++`` and make sure that ``C++-CMake-Tools für Windows`` is checked on the right side of the installer.

            4. Press Install


    *Linux*
        A simple way is using ``apt-get`` by running the command

        .. code-block:: bash

            sudo apt-get install cmake

    
    *MacOS*
        A simple way is using ``brew`` by running the command

        .. code-block:: bash

            brew install cmake


Installation
------------

1. Download the `git repository <https://github.com/RivinHD/Tsunami-Simulation>`_ by clicking on the Code Button

2. Go into the project folder. Your current path should look like this ``../Tsunami-Simulation``.

3. Now create a new folder called ``build`` with

    .. code-block:: bash

        mkdir build

4. Go into this directory. Your current path should look like this ``../Tsunami-Simulation/build``.

5. Now we can start with CMake. Run the following command

    .. code-block:: bash

        cmake ..

    .. note::

        With the Option ``-G`` a Generator can be defined used to create the make files and compile the Code.
        All available Generators can be found at the bottom of the :raw-html:`<br/>` ``cmake --help`` text.
        An Example could look like this

        .. code-block:: bash

            cmake .. -G "MinGW Makefiles"

    Now our make files are being build from the ``CMakeLists.txt`` that are used to build the project.

6. Now we can build the project. The most desired command might be

    .. code-block:: bash

        cmake --build . --config Release --target build

    Which build the project with the Optimization turned on.

    Options for ``--config`` are **Release** and **Debug**

    Where **Release** enable the Optimization flags and **Debug** disable the Optimization flags.

    Options for ``--target`` are **build**, **sanitize** and **test**

    +-----------+-----------------------------------------------------------+
    |Option     |  Description                                              |
    +===========+===========================================================+
    | build     | Is the Option to build the project with default flags     |
    +-----------+-----------------------------------------------------------+
    | sanitize  | Enables code sanitization                                 |
    +-----------+-----------------------------------------------------------+
    | test      | Builds the unit test executable                           |
    +-----------+-----------------------------------------------------------+

    




