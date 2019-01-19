# -*- cmake -*-


# NOTE: TEMPORARY WORK! ONLY FOR THIS GIT REPO!
#       PATH_SDC_BUILD must be defined first!

# - Find SDCLib
# Find the SDCLib includes and libraries
# This module defines PATH_SDC_ROOT, PATH_SDC_INCLUDES, SDCLib and SDC_FOUND

################################################################################
# Here we have to add a few pathes to get it working
# cause is the structure of the project that makes out of source builds and
# git submodules a little troublesome
################################################################################


# Find the root folder inside the dependencies - This script is inside it!

# Just search for this file in the SDC Root folder
find_path(PATH_SDC_ROOT FindSDCLib.cmake ${PATH_SDC_SEARCH})
message(STATUS "Searching for SDCLib files in ${PATH_SDC_SEARCH}")

# Already found!
if(SDC_FOUND)
    RETURN()
endif()

# Init Flag to false
set(SDC_FOUND FALSE)

# Found?
if (PATH_SDC_ROOT)
    message(STATUS "-Found SDC Root Folder!")
else ()
    message(STATUS "Please specify PATH_SDC_SEARCH Variable!")
    RETURN()
endif ()

# Found both: Set include dirs and lib
if (PATH_SDC_ROOT)
#
    set(PATH_SDC_INCLUDES   ${PATH_SDC_ROOT}/include
                            # OSCLib
                            ${PATH_SDC_ROOT}/include/OSCLib
                            ${PATH_SDC_ROOT}/include/OSCLib/Data/SDC
                            ${PATH_SDC_ROOT}/include/OSCLib/Data/SDC/MDIB
                            ${PATH_SDC_ROOT}/include/OSCLib/Data/SDC/MDIB/custom
                            ${PATH_SDC_ROOT}/include/OSCLib/Dev
                            ${PATH_SDC_ROOT}/include/OSCLib/Util
                            # OSELib
                            ${PATH_SDC_ROOT}/include/OSELib
                            ${PATH_SDC_ROOT}/include/DPWS
                            ${PATH_SDC_ROOT}/include/Helper
                            ${PATH_SDC_ROOT}/include/HTTP
                            ${PATH_SDC_ROOT}/include/SDC
                            ${PATH_SDC_ROOT}/include/SOAP
                            ${PATH_SDC_ROOT}/include/WSDL
                            # Poco
                            ${PATH_SDC_ROOT}/Dependencies/Poco/Foundation/include/
                            ${PATH_SDC_ROOT}/Dependencies/Poco/Net/include/
                            # tclap
                            ${PATH_SDC_ROOT}/include/tclap
                            # datamodel
                            ${PATH_SDC_ROOT}/datamodel/generated
    )

    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        # Set the library based on build type
        if(CMAKE_BUILD_TYPE)
            if(CMAKE_BUILD_TYPE STREQUAL "Release")
                set(SDCLib ${PATH_SDC_BUILD}/bin/libSDCLib.so)
            else()
                set(SDCLib ${PATH_SDC_BUILD}/bin/libSDCLib_d.so)
            endif()
        else()
            message(STATUS "Trying to determine SDCLib type, but no build type specified yet. Specify one first, before calling findSDCLib!")
        endif()
        # Append Xerces - quick hack - remove this for cleaner resource management later
        list(APPEND SDCLib ${XercesLibrary})

        ################################################################################
        # XERCES - qnd
        # Note: Dependency - Just for convenience (bad style!)
        #       Adding SDCLib as shared lib, we need xerces too
        #       As quick hack, append it to the SDCLib variable
        ################################################################################
        find_library(XercesLibrary NAMES xerces-c REQUIRED)
        ################################################################################


        # Set Flag
        set(SDC_FOUND TRUE)
        message(STATUS "-SDC_FOUND !")
    else()
        message(STATUS "TODO...")
    endif()
else()
    message(STATUS "Failed...")
endif()


################################################################################
