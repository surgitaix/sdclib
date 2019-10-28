# cmake version
cmake_minimum_required(VERSION 3.5.0)
################################################################################
# Note: This is the "entry point" for cmake. Make a general configuration on
#       your project, like the C++ standard, the minimum compiler version etc.
#       Targets will be added in other CMakeLists files and be configured
#       individually and based on the set variables.
################################################################################


################################################################################
# Using the sdclib modules folder and add to CMake Modules
get_filename_component(PROJECT_CMAKE_MODULES ${CMAKE_CURRENT_LIST_DIR}/../../cmake/Modules REALPATH)
message(STATUS "Adding ${PROJECT_CMAKE_MODULES} to Modules Path...")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_CMAKE_MODULES})
################################################################################

################################################################################
# C++ standard
################################################################################
message(STATUS "Setting CXX_STANDARD...")
set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ Standard" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
################################################################################



################################################################################
# Main Project
################################################################################
set( PROJECT_NAME "CMakeExampleProject" CACHE STRING "CMake ExampleProject")
project(${PROJECT_NAME} "CXX")
################################################################################


################################################################################
# Check Compiler Version
################################################################################
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8.1)
        message(FATAL_ERROR "GCC version must be at least 4.8.1!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
        message(FATAL_ERROR "Clang version must be at least 3.3!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.0)
        message(FATAL_ERROR "MSVC version must be at least 18.0!")
    endif()
else()
    message(FATAL_ERROR "No supported Compiler detected. Checked for GCC(4.8.1+), Clang(3.3+) or MSVC(18.0+).")
endif()
################################################################################



################################################################################
# Bin and Install prefix
################################################################################
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Default install prefix init to default, manually setting one...")
    set (CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install CACHE STRING "Where to install the binaries?" FORCE)
endif()

set(PATH_RUNTIME_OUTPUT ${PROJECT_BINARY_DIR}/bin)
set(PATH_LIBRARY_OUTPUT ${PROJECT_BINARY_DIR}/bin)
set(PATH_ARCHIVE_OUTPUT ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX _d) # Force the Debug Postfix

# by "default" take the install prefix
set(PATH_INSTALL_RUNTIME ${CMAKE_INSTALL_PREFIX}/bin)
set(PATH_INSTALL_LIBRARY ${CMAKE_INSTALL_PREFIX}/bin)
set(PATH_INSTALL_ARCHIVE ${CMAKE_INSTALL_PREFIX}/lib)
################################################################################



################################################################################
# Targets
# Overwrite
################################################################################
set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Config Types")
# None specified?
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type specified, setting to Debug.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Debug as default" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug")
endif()
################################################################################

################################################################################
# Some more paths - cleaned from symlinks
################################################################################
# Path to dependencie folder - here its the path one above the cmake root folder
# Imagine the following project structure, when embedding the sdclib into your
# own project:
# Project/
#   - src/
#       - ...
#       - ...
#   - include/
#       - ...
#       - ...
#   - dependencies/ <- ${PATH_DEPS_ROOT} points here
#       - sdclib
#       - sdclib_build (Set to ignore by git or exclude in .git/info/exclude)
#       - ...
#   - dev/
get_filename_component(PATH_DEPS_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../ REALPATH)
# Note: PATH_DEPS_ROOT is an absolute path pointing to the sdc root directory.
#       The Example project structure does not match the one in this example,
#       because here the ExampleProject lies inside a subfolder of the git
#       project. But as long as the absolute pathes are correct, cmake will
#       find the SDCLib.
################################################################################

################################################################################
# SDCLib
################################################################################
# Here we have to specify the SDC Folders root path
################################################################################

# This variable is needed by the FindSDCLib.cmake module. Set it to the SDCLib
# root dir.
set(SDCLib_SEARCH_DIRS "${PATH_DEPS_ROOT}/sdclib" CACHE STRING "SDCLib root dir")

# FindSDCLib.cmake will set all necessary variables, Prefix: SDCLib_
include(${SDCLib_SEARCH_DIRS}/FindSDCLib.cmake)
if(NOT SDCLib_FOUND)
    message(FATAL_ERROR "SDC not found, build it first or specify correct path!")
endif()
################################################################################



################################################################################
# RPATH Settings
# NOTE: Set the RPath to the "Current Directory". (Portability)
################################################################################
set(CMAKE_INSTALL_RPATH ".")
################################################################################


################################################################################
# Configuration Done
# Now add the subdirectories
message(STATUS "Adding Targets...")
################################################################################

# Code Directory
add_subdirectory(code)

# ...
# ...
