###########
Tsunami Lab
###########

This is the initial code of the Tsunami Lab taught at Friedrich Schiller University Jena.
Further information is available from: https://scalable.uni-jena.de/opt/tsunami/

###How to build the project using cmake?

1. navigate to the tsunami_lab folder
2. create a folder 'cmake-build'
3. navigate to the folder 'cmake-build'
4. enter the command $ cmake -DBUILD_MODE:STRING=<build_mode> ../

  options for <build_mode>: release, release_san, debug, debug_san
  <build_mode> defaults to release

5. enter the command 4 cmake --build ../
