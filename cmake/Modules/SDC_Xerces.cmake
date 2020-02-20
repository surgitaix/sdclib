# -*- cmake -*-

# - SDC custom to find Xerces
# Linux: Forward to FindXercesC!
# Windows:  Set some variables to help tthe find script. Call the script to set
#           all remaining variables.
################################################################################

################################################################################
# Already found!
if(XercesC_FOUND)
    RETURN()
endif()
################################################################################


################################################################################
# Linux
################################################################################
IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Call the default FindXercesC script
    find_package(XercesC REQUIRED)
ENDIF()
################################################################################

################################################################################
# Windows
#
# Note: Make sure to build xerces-c first. See README inside Dependencies/xerces-c folder for further information.
################################################################################
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 

	set(Xerces_ROOT ${SDCLib_ROOT_DIR}\\Dependencies\\xerces-c\\xerces-c)

	set(XercesC_DEFAULT_INCLUDE_DIR ${Xerces_ROOT}\\src\\ CACHE PATH "Manual XercesC include dir. NOTE: Set it manually if autodetection does not work." FORCE)
	if(NOT EXISTS "${XercesC_DEFAULT_INCLUDE_DIR}")
		message(FATAL_ERROR "XercesC_DEFAULT_INCLUDE_DIR (${XercesC_DEFAULT_INCLUDE_DIR})DOES NOT EXIST! Please set it manually and reconfigure!")
	endif()
	# ADD TO CMAKE SEARCH PATH
	list(APPEND CMAKE_PREFIX_PATH ${XercesC_DEFAULT_INCLUDE_DIR})

	set(XercesC_DEFAULT_LIB_DIR "${XercesC_DEFAULT_INCLUDE_DIR}\\${CMAKE_BUILD_TYPE}\\" CACHE PATH "Manual XercesC lib dir. NOTE: Set it manually if autodetection does not work." FORCE)
    if(NOT EXISTS "${XercesC_DEFAULT_LIB_DIR}")
        message(FATAL_ERROR "XercesC_DEFAULT_LIB_DIR DOES NOT EXIST! Please set it manually and reconfigure!")
    endif()

    # ADD TO CMAKE SEARCH PATH
    list(APPEND CMAKE_PREFIX_PATH ${XercesC_DEFAULT_LIB_DIR})

    # Use the default script to set all necessary variables
    find_package(XercesC REQUIRED)

ENDIF()
################################################################################