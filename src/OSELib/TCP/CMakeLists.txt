# Current Target
set( CURRENT_TARGET_NAME MessageManipulatorLib )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

# Add an empty target first - FIXME: Why distinguish here. Does PIC flag solve it?
add_library(${CURRENT_TARGET_NAME} STATIC "")


message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})


# Better Handling of Public Header Files
set(TARGET_PUBLIC_HEADERS 
		${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPClient.h)



# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/TCPClient.cpp
       	${SRC_DIR}/TCPClientMessenger.cpp
        ${SRC_DIR}/TCPClientEventHandler.cpp
       	${SRC_DIR}/TCPConnection.cpp
        ${SRC_DIR}/TCPConnectionBroadcastHandler.cpp
      	${SRC_DIR}/TCPConnectionMessenger.cpp
       	${SRC_DIR}/TCPBroadcastServerHandler.cpp
        ${SRC_DIR}/TCPServer.cpp
        ${SRC_DIR}/ContextWorker.cpp
        ${SRC_DIR}/UUID.cpp
   PUBLIC
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPClient.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPClientMessenger.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPClientEventHandler.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPConnection.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPConnectionBroadcastHandler.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPConnectionMessenger.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPBroadcastServerHandler.h
        ${PATH_INCLUDE_ROOT}/OSELib/TCP/TCPServer.h
        
)


# Make sure include dirs can be found inside the project
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${SRC_DIR} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_SRC_ROOT} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_INCLUDE_ROOT} )


# build
set_target_properties(  ${CURRENT_TARGET_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT}
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT}
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT}
                        )

# install
install(TARGETS ${CURRENT_TARGET_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME}
            LIBRARY DESTINATION ${PATH_INSTALL_LIBRARY}
            ARCHIVE DESTINATION ${PATH_INSTALL_ARCHIVE}
)

# ...
