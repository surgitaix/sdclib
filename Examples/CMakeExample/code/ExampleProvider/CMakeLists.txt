# Current Target
set( CURRENT_TARGET_NAME ExampleProvider )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")
add_executable(${CURRENT_TARGET_NAME} "")

# Variables for better handling
set(SRC_DIR ${SDCLib_ROOT_DIR}/Examples/ExampleProvider/)

# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/ExampleProvider.cpp
        # ...
        # [Recommended] Add the includes too
        # ...
        # [Recommended] Private Headers
        # ...
)



# Make sure this include dir can be found inside the project to include
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${SRC_DIR})
# Additional include directories
# ...

# Add SDCLib Include Directories and Link to it
target_include_directories(${CURRENT_TARGET_NAME} PRIVATE ${SDCLib_INCLUDE_DIRS})
target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE ${SDCLib_LIBRARIES})


# Some properties (These variables are set in the top level CMakeLists file)
set_target_properties(  ${CURRENT_TARGET_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT} # Executables
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT} # Shared Libraries (*.dll / *.so)
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT} # *.lib files
                        DEBUG_POSTFIX ${DEBUG_POSTFIX_OUTPUT}
                        )

# NOTE: Distinguish between "Install" and "Building" (See cmake documentation for further detail)
install(TARGETS ${CURRENT_TARGET_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE} RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME})

# ...

