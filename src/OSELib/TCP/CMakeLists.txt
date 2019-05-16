# Current Target
set( CURRENT_TARGET_NAME MessageManipulatorLib )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

# Add an empty target first - FIXME: Why distinguish here. Does PIC flag solve it?
if(WIN32)
	add_library(${CURRENT_TARGET_NAME} STATIC "")
else()
	add_library(${CURRENT_TARGET_NAME} SHARED "")
endif()

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})


# Better Handling of Public Header Files
set(TARGET_PUBLIC_HEADERS   "")



# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/TCPClient.cpp
        ${SRC_DIR}/TCPConnection.cpp
        ${SRC_DIR}/TCPConnectionEventHandler.cpp
        ${SRC_DIR}/TCPServer.cpp
        ${SRC_DIR}/TCPServerEventHandler.cpp
        ${SRC_DIR}/ContextWorker.cpp
        ${SRC_DIR}/UUID.cpp
        ${SRC_DIR}/TCPClientEventHandler.cpp
)


# Make sure include dirs can be found inside the project
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${SRC_DIR} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_SRC_ROOT} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_INCLUDE_ROOT} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${Qt5Core_INCLUDE_DIRS} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${Qt5Quick_INCLUDE_DIRS} )


# build
set_target_properties(  ${CURRENT_TARGET_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT}
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT}
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT}
                        DEBUG_POSTFIX ${DEBUG_POSTFIX_OUTPUT}
                        )

# install
install(TARGETS ${CURRENT_TARGET_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME}
            LIBRARY DESTINATION ${PATH_INSTALL_LIBRARY}
            ARCHIVE DESTINATION ${PATH_INSTALL_ARCHIVE}
)

# ...
