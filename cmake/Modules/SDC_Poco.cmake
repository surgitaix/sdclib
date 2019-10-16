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
                        ${POCO_SEARCH_DIRS}/NetSSL_OpenSSL/include/
                        ${POCO_SEARCH_DIRS}/Crypto/include/
                        ${POCO_SEARCH_DIRS}/Util/include/
                        )

#target_link_libraries(${CURRENT_TARGET_NAME} ${POCO_LIBRARIES})
set(POCO_LIBRARIES Foundation Net NetSSL Crypto Util)
# target_compile_definitions(${CURRENT_TARGET_NAME} ${POCO_EXPORTS})
set(POCO_COMPILE_DEFINITIONS POCO_NO_AUTOMATIC_LIBS $<$<CXX_COMPILER_ID:MSVC>:Foundation_EXPORTS Net_EXPORTS NetSSL_EXPORTS Crypto_EXPORTS>)

message(STATUS "### Configuring Poco...")
add_subdirectory(${POCO_SEARCH_DIRS})
message(STATUS "### Configuring Poco done!")

# Set FOUND - Flag
set(POCO_FOUND TRUE)
