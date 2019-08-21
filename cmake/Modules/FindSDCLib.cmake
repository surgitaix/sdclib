# -*- cmake -*-


# NOTE: TEMPORARY WORK! WIP!
#       SDCLib_SEARCH_DIRS must be defined first!
#       Building out of source specify SDCLib_ADDITIONAL_LIBRARY_DIRS

# - Find SDCLib
# Find the SDCLib includes and libraries
# This module defines:
# SDCLib_ROOT_DIR, SDCLib_INCLUDE_DIRS, SDCLib_DEFINITIONS, SDCLib_LIBRARY_DIRS, SDCLib_FOUND

################################################################################
# Here we have to add a few pathes to get it working
# cause is the structure of the project that makes out of source builds and
# git submodules a little troublesome
################################################################################

################################################################################
# Already found!
if(SDCLib_FOUND)
    RETURN()
endif()

# Init Flag to false
set(SDCLib_FOUND FALSE)
#
# Set other variables
set(SDCLib_LIBRARIES            "")
set(SDCLib_INCLUDE_DIRS         "")
set(SDCLib_DEFINITIONS          "")
set(SDCLib_OPTIONS              "")
# Dependencies
set(SDCLib_DEPS_LIBRARIES       "")
set(SDCLib_DEPS_INCLUDE_DIRS    "")
set(SDCLib_DEPS_DEFINITIONS     "")



################################################################################


################################################################################
# Check if necessary variables have been specified
if (NOT SDCLib_SEARCH_DIRS)
    message(FATAL_ERROR "PLEASE SPECIFY SDCLib_SEARCH_DIRS!")
    RETURN()
endif()
################################################################################




################################################################################
# Find the root folder inside the dependencies - This script is inside it!
# Just search for this file in the SDC Root folder
find_path(SDCLib_ROOT_DIR cmake/Modules/FindSDCLib.cmake ${SDCLib_SEARCH_DIRS})
message(STATUS "-Searching for SDCLib files in ${SDCLib_SEARCH_DIRS}")

# Found?
# Set Bin folder and manage library dirs
if (SDCLib_ROOT_DIR)
    message(STATUS "-Found SDC Root Folder: ${SDCLib_ROOT_DIR}!")
    # Additional Library Dirs?
    if (SDCLib_ADDITIONAL_LIBRARY_DIRS)
        message(STATUS "-Detected SDCLib_ADDITIONAL_LIBRARY_DIRS!")
        message(STATUS "-Adding ${SDCLib_ADDITIONAL_LIBRARY_DIRS} to SDCLib_LIBRARY_DIRS...")
        set(SDCLib_LIBRARY_DIRS ${SDCLib_ADDITIONAL_LIBRARY_DIRS})
    else()
        message(STATUS "-Adding ${SDCLib_ROOT_DIR} to SDCLib_LIBRARY_DIRS...")
        set(SDCLib_LIBRARY_DIRS ${SDCLib_ROOT_DIR})
    endif()
else ()
    message(SEND_ERROR "Could not find SDC Root folder!")
    RETURN()
endif ()
################################################################################



################################################################################
# Includes SDCLib_INCLUDE_DIRS
message(STATUS "-Adding SDC Include Files...")
################################################################################

set(SDCLib_INCLUDE_DIRS     ${SDCLib_ROOT_DIR}/include
                            # SDCLib
                            ${SDCLib_ROOT_DIR}/include/SDCLib
                            ${SDCLib_ROOT_DIR}/include/SDCLib/Data/SDC
                            ${SDCLib_ROOT_DIR}/include/SDCLib/Data/SDC/MDIB
                            ${SDCLib_ROOT_DIR}/include/SDCLib/Data/SDC/MDIB/custom
                            ${SDCLib_ROOT_DIR}/include/SDCLib/Dev
                            ${SDCLib_ROOT_DIR}/include/SDCLib/Util
                            # OSELib
                            ${SDCLib_ROOT_DIR}/include/OSELib
                            ${SDCLib_ROOT_DIR}/include/DPWS
                            ${SDCLib_ROOT_DIR}/include/Helper
                            ${SDCLib_ROOT_DIR}/include/HTTP
                            ${SDCLib_ROOT_DIR}/include/SDC
                            ${SDCLib_ROOT_DIR}/include/SOAP
                            ${SDCLib_ROOT_DIR}/include/WSDL
                            # Poco
                            ${SDCLib_ROOT_DIR}/Dependencies/Poco/Foundation/include/
                            ${SDCLib_ROOT_DIR}/Dependencies/Poco/Net/include/
                            # datamodel
                            ${SDCLib_ROOT_DIR}/datamodel/generated
)
################################################################################



################################################################################
# Clear the given path of all symlinks
get_filename_component(SDCLib_SEARCH_LIB ${SDCLib_LIBRARY_DIRS} REALPATH)
################################################################################
# Platform specific Parameters
#
# FIXME: Check if files are really there!
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Set the library based on build type
    if (CMAKE_BUILD_TYPE)
        if (CMAKE_BUILD_TYPE STREQUAL "Release")
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/libSDCLib.so)
        else()
            # Not set? Specify a default
            if (NOT CMAKE_DEBUG_POSTFIX)
                set(CMAKE_DEBUG_POSTFIX _d)
                message(STATUS "No Debug Postfix set. Setting to ${CMAKE_DEBUG_POSTFIX}!")
            endif()
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/libSDCLib${CMAKE_DEBUG_POSTFIX}.so)
        endif()
    else()
        message(SEND_ERROR "Trying to determine SDCLib type, but no build type specified yet. Specify one first, before calling findSDCLib!")
        RETURN()
    endif()
