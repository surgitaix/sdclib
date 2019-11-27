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
set (SDCLibrary_VERSION_MIDDLE         3)
set (SDCLibrary_VERSION_LAST           8)
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
set(CMAKE_DEBUG_POSTFIX _d) # Force the Debug Postfix

# by "default" take the install prefix
set(PATH_INSTALL_RUNTIME bin)
set(PATH_INSTALL_LIBRARY bin)
set(PATH_INSTALL_ARCHIVE lib)
set(PATH_INSTALL_INCLUDE include)
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

set(SDC_DISCOVERY_TIMEOUT_MS 5000 CACHE STRING "Time in milliseconds a Discovery until timeout." FORCE)
mark_as_advanced(SDC_DISCOVERY_TIMEOUT_MS)

set(SDC_CONNECTION_TIMEOUT_MS 4000 CACHE STRING "Time in milliseconds the SDCLib will check if the connection is lost." FORCE)
mark_as_advanced(SDC_CONNECTION_TIMEOUT_MS)


set(SDC_MAX_KNOWN_MESSAGE_IDS 200 CACHE STRING "Limits the maximum number of MessageIDs a Messaging Context caches. Be careful with this value!" FORCE)
mark_as_advanced(SDC_MAX_KNOWN_MESSAGE_IDS)

set(SDC_IP_V4_ENABLED true  CACHE STRING "Enable IPv4 by default or not." FORCE)
set(SDC_IP_V6_ENABLED false CACHE STRING "Enable IPv6 by default or not." FORCE)
mark_as_advanced(SDC_IP_V4_ENABLED)
mark_as_advanced(SDC_IP_V6_ENABLED)
################################################################################

################################################################################
# OpenSSL - Version Check
# Note: Must be placed here in order to be added to the config file. Patch 
# version is set to a number, where (1 = a, 2 = b, ...) 
# In the following, the variables for the supported OpenSSL minimal version are
# defined. The OpenSSL version is defined by major version, minor, fix, patch
# and a status (release / development, ...) 
################################################################################

# Enable static build of OpenSSL
# Taken from https://cmake.org/cmake/help/v3.4/module/FindOpenSSL.html#hints
# TODO: Required here? Or should it be moved to POCO inclusion of OpenSSL? SDCLib
# does not include OpenSSL directly
set (OPENSSL_USE_STATIC_LIBS TRUE)

# Define minimal version
set (SDCLibrary_Minimal_OpenSSL_Version_Major          1)
set (SDCLibrary_Minimal_OpenSSL_Version_Minor          0)
set (SDCLibrary_Minimal_OpenSSL_Version_Fix            1)
set (SDCLibrary_Minimal_OpenSSL_Version_Patch          3)
set (SDCLibrary_Minimal_OpenSSL_Version_Patch_Char     "b")

# Check, if package exists (normally done by POCO)
find_package(OpenSSL REQUIRED)
if(NOT OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found!")
else ()
    
    message(STATUS "Found OpenSSL version ${OPENSSL_VERSION}")

    # Build substrings containing the version level information
    string(SUBSTRING ${OPENSSL_VERSION} 0 1 MAJOR_VERSION)
    string(SUBSTRING ${OPENSSL_VERSION} 2 1 MINOR_VERSION)
    string(SUBSTRING ${OPENSSL_VERSION} 4 1 FIX_VERSION)
    string(SUBSTRING ${OPENSSL_VERSION} 5 1 PATCH_VERSION)
  
    # Version check. If major release is smaller than allowed, leave the build. If version is 
    # equal to the minimal, proceed to check of minor version. Continue for the other levels
    # accordingly
    string(COMPARE LESS "${MAJOR_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Major}" MAJOR_TOO_LOW)
    if(${MAJOR_TOO_LOW})
        message (FATAL_ERROR "OpenSSL is too old. Expected version ${SDCLibrary_Minimal_OpenSSL_Version_Major}.${SDCLibrary_Minimal_OpenSSL_Version_Minor}.${SDCLibrary_Minimal_OpenSSL_Version_Fix}${SDCLibrary_Minimal_OpenSSL_Version_Patch_Char}. Aborting") 
    endif()
    string(COMPARE EQUAL "${MAJOR_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Major}" MAJOR_EQUAL)

    if(${MAJOR_EQUAL})
        # Check minor 
        string(COMPARE LESS "${MAJOR_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Minor}" MINOR_TOO_LOW)
        if(${MINOR_TOO_LOW})
            message (FATAL_ERROR "OpenSSL is too old. Expected version ${SDCLibrary_Minimal_OpenSSL_Version_Major}.${SDCLibrary_Minimal_OpenSSL_Version_Minor}.${SDCLibrary_Minimal_OpenSSL_Version_Fix}${SDCLibrary_Minimal_OpenSSL_Version_Patch_Char}. Aborting")
        endif()
        string(COMPARE EQUAL "${MINOR_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Minor}" MINOR_EQUAL)            
        if(${MINOR_EQUAL})
            # Check Fix
            string(COMPARE LESS "${FIX_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Fix}" FIX_TOO_LOW)
            if(${MAJOR_TOO_LOW})
                message (FATAL_ERROR "OpenSSL is too old. Expected version ${SDCLibrary_Minimal_OpenSSL_Version_Major}.${SDCLibrary_Minimal_OpenSSL_Version_Minor}.${SDCLibrary_Minimal_OpenSSL_Version_Fix}${SDCLibrary_Minimal_OpenSSL_Version_Patch_Char}. Aborting")
            endif()
            string(COMPARE EQUAL "${FIX_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Fix}" FIX_EQUAL)
            if(${FIX_EQUAL})
                string(COMPARE LESS "${PATCH_VERSION}" "${SDCLibrary_Minimal_OpenSSL_Version_Patch_Char}" PATCH_TOO_LOW)
                if(${PATCH_TOO_LOW}) 
                    message (FATAL_ERROR "OpenSSL is too old. Expected version ${SDCLibrary_Minimal_OpenSSL_Version_Major}.${SDCLibrary_Minimal_OpenSSL_Version_Minor}.${SDCLibrary_Minimal_OpenSSL_Version_Fix}${SDCLibrary_Minimal_OpenSSL_Version_Patch_Char}. Aborting")
                endif()
            endif() 
        endif()
    endif()   
endif()



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
# Doxygen config
# Note: Make sure all values are set before doing this!
################################################################################
# configure
message(STATUS "Configuring Doxygen files...")
get_filename_component(SDC_PATH_DOXYGEN ${CMAKE_CURRENT_LIST_DIR}/doc/Doxygen REALPATH)
configure_file(${SDC_PATH_DOXYGEN}/Doxyfile.in ${SDC_PATH_DOXYGEN}/Doxyfile)
configure_file(${SDC_PATH_DOXYGEN}/Mainpage.h.in ${SDC_PATH_DOXYGEN}/Mainpage.h)
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
