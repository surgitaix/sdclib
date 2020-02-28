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

	# Some variables...
	set(XERCES_RELEASE_DLL_NAME 	xerces-c_3_2.dll) 	# NOTE: If version ever changes: CHANGE HERE!
	set(XERCES_DEBUG_DLL_NAME 		xerces-c_3_2D.dll)  # NOTE: If version ever changes: CHANGE HERE!
	set(Xerces_ROOT ${SDCLib_ROOT_DIR}\\Dependencies\\xerces-c\\xerces-c)
	set(XercesC_DEFAULT_INCLUDE_DIR ${Xerces_ROOT}\\src\\ CACHE PATH "Manual XercesC include dir. NOTE: Set it manually if autodetection does not work." FORCE)

	set(XERCES_RELEASE_DLL 	${XercesC_DEFAULT_INCLUDE_DIR}\\Release\\${XERCES_RELEASE_DLL_NAME})
	set(XERCES_DEBUG_DLL 	${XercesC_DEFAULT_INCLUDE_DIR}\\Debug\\${XERCES_DEBUG_DLL_NAME})


	# Check if exists and append to search path to let the XercesC script find the files
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

	# FOUND? -> Copy DLLS
	if(XercesC_FOUND)
		# Release
		if(EXISTS ${XERCES_RELEASE_DLL})
			message(STATUS "Copy XercesC Release DLL (${XERCES_RELEASE_DLL_NAME}) to bin folder...")
			configure_file(${XERCES_RELEASE_DLL}	${PATH_RUNTIME_OUTPUT_ROOT}\\${XERCES_RELEASE_DLL_NAME} COPYONLY)
		endif()
		# Debug
		if(EXISTS ${XERCES_DEBUG_DLL})
			message(STATUS "Copy XercesC Debug DLL (${XERCES_DEBUG_DLL_NAME}) to bin folder...")
			configure_file(${XERCES_DEBUG_DLL}		${PATH_RUNTIME_OUTPUT_ROOT}\\${XERCES_DEBUG_DLL_NAME} COPYONLY)
		endif()
	endif()

ENDIF()
################################################################################
