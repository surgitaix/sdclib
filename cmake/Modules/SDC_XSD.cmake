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
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Not needed when installed under MacOS.
    # Set FOUND - Flag
    set(XSD_FOUND TRUE)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 

    # By default -> Use the Xerces version installed with XSD
    # Searching for the corresponding files

    # Only if not already set! -> We dont want to override this
    if(NOT XSD_ROOT)
        set(XSD_ROOT "C:\\Program Files (x86)\\CodeSynthesis XSD 4.0" CACHE PATH "Path where CodeSynthesis XSD is installed." FORCE)
    endif()

    # INCLUDE
    set(XSD_INCLUDE_DIRS ${XSD_ROOT}\\include\\ CACHE PATH "Manual XSD include dir. NOTE: Set it manually if autodetection does not work." FORCE)
    if(NOT EXISTS "${XSD_INCLUDE_DIRS}")
        message(FATAL_ERROR "XSD_ROOT DOES NOT EXIST! Please set it manually and reconfigure!")
    endif()

    # Set FOUND - Flag
    set(XSD_FOUND TRUE)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
