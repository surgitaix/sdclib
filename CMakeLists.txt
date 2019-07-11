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
set (SDCLibrary_VERSION_MIDDLE         0)
set (SDCLibrary_VERSION_LAST           3)
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

#MessageManipulation
add_definitions(-DMESSAGEMANIPULATION=1)
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
# Firewall - Allowed Ports
# Note: For the UnitTests and Examples to work, make sure in- and outbound
#       traffic on this portrange is allowed
# With ufw just run: sudo ufw allow <startport>:<endport>/tcp (or udp)
################################################################################

# Note: Just randomly took a port range that is not densly occupied from:
# https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers

set(SDC_DEFAULT_MDPWS_PORT 0 CACHE STRING "The Default Port to bind on. A value of 0 will choose any free port." FORCE)

set(SDC_ALLOWED_PORT_START 14000 CACHE STRING "Start Port of allowed port range. [Make sure your firewall settings match these value]" FORCE)
set(SDC_ALLOWED_PORT_RANGE  2000 CACHE STRING "Port Range of allowed ports as offset from the Start Port. [Make sure your firewall settings match these value]" FORCE)
set(SDC_DEFAULT_PORT_RANGE  1000 CACHE STRING "Passed default Port Range if none is specified in configuration.")

set(SDC_DEFAULT_PORT_PROVIDER 14000 CACHE STRING "Default Port to start the Example Provider." FORCE)
set(SDC_DEFAULT_PORT_CONSUMER 14001 CACHE STRING "Default Port to start the Example Consumer." FORCE)

mark_as_advanced(SDC_ALLOWED_PORT_START)
mark_as_advanced(SDC_ALLOWED_PORT_RANGE)
mark_as_advanced(SDC_DEFAULT_PORT_RANGE)
mark_as_advanced(SDC_DEFAULT_PORT_PROVIDER)
mark_as_advanced(SDC_DEFAULT_PORT_CONSUMER)

set(SDC_DISCOVERY_TIMEOUT_MS 5000 CACHE STRING "Time in milliseconds a Discovery will take." FORCE)
mark_as_advanced(SDC_DISCOVERY_TIMEOUT_MS)

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
# Threads - prefer pthreads
################################################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Use it like this in the subprojects:
#target_link_libraries(${CURRENT_TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})
################################################################################



################################################################################
# XERCES
################################################################################
find_library(XercesLibrary NAMES xerces-c REQUIRED)
################################################################################

################################################################################
# Poco
# Custom Version - only a few Components needed
# Net needed
# Foundation needed
################################################################################
message(STATUS "######## Configuring Poco...")
set(PATH_POCO_INCLUDE
                        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/Poco/Net/include/
                        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/Poco/Foundation/include/
                        )

set(POCO_LIBRARIES Net Foundation)
#target_link_libraries(${CURRENT_MODULE_NAME} ${POCO_LIBRARIES})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Dependencies/Poco/)
message(STATUS "######## Configuring Poco done!")
################################################################################

################################################################################
#Asio
################################################################################
message(STATUS "###### Configure Asio...")
get_filename_component(PATH_ASIO_ROOT ${CMAKE_CURRENT_LIST_DIR}/Dependencies/asio/include REALPATH)
include_directories(${PATH_ASIO_ROOT})
add_definitions(-DASIO_STANDALONE)
message(STATUS "######## Configuring Asio done!")

################################################################################
#OPENSSL
#Needed for SHA1 
################################################################################
message(STATUS "##### Configure Openssl...")
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
message(STATUS "######## Configuring Openssl done!")




################################################################################
# Some more paths - cleaned from symlinks
# Note: Use these in the other CMakeLists for easier handling
################################################################################
get_filename_component(PATH_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/src/ REALPATH)
get_filename_component(PATH_INCLUDE_ROOT ${CMAKE_CURRENT_LIST_DIR}/include/ REALPATH)
get_filename_component(PATH_DATAMODEL_ROOT ${CMAKE_CURRENT_LIST_DIR}/datamodel/ REALPATH)
get_filename_component(PATH_EXAMPLES_ROOT ${CMAKE_CURRENT_LIST_DIR}/Examples/ REALPATH)
get_filename_component(PATH_TESTS_ROOT ${CMAKE_CURRENT_LIST_DIR}/Tests/ REALPATH)
get_filename_component(PATH_ACS_ROOT ${CMAKE_CURRENT_LIST_DIR}/AbstractConsumerSimulator/ REALPATH)
get_filename_component(PATH_SDCTESTS_ROOT ${PATH_TESTS_ROOT}/SDCTests/ REALPATH)

################################################################################


IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux") 
    ADD_DEFINITIONS(-D_LINUX)
    ADD_DEFINITIONS(-Dlinux)
    # constexpr macro / checking for C++11 is done above allready
    # Note: Shouldnt this be fixed inside the code? - only used once as far as I can tell...!
    add_definitions(-DCONSTEXPR_MACRO=constexpr)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


# <FIXME> WINDOWS untested!
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 
    ADD_DEFINITIONS(-D_WIN32)

    # Libraries - WIP... maybe include in Dependencies?
    SET(PTHREAD_LIB_DIR "${PROJECT_SOURCE_DIR}/../pthread/lib/" CACHE PATH "Path to PTHREAD libraries.")
    SET(XERCES_LIB_DIR "${PROJECT_SOURCE_DIR}/../xerces/lib/" CACHE PATH "Path to XERCES-C libraries.")

    # XERCES [needed here? - Test!]
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        set(XERCES_LIB xerces-c_3D)
    else ()
        set(XERCES_LIB xerces-c_3)
    endif()

    # define preprocessor macros for Visual Studio: no CONSTEXPR_MACRO before VS15
    MESSAGE( STATUS "MSVS compiler version: " ${CMAKE_CXX_COMPILER_VERSION} )
    # Note: Shouldnt this be fixed inside the code? - only used once as far as I can tell...!
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.00)
        add_definitions(-DCONSTEXPR_MACRO= )
    else()
        add_definitions(-DCONSTEXPR_MACRO=constexpr)
    endif()
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


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
# Configuration Done
# Now add the subdirs
# Note: Inside the subdirs only work by including. See other files
message(STATUS "Adding Targets...")
################################################################################

# datamodel
add_subdirectory(${PATH_DATAMODEL_ROOT})
add_subdirectory(${PATH_SRC_ROOT}/OSELib/TCP)


# src folder
add_subdirectory(${PATH_SRC_ROOT})

set(SDCLib_SEARCH_DIRS ".")


# Examples
if(SDC_EXAMPLES)
    find_package(SDCLib)
    add_subdirectory(${PATH_EXAMPLES_ROOT})
endif()
# Tests
if(SDC_TESTS)
    find_package(SDCLib)
    add_subdirectory(${PATH_TESTS_ROOT})
ENDIF()
#...
