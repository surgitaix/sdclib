# -*- cmake -*-


# NOTE: TEMPORARY WORK! WIP!

# - Find Xerces (Note: Different from FindXercesC !)
# Under Linux this module calls FindXercesC!
# Under Windows a custom implementation is used!
# Still using the FindXercesC variables
################################################################################

################################################################################
# Already found!
if(XercesC_FOUND)
    RETURN()
endif()
################################################################################


IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Call the default FindXercesC script
    find_package(XercesC REQUIRED)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 

    # By default -> Use the Xerces version installed with XSD
    # Searching for the corresponding files

    # Only if not already set! -> We dont want to override this
    if(NOT XSD_ROOT)
        set(XSD_ROOT "C:\\Program Files (x86)\\CodeSynthesis XSD 4.0" CACHE PATH "Path where CodeSynthesis XSD is installed.")
    endif()

    # INCLUDE
    set(XercesC_DEFAULT_INCLUDE_DIR ${XSD_ROOT}\\include\\ CACHE PATH "Manual XercesC include dir. NOTE: Set it manually if autodetection does not work.")
    if(NOT EXISTS "${XercesC_DEFAULT_INCLUDE_DIR}")
        message(FATAL_ERROR "XercesC_DEFAULT_INCLUDE_DIR DOES NOT EXIST! Please set it manually and reconfigure!")
    endif()
    # ADD TO CMAKE SEARCH PATH
    list(APPEND CMAKE_PREFIX_PATH ${XercesC_DEFAULT_LIB_DIR})


    # LIB
    # Check on x64 (or empty -> defaults to x64)
    set(BIN_DIR bin)
    set(LIB_DIR lib)
    if("${CMAKE_GENERATOR_PLATFORM}" MATCHES "(x64|)")
        set(LIB_DIR lib64)
        set(BIN_DIR bin64)
    endif()
    ################################################################################
    # NOTE: This is just a quick fix! Set it to current maximum for auto detection.
    ################################################################################
    set(DEFAULT_LIB_DIR "vc-12.0")
    ################################################################################

    set(XercesC_DEFAULT_LIB_DIR "${XSD_ROOT}\\${LIB_DIR}\\${DEFAULT_LIB_DIR}\\" CACHE PATH "Manual XercesC lib dir. NOTE: Set it manually if autodetection does not work.")
    if(NOT EXISTS "${XercesC_DEFAULT_LIB_DIR}")
        message(FATAL_ERROR "XercesC_DEFAULT_LIB_DIR DOES NOT EXIST! Please set it manually and reconfigure!")
    endif()
    # ADD TO CMAKE SEARCH PATH
    list(APPEND CMAKE_PREFIX_PATH ${XercesC_DEFAULT_LIB_DIR})

    # Use the default script to set all necessary variables
    find_package(XercesC REQUIRED)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
