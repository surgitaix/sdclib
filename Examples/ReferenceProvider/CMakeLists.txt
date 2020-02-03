# Current Target
set( CURRENT_TARGET_NAME ReferenceProvider )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME} "CXX")

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")
add_executable(${CURRENT_TARGET_NAME} "")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CERT_DIR ${CMAKE_CURRENT_LIST_DIR}/certs)

# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/ReferenceProvider.cpp
        # Add the includes too (for better generation)
        #...
)

# Make sure this include dir can be found inside the project to include
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${SRC_DIR})
# Additional include directories
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${PATH_INCLUDE_ROOT})

# SDCLib
target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE SDCLib)


# build
set_target_properties(  ${CURRENT_TARGET_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT}
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT}
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT}
                        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
                        )
# install
install(TARGETS ${CURRENT_TARGET_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE} RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME})

# Copy files to build folder
configure_file(${CERT_DIR}/ca.pem   ${PATH_RUNTIME_OUTPUT}/ca.pem COPYONLY)
configure_file(${CERT_DIR}/sdccert.pem     ${PATH_RUNTIME_OUTPUT}/sdccert.pem COPYONLY)
configure_file(${CERT_DIR}/userkey.pem  ${PATH_RUNTIME_OUTPUT}/userkey.pem COPYONLY)
configure_file(${SRC_DIR}/referenceMDIB.xml ${PATH_RUNTIME_OUTPUT}/referenceMDIB.xml COPYONLY)

# ...

