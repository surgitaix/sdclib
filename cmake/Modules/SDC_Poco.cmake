# -*- cmake -*-


# NOTE: TEMPORARY WORK! WIP!

# - Find Poco
# Needs POCO_SEARCH_DIRS set.
# Highly customized to meet the need to build the SDCLib.
################################################################################

################################################################################
# Already found!
if(POCO_FOUND)
    RETURN()
endif()
################################################################################


# Set Variable POCO_SEARCH_DIRS!
if(NOT POCO_SEARCH_DIRS)
    message(FATAL_ERROR "Please set POCO_SEARCH_DIRS Variable to Poco root folder! Hint: <SDCLibROOT>/Dependencies/Poco")
endif()


message(STATUS "######## Searching for Poco...")
set(POCO_INCLUDE_DIRS
                        ${POCO_SEARCH_DIRS}/Foundation/include/
                        ${POCO_SEARCH_DIRS}/Net/include/
                        ${POCO_SEARCH_DIRS}/Crypto/include/
                        ${POCO_SEARCH_DIRS}/Util/include/
                        )

#target_link_libraries(${CURRENT_TARGET_NAME} ${POCO_LIBRARIES})
set(POCO_LIBRARIES Foundation Net Crypto Util)
# target_compile_definitions(${CURRENT_TARGET_NAME} ${POCO_EXPORTS})
set(POCO_COMPILE_DEFINITIONS POCO_NO_AUTOMATIC_LIBS Foundation_EXPORTS Net_EXPORTS Crypto_EXPORTS)

# System dependend
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND POCO_INCLUDE_DIRS ${POCO_SEARCH_DIRS}/NetSSL_OpenSSL/include/)
    list(APPEND POCO_LIBRARIES NetSSL)
    list(APPEND POCO_COMPILE_DEFINITIONS NetSSL_EXPORTS)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    list(APPEND POCO_INCLUDE_DIRS ${POCO_SEARCH_DIRS}/NetSSL_Win/include/)
    list(APPEND POCO_LIBRARIES NetSSL_Win)
    list(APPEND POCO_COMPILE_DEFINITIONS NetSSL_Win_EXPORTS)
endif()


message(STATUS "### Configuring Poco...")
add_subdirectory(${POCO_SEARCH_DIRS})
message(STATUS "### Configuring Poco done!")


# Set FOUND - Flag
set(POCO_FOUND TRUE)
