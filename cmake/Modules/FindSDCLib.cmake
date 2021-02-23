# -*- cmake -*-


# NOTE: TEMPORARY WORK! WIP!
# SDCLib_SEARCH_DIRS (Optional) -> Will be set to CMAKE_SOURCE_DIR if not set
# You can provide SDCLib_EXTERNAL_LIBRARY_DIRS to specify an external binary dir

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

	# Determin the subdirectory
	set(Library_Subdir lib)
	if(SDCLib_DYNAMIC_LINKING)
		set(Library_Subdir bin)
	endif()

    message(STATUS "-Found SDC Root Folder: ${SDCLib_ROOT_DIR}!")
    if(DEFINED SDCLib_EXTERNAL_LIBRARY_DIRS) 								# OVERRIDE: SDCLib_EXTERNAL_LIBRARY_DIRS
		message(STATUS "-Using SDCLib_EXTERNAL_LIBRARY_DIRS!")
		message(STATUS "-Setting ${SDCLib_EXTERNAL_LIBRARY_DIRS} to SDCLib_LIBRARY_DIRS!")
		set(SDCLib_LIBRARY_DIRS ${SDCLib_EXTERNAL_LIBRARY_DIRS})
    elseif(NOT(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR}))			# Out of source?
		message(STATUS "-Out of source build detected!")
		message(STATUS "-Setting ${CMAKE_BINARY_DIR}/${Library_Subdir} to SDCLib_LIBRARY_DIRS!")
		set(SDCLib_LIBRARY_DIRS ${CMAKE_BINARY_DIR}/${Library_Subdir})
    else() 																	# In source
        message(STATUS "-Setting ${CMAKE_SOURCE_DIR}/${Library_Subdir} to SDCLib_LIBRARY_DIRS...")
        set(SDCLib_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/${Library_Subdir})
    endif()
else ()
    message(SEND_ERROR "## Could not find SDC Root folder!")
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

set(FileExtension lib) # Default

# FIXME: Check if files are really there!
if (CMAKE_SYSTEM_NAME MATCHES "Linux")

	if(SDCLib_DYNAMIC_LINKING)
		set(FileExtension so)
	endif()

    # Set the library based on build type
    if (CMAKE_BUILD_TYPE)
        if (CMAKE_BUILD_TYPE STREQUAL "Release")
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/libSDCLib${CMAKE_RELEASE_POSTFIX}.${FileExtension})
        else()
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/libSDCLib${CMAKE_DEBUG_POSTFIX}.${FileExtension})
        endif()
    else()
        message(SEND_ERROR "Trying to determine SDCLib type, but no build type specified yet. Specify one first, before calling findSDCLib!")
        RETURN()
    endif()
endif()

# FIXME: Check if files are there!
if (CMAKE_SYSTEM_NAME MATCHES "Windows")

	if(SDCLib_DYNAMIC_LINKING)
		set(FileExtension dll)
	endif()

    # Set the library based on build type
    if(NOT CMAKE_BUILD_TYPE)
		message(WARNING "No build Type specified in CMAKE_BUILD_TYPE. Setting to Release.")
		set(CMAKE_BUILD_TYPE "Release")
	endif()
    if(CMAKE_BUILD_TYPE)
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/SDCLib${CMAKE_RELEASE_POSTFIX}.${FileExtension})
        else()
            set(SDCLib_LIBRARIES ${SDCLib_SEARCH_LIB}/SDCLib${CMAKE_DEBUG_POSTFIX}.${FileExtension})
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
# Support for UTF8 with MSVC
list(APPEND SDCLib_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
# Debug Flags
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-ggdb -g>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>>:-ggdb -g>)
# Warnings
list(APPEND SDCLib_OPTIONS $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic>)
list(APPEND SDCLib_OPTIONS $<$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>:-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic>)
list(APPEND SDCLib_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:/W4>)
# Optimization
# (Release)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O3>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>>:-O3>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>)
# (Debug)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O0>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:ARMCC>,$<CXX_COMPILER_ID:ARMClang>>>:-O0>)
list(APPEND SDCLib_OPTIONS $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Od>)
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
# explicitly link atomic -> Needed to build on ARM / ignored on linux / no need on windows
if (NOT (CMAKE_SYSTEM_NAME MATCHES "Windows"))
	list(APPEND SDCLib_DEPS_LIBRARIES atomic)
endif()
################################################################################

################################################################################
# Other Dependencies
# - OpenSSL
# - XercesC
# - Poco
# - XSD
################################################################################
#
#
#


################################################################################
# OpenSSL - Version Check
# Note: Must be placed here in order to be added to the config file. Patch
# version is set to a number, where (1 = a, 2 = b, ...)
# In the following, the variables for the supported OpenSSL minimal version are
# defined. The OpenSSL version is defined by major version, minor, fix, patch
# and a status (release / development, ...)
################################################################################



################################################################################
# Enable static build of OpenSSL
# Taken from https://cmake.org/cmake/help/v3.4/module/FindOpenSSL.html#hints
# TODO: Required here? Or should it be moved to POCO inclusion of OpenSSL? SDCLib
# does not include OpenSSL directly
################################################################################
set (OPENSSL_USE_STATIC_LIBS FALSE)

# Define minimal version
set (SDCLibrary_Minimal_OpenSSL_Version_Major          1)
set (SDCLibrary_Minimal_OpenSSL_Version_Minor          0)
set (SDCLibrary_Minimal_OpenSSL_Version_Fix            1)
set (SDCLibrary_Minimal_OpenSSL_Version_Patch          3)
set (SDCLibrary_Minimal_OpenSSL_Version_Patch_Char     "b")
mark_as_advanced(SDCLibrary_Minimal_OpenSSL_Version_Major)
mark_as_advanced(SDCLibrary_Minimal_OpenSSL_Version_Minor)
mark_as_advanced(SDCLibrary_Minimal_OpenSSL_Version_Fix)
mark_as_advanced(SDCLibrary_Minimal_OpenSSL_Version_Patch)
mark_as_advanced(SDCLibrary_Minimal_OpenSSL_Version_Patch_Char)


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

	# Add to Deps
	list(APPEND SDCLib_INCLUDE_DIRS ${OPENSSL_INCLUDE_DIR})
	list(APPEND SDCLib_DEPS_LIBRARIES ${OPENSSL_SSL_LIBRARY})

endif()
################################################################################



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

list(APPEND SDCLib_DEPS_INCLUDE_DIRS ${XercesC_INCLUDE_DIR})


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
message(STATUS "-Looking for XSD...")
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