endif()

# FIXME: Check if files are there!
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Set the library based on build type
    if(NOT CMAKE_BUILD_TYPE)
		message(WARNING "No build Type specified in CMAKE_BUILD_TYPE. Setting to Release.")
		set(CMAKE_BUILD_TYPE "Release")
	endif()
    if(CMAKE_BUILD_TYPE)
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/SDCLib${CMAKE_RELEASE_POSTFIX}.lib)
        else()
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/SDCLib${CMAKE_DEBUG_POSTFIX}.lib)
        endif()
    else()
        message(SEND_ERROR "Trying to determine SDCLib type, but no build type specified yet. Specify one first, before calling findSDCLib!")
        RETURN()
    endif()
endif()

################################################################################
# Compile Definitions
################################################################################

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND SDCLib_DEFINITIONS -D_LINUX)
    list(APPEND SDCLib_DEFINITIONS -Dlinux)
endif()


if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    list(APPEND SDCLib_DEFINITIONS -D_WIN32)
endif()


################################################################################
# Compile Options
################################################################################
if(CMAKE_BUILD_TYPE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
			# Only if under Linux
			if(CMAKE_SYSTEM_NAME MATCHES "Linux")
			# enable debug and profiling informations for sprof
			list(APPEND SDCLib_OPTIONS -ggdb -g -O0)
        endif()
    endif()
endif()
################################################################################


################################################################################
# Search for given libary file
################################################################################
# Not Found
message(STATUS "-Searching for SDCLib file (${SDCLib_LIBRARIES}) ...")
if (NOT EXISTS ${SDCLib_LIBRARIES})
    message("  Could not find ${SDCLib_LIBRARIES}!")
    if(NOT SDCLib_ADDITIONAL_LIBRARY_DIRS)
        message("## Note: For our of source build add SDCLib_ADDITIONAL_LIBRARY_DIRS ##\n")
    endif()
else()
    message(STATUS "FOUND ${SDCLib_LIBRARIES}!")
endif()

################################################################################

################################################################################
# Note: This script will also gather SDCLib dependencies inside the given
#       variables for better handling.
################################################################################
# explicitly link atomic -> Needed to build on ARM
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
list(APPEND SDCLib_DEPS_LIBRARIES atomic)
endif()
################################################################################

################################################################################
# Other Dependencies
# - XercesC
# - Poco
# - XSD
################################################################################
#
#
#
################################################################################
# XERCESC
# Note: Dependency - Just for convenience (bad style!)
#       Adding SDCLib as shared lib, we need xerces too
#       As quick hack, append it to the SDCLib variable
################################################################################
message(STATUS "-Looking for XercesC...")
include("${CMAKE_CURRENT_LIST_DIR}/SDC_Xerces.cmake") # This adds an imported target WIP

# Found it?
if(NOT XercesC_FOUND)
	message(FATAL_ERROR "Failed to find XercesC!")
endif()

# Append Xerces
if (CMAKE_BUILD_TYPE STREQUAL Release)
    list(APPEND SDCLib_DEPS_LIBRARIES ${XercesC_LIBRARY_RELEASE})
else ()
    if(NOT XercesC_LIBRARY_DEBUG)
        message(STATUS "Could not find XercesC Debug Library, using release version!")
        list(APPEND SDCLib_DEPS_LIBRARIES ${XercesC_LIBRARY_RELEASE})
    else()
        list(APPEND SDCLib_DEPS_LIBRARIES ${XercesC_LIBRARY_DEBUG})
    endif()
endif()
################################################################################
#
#
#
################################################################################
# Poco (Some components needed)
# - Foundation
# - Net
# - Crypto
# - Util
# - NetSSL
################################################################################
set(POCO_SEARCH_DIRS ${SDCLib_ROOT_DIR}/Dependencies/Poco CACHE STRING "Poco Root folder")
include("${CMAKE_CURRENT_LIST_DIR}/SDC_Poco.cmake")

# Found it?
if(NOT POCO_FOUND)
  message(FATAL_ERROR "Failed to find Poco!")
endif()

# Append Libraries
list(APPEND SDCLib_DEPS_LIBRARIES ${POCO_LIBRARIES})

# Append Include Dirs
list(APPEND SDCLib_INCLUDE_DIRS ${POCO_INCLUDE_DIRS})
list(APPEND SDCLib_DEPS_INCLUDE_DIRS ${POCO_INCLUDE_DIRS})

# Append Compile Definitions
list(APPEND SDCLib_DEPS_DEFINITIONS ${POCO_COMPILE_DEFINITIONS})
################################################################################



################################################################################
# XSD
################################################################################
# Only Include Path needed under Windows
include("${CMAKE_CURRENT_LIST_DIR}/SDC_XSD.cmake")

# Found it?
if(NOT XSD_FOUND)
    message(FATAL_ERROR "Failed to find XSD Include! Please specify XSD_ROOT!")
endif()
list(APPEND SDCLib_DEPS_INCLUDE_DIRS ${XSD_INCLUDE_DIRS})

################################################################################

################################################################################
# Threads - prefer pthreads
################################################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
list(APPEND SDCLib_DEPS_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
################################################################################


################################################################################
# Set flag
set(SDCLib_FOUND TRUE)
################################################################################
