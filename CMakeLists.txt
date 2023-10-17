cmake_minimum_required(VERSION 3.1.0)
project(TsunamiSimulation VERSION 0.1.0 LANGUAGES C CXX)

message("####################################")
message("### Tsunami Lab                  ###")
message("###                              ###")
message("### https://scalable.uni-jena.de ###")
message("####################################")

# Setup compile Flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "/Wall /W3 /WL /EHsc ")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE on)


# Add source files
set(PROJECT_SOURCE_DIR "src")
set(PROJECT_INCLUDE_DIR "include")

set(SRC_FILES
    solvers/Roe
    setups/DamBreak1d
    patches/WavePropagation1d
    io/Csv
)
set(TEST_FILES ${PROJECT_SOURCE_DIR}/tests.cpp)
set(MAIN_FILE ${PROJECT_SOURCE_DIR}/main.cpp)

# Create SOURCE_FILES
foreach(file ${SRC_FILES})
    list(APPEND SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/${file}.cpp
        ${PROJECT_INCLUDE_DIR}/${file}.h
    )
    list(APPEND TEST_FILES
        ${PROJECT_SOURCE_DIR}/${file}.test.cpp
    )
endforeach()


# Set up such that your IDE organizes the files correctly
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

# Setup Testing
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1) # hack to prevent CTest added targets
add_executable(test ${SOURCE_FILES})
add_subdirectory(submodules/Catch2)
include_directories(SYSTEM submodules/Catch2/single_include)
target_link_libraries(test PRIVATE Catch2::Catch2)
target_sources(test PRIVATE ${TEST_FILES})

add_executable(build ${SOURCE_FILES})
target_sources(build PRIVATE ${MAIN_FILE})

add_executable(sanitize ${SOURCE_FILES})
target_sources(sanitize PRIVATE ${MAIN_FILE})

# Init sanitizer
if (MSVC)
    # MSVC only has address sanitizer
    set_target_properties(sanitize
        PROPERTIES
        COMPILE_FLAGS "/fsanitize=address /Zi"
    )
else()
    set_target_properties(sanitize
        PROPERTIES
        COMPILE_FLAGS "-g -fsanitize=float-divide-by-zero -fsanitize=bounds -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer"
        LINK_FLAGS "-g -fsanitize=address -fsanitize=undefined"
    )
endif()

if(CMAKE_COMPILER_IS_GNUCC AND WIN32)
    message(AUTHOR_WARNING "MingW (aka g++ on Windows) has no sanitizers :/")
endif()
if(MSVC)
    message(AUTHOR_WARNING "Test with Catch2 does not work because of linking error :(")
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# Doxygen

# look for Doxygen package
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs_doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)