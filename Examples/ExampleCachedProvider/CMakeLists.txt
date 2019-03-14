# Current Module
set( CURRENT_MODULE_NAME ExampleCachedProvider )
# Add this for better project structure after cmake generation
project(${CURRENT_MODULE_NAME})

message(STATUS "Adding Module ${CURRENT_MODULE_NAME}...")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})


# Add the sources to the target
target_sources(${CURRENT_MODULE_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/ExampleCachedProvider.cpp
        # Add the includes too (for better generation)
        #...
)

# Make sure this include dir can be found inside the project to include
target_include_directories(${CURRENT_MODULE_NAME} PUBLIC ${SRC_DIR})
# Additional include directories
target_include_directories(${CURRENT_MODULE_NAME} PUBLIC ${PATH_INCLUDE_ROOT})

# link libraries
target_link_libraries(${CURRENT_MODULE_NAME} PUBLIC SDCLib)


# build
set_target_properties(  ${CURRENT_MODULE_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT}
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT}
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT}
                        DEBUG_POSTFIX _d
                        )
# install
install(TARGETS ${CURRENT_MODULE_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE} RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME})


# Copy file to build folder
configure_file(${SRC_DIR}/cachedMdib.xml ${PATH_RUNTIME_OUTPUT}/cachedMdib.xml COPYONLY)

# ...

