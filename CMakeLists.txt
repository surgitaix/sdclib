# cmake version
# Note: Some of the functions need at least 3.5
cmake_minimum_required(VERSION 3.5.0)

#set(CMAKE_VERBOSE_MAKEFILE ON)

################################################################################
# Using own CMake Modules
# Add this to your cmake modules path to find the SDCLib Finder
################################################################################
get_filename_component(PROJECT_CMAKE_MODULES ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules REALPATH)
message(STATUS "Adding ${PROJECT_CMAKE_MODULES} to Modules Path...")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_CMAKE_MODULES})
################################################################################


################################################################################
# RPATH Settings
# NOTE: Set the RPath to the "Current Directory". (Portability)
################################################################################
set(CMAKE_INSTALL_RPATH ".")
################################################################################

################################################################
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
set( PROJECT_NAME "SDCLibrary") # in case you need it in a config file
project(${PROJECT_NAME})

# Version numbers -> Will be written to the config file
set (SDCLibrary_VERSION_FIRST          4)
set (SDCLibrary_VERSION_MIDDLE         1)
set (SDCLibrary_VERSION_LAST           0)
set (SDCLibrary_C_YEAR              2019)
set (SDCLibrary_SurgiTAIX "SurgiTAIX AG")



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
# What to enable?
################################################################################

# Tests - Default to ON
set (SDC_TESTS      ON CACHE STRING "Enable Building Tests")
set_property(CACHE SDC_TESTS PROPERTY STRINGS "ON" "OFF")

# Examples - Default to ON
set (SDC_EXAMPLES   ON CACHE STRING "Enable Building Examples")
set_property(CACHE SDC_EXAMPLES PROPERTY STRINGS "ON" "OFF")
################################################################################


################################################################################
# Enable to make Poco and SDCLib work when build as static/shared
################################################################################
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
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
set(DEBUG_POSTFIX_OUTPUT _d)

# by "default" take the install prefix
set(PATH_INSTALL_RUNTIME ${CMAKE_INSTALL_PREFIX}/bin)
set(PATH_INSTALL_LIBRARY ${CMAKE_INSTALL_PREFIX}/bin)
set(PATH_INSTALL_ARCHIVE ${CMAKE_INSTALL_PREFIX}/lib)
set(PATH_INSTALL_INCLUDE ${CMAKE_INSTALL_PREFIX}/include)
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
# Warnings
################################################################################
message(STATUS "Setting Warning-Level...")
if(CMAKE_BUILD_TYPE MATCHES Release)
    if (MSVC)
        add_compile_options(/W4)
    else()
        add_compile_options(-Wall -Wextra -pedantic)
    endif()
else()
    # Inhibit all warning messages
    add_compile_options(-w)
endif()
################################################################################

################################################################################
# Firewall - Allowed Ports
# Note: For the UnitTests and Examples to work, make sure in- and outbound
#       traffic on this portrange is allowed
# With ufw just run: sudo ufw allow <startport>:<endport>/tcp (or udp)
################################################################################

# Note: Just randomly took a port range that is not densly occupied from:
# https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers
# NOTE: CURRENTLY NOT IN USE!

set(SDC_ALLOWED_PORT_START 14000 CACHE STRING "Start Port of allowed port range. [Make sure your firewall settings match these value]" FORCE)
set(SDC_ALLOWED_PORT_RANGE  2000 CACHE STRING "Port Range of allowed ports as offset from the Start Port. [Make sure your firewall settings match these value]" FORCE)
set(SDC_DEFAULT_PORT_RANGE  1000 CACHE STRING "Passed default Port Range if none is specified in configuration." FORCE)

mark_as_advanced(SDC_ALLOWED_PORT_START)
mark_as_advanced(SDC_ALLOWED_PORT_RANGE)
mark_as_advanced(SDC_DEFAULT_PORT_RANGE)

set(SDC_DISCOVERY_TIMEOUT_MS 5000 CACHE STRING "Time in milliseconds a Discovery will take.")
mark_as_advanced(SDC_DISCOVERY_TIMEOUT_MS)

set(SDC_IP_V4_ENABLED true  CACHE STRING "Enable IPv4 by default or not." FORCE)
set(SDC_IP_V6_ENABLED false CACHE STRING "Enable IPv6 by default or not." FORCE)
mark_as_advanced(SDC_IP_V4_ENABLED)
mark_as_advanced(SDC_IP_V6_ENABLED)
################################################################################


################################################################################
# Python
################################################################################
message(STATUS "Looking for Python...")
set(Python_ADDITIONAL_VERSIONS 2.7)
find_package(PythonLibs 2.7 REQUIRED)

# Use it like this in the subprojects:
# ${PYTHON_LIBRARIES} # Path to the libs
#target_link_libraries(${CURRENT_TARGET_NAME} ${PYTHON_LIBRARIES})
################################################################################

################################################################################
# Some more paths - cleaned from symlinks
# Note: Use these in the other CMakeLists for easier handling
################################################################################
get_filename_component(PATH_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/src/ REALPATH)
get_filename_component(PATH_INCLUDE_ROOT ${CMAKE_CURRENT_LIST_DIR}/include/ REALPATH)
get_filename_component(PATH_DATAMODEL_ROOT ${CMAKE_CURRENT_LIST_DIR}/datamodel/ REALPATH)
get_filename_component(PATH_EXAMPLES_ROOT ${CMAKE_CURRENT_LIST_DIR}/Examples/ REALPATH)
get_filename_component(PATH_TESTS_ROOT ${CMAKE_CURRENT_LIST_DIR}/Tests/ REALPATH)
get_filename_component(PATH_SDCTESTS_ROOT ${PATH_TESTS_ROOT}/SDCTests/ REALPATH)
################################################################################


################################################################################
# config
# Note: Make sure all values are set before doing this!
################################################################################
set(CONFIG_DIR ${CMAKE_CURRENT_LIST_DIR}/include/config)

# configure
message(STATUS "Configuring ${PROJECT_NAME}...")
configure_file (${CONFIG_DIR}/config.h.in ${CONFIG_DIR}/config.h)
################################################################################


################################################################################
# Configuration Done
# Now add the subdirs
# Note: Inside the subdirs only work by including. See other files
message(STATUS "Adding Targets...")
################################################################################

# datamodel
add_subdirectory(${PATH_DATAMODEL_ROOT})

set(SDCLib_SEARCH_DIRS ".")
find_package(SDCLib)

# src folder
add_subdirectory(${PATH_SRC_ROOT})

# Examples
if(SDC_EXAMPLES)
    add_subdirectory(${PATH_EXAMPLES_ROOT})
endif()
# Tests
if(SDC_TESTS)
    add_subdirectory(${PATH_TESTS_ROOT})
ENDIF()
#...
