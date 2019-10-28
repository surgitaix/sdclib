# -*- cmake -*-


# NOTE: TEMPORARY WORK! WIP!
# SDCLib_SEARCH_DIRS (Optional) -> Will be set to CMAKE_SOURCE_DIR if not set

# - Find SDCLib
# Find the SDCLib includes and libraries
# This module defines:
# SDCLib_ROOT_DIR, SDCLib_INCLUDE_DIRS, SDCLib_DEFINITIONS, SDCLib_OPTIONS, SDCLib_LIBRARY_DIRS, SDCLib_FOUND

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
################################################################################


################################################################################
# If not specified: Search in CMAKE_SOURCE_DIR
if (NOT SDCLib_SEARCH_DIRS)
	set(SDCLib_SEARCH_DIRS ${CMAKE_SOURCE_DIR})
endif()
################################################################################


################################################################################
# Find the root folder inside the dependencies - This script is inside it!
# Just search for this file in the SDC Root folder
find_path(SDCLib_ROOT_DIR cmake/Modules/FindSDCLib.cmake ${SDCLib_SEARCH_DIRS})
message(STATUS "Searching for SDCLib in ${CMAKE_SOURCE_DIR} ...")

# Found?
# Set Bin folder and manage library dirs
if (SDCLib_ROOT_DIR)
    message(STATUS "-Found SDC Root Folder: ${SDCLib_ROOT_DIR}!")
    # Out of source?
    if (NOT(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR}))
		message(STATUS "-Out of source build detected!")
		if(SDCLib_ADDITIONAL_LIBRARY_DIRS)
			message(STATUS "Using SDCLib_ADDITIONAL_LIBRARY_DIRS!")
			message(STATUS "Setting ${SDCLib_ADDITIONAL_LIBRARY_DIRS} to SDCLib_LIBRARY_DIRS!")
			set(SDCLib_LIBRARY_DIRS ${SDCLib_ADDITIONAL_LIBRARY_DIRS})
		else()
			message(STATUS "Setting ${CMAKE_BINARY_DIR} to SDCLib_LIBRARY_DIRS!")
			set(SDCLib_LIBRARY_DIRS ${CMAKE_BINARY_DIR})
		endif()
    else()
        message(STATUS "-Setting ${CMAKE_SOURCE_DIR}/bin to SDCLib_LIBRARY_DIRS...")
        set(SDCLib_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/bin)
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
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/libSDCLib${CMAKE_RELEASE_POSTFIX}.so)
        else()
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


################################################################################
# Compile Definitions
################################################################################
list(APPEND SDCLib_DEFINITIONS $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:linux _LINUX >)
list(APPEND SDCLib_DEFINITIONS $<$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>:linux _LINUX>)
list(APPEND SDCLib_DEFINITIONS $<$<CXX_COMPILER_ID:MSVC>:_WIN32>)
################################################################################


################################################################################
# Compile Options
################################################################################
# Debug Flags
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-ggdb -g>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>>:-ggdb -g>)
# Warnings
list(APPEND SDCLib_OPTIONS $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>)
list(APPEND SDCLib_OPTIONS $<$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>:-Wall -Wextra -pedantic>)
list(APPEND SDCLib_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:/W4>)
# Optimization
# (Release)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O3>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>>:-O3>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>)
# (Debug)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O0>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>>:-O0>)
# list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/O0>) ?
################################################################################



################################################################################
# Search for given libary file
################################################################################
# Not Found
message(STATUS "-Searching for SDCLib file (${SDCLib_LIBRARIES}) ...")
if (NOT EXISTS ${SDCLib_LIBRARIES})
    message("  Could not find ${SDCLib_LIBRARIES}!")
else()
    message(STATUS "  -- FOUND SDCLib (${SDCLib_LIBRARIES})!")
endif()

################################################################################


################################################################################
# Note: This script will also gather SDCLib dependencies inside the given
#       variables for better handling.
################################################################################
# explicitly link atomic -> Needed to build on ARM
list(APPEND SDCLib_DEPS_LIBRARIES atomic)
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
include(SDC_Xerces) # This adds an imported target WIP

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
include(SDC_Poco)

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
include(SDC_XSD)

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
