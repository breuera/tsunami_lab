cmake_minimum_required(VERSION 3.26)
project(tsunami_lab)

message("####################################")
message("### Tsunami Lab                  ###")
message("###                              ###")
message("### https://scalable.uni-jena.de ###")
message("####################################")
message("")
message("running build script")
message("")

set(BUILD_MODE "release" CACHE STRING "compile modes, option 'san' enables address and undefined behavior sanitizers")

message("BUILD_MODE: ${BUILD_MODE}")

#set CMAKE_BUILD_TYPE and exit in the case of unknown variables
if(BUILD_MODE MATCHES "release" OR BUILD_MODE MATCHES "release_san")
    SET(CMAKE_BUILD_TYPE RELEASE)
    message("CMAKE_BUILD_TYPE set to release")
elseif(BUILD_MODE MATCHES "debug" OR BUILD_MODE MATCHES "debug_san")
    set(CMAKE_BUILD_TYPE DEBUG)
    message("CMAKE_BUILD_TYPE set to debug")
else()
    message("build configuration corrupted, don't know what to do with: ${BUILD_MODE}")
endif()

#add default flags
add_compile_options(-std=c++11 -Wall -Wextra -Wpedantic -Werror)

#set optimization mode
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    add_compile_options(-g -O0)
    message("added optimizations for debug mode")
else()
    add_compile_options(-O2)
    message("added optimizations")
endif()

#add sanitizers
if((BUILD_MODE MATCHES "release_san") OR (BUILD_MODE MATCHES "debug_san"))
    add_compile_options(-g -fsanitize=float-divide-by-zero -fsanitize=bounds -fsanitize=address -fsanitize=undefined-fno-omit -frame-pointer)
    add_link_options(-g -fsanitize=address -fsanitize=undefined)
    message("added sanitizers")
endif()

#add Catch 2
add_compile_options(-isystem submodules/Catch2/single_include)

add_executable(tsunami_lab src/main.cpp
        src/solvers/Roe.cpp
        src/patches/WavePropagation1d.cpp
        src/setups/DamBreak1d.cpp
        src/io/Csv.cpp)
set_target_properties(tsunami_lab
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/tsunami_lab/")
message("configured simulation target")

add_subdirectory(submodules/Catch2)
add_executable(tests src/tests.cpp
        src/solvers/Roe.cpp
        src/solvers/Roe.test.cpp
        src/patches/WavePropagation1d.cpp
        src/patches/WavePropagation1d.test.cpp
        src/setups/DamBreak1d.cpp
        src/setups/DamBreak1d.test.cpp
        src/io/Csv.cpp
        src/io/Csv.test.cpp
        )
target_link_libraries(tests PRIVATE Catch2::Catch2)
message("configured test target")


message("")
message("finished build script")
message("")
