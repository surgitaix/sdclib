# -*- cmake -*-


# NOTE: TEMPORARY WORK! WIP!

# - Find XSD include dir
# XSD_ROOT needs to be set!
# Under Linux this module does nothing.
# Under Windows it sets XSD_INCLUDE_DIR
# Still using the FindXercesC variables
################################################################################

################################################################################
# Already found!
if(XSD_FOUND)
    RETURN()
endif()
################################################################################

# Create an empty Variable
set(XSD_INCLUDE_DIRS "")

# Note: WIP!
IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Not needed when installed under Linux.
    # Set FOUND - Flag
    set(XSD_FOUND TRUE)
ENDIF()

IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 

	set(XSD_ROOT ${SDCLib_ROOT_DIR}\\Dependencies\\xsd\\xsd-4.0.0-i686-windows)
	if(NOT EXISTS "${XSD_ROOT}")
		message(FATAL_ERROR "XSD_ROOT (${XSD_ROOT})DOES NOT EXIST! Please set it manually and reconfigure!")
	endif()

    # INCLUDE
    set(XSD_INCLUDE_DIRS ${XSD_ROOT}\\libxsd CACHE PATH "Manual XSD include dir. NOTE: Set it manually if autodetection does not work." FORCE)
    if(NOT EXISTS "${XSD_INCLUDE_DIRS}")
        message(FATAL_ERROR "XSD_INCLUDE_DIRS DOES NOT EXIST! Please set it manually and reconfigure!")
    endif()

	message(STATUS "Found XSD: ${XSD_INCLUDE_DIRS}")
    # Set FOUND - Flag
    set(XSD_FOUND TRUE)

ENDIF()