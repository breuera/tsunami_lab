Tsunami Lab
==========================

This is the initial code of the Tsunami Lab taught at Friedrich Schiller University Jena.
Further information is available from: https://scalable.uni-jena.de/opt/tsunami/

Our website is available via the Github pages: https://philliprothenbeck.github.io/tsunami_lab/

### Requirements
- up-to-date version of the building tool `SCons`
- C++ with standard 11

### Setup Project

After cloning the project enter the following into the terminal for /tsunami_lab/:
```
$ git submodule init
$ git submodule update 
```

### Build the Project

Enter the following into the terminal, when being in /tsunami_lab/:

```
$ scons <build-mode>
```

#### Options for `<build-mode>`
- `release`: build in release mode, default value
- `release+san`: build in release mode and activate sanitizers
- `debug`: build in debug mode
- `debug+san`: build in debug mode and avtivate sanitizers

### Run the Code
Run unit tests from /tsunami_lab/ with:
```
$ ./build/tests
```
Run program from /tsunami_lab/ with:
```
$ ./build/tsunami_lab/ <scenario_mode> <n_cells_x> <solver>
```
#### Options for `<scenario_mode>`
Decides which setup is chosen
- `DamBreak`: loads a dam break setup
- `Sanitize1d`: loads data from a middle state file into a custom setup and checks if the calculated middle states are correct.
  The repository comes only with a dummy file `dummy_middle_states.csv` that contains 10 cases. The file `middle_states.csv` has to be placed manually into the folder `tsunami_lab/res/`.

#### Options for `<n_cells_x>`
Decides how many cells in the x direction are to be used in the program. Need to be an positive `int` value.

#### Options for `<solver>`
- `-r`: uses the roe solver
- `-f`: uses the f-wave solver, default value
