# Current Target
# You just need to copy this file, change this name and edit the target_sources
#################################################################
set( CURRENT_TARGET_NAME Dummy1 )
#################################################################

# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")
add_executable(${CURRENT_TARGET_NAME} "")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

#################################################################
# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/main.cpp
        # ...
        # [Recommended] Add the includes too
        # ...
        # [Recommended] Private Headers
        # ...
)
#################################################################


# Make sure this include dir can be found inside the project to include
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${SRC_DIR})
# Additional include directories
# ...

# "Link" the Current target to the SDCLib.
# NOTE: CMake will handle all dependencies that are set to PUBLIC, including include files,
#       required libraries to link against etc.
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_LIBRARIES})


# Some properties (These variables are set in the top level CMakeLists file)
set_target_properties(  ${CURRENT_TARGET_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT} # Executables
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT} # Shared Libraries (*.dll / *.so)
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT} # *.lib files
                        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
                        )

# NOTE: Distinguish between "Install" and "Building" (See cmake documentation for further detail)
install(TARGETS ${CURRENT_TARGET_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE} RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME})

# ...

