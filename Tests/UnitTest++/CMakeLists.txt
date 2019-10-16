# Current Target
set( CURRENT_TARGET_NAME UnitTests )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME} "CXX")

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")
add_executable(${CURRENT_TARGET_NAME} "")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${PATH_TESTS_ROOT}/UnitTests.cpp
        # UnitTests++
        ${SRC_DIR}/Test.cpp
        ${SRC_DIR}/TestList.cpp
        ${SRC_DIR}/TestRunner.cpp
        ${SRC_DIR}/CurrentTest.cpp
        ${SRC_DIR}/TestDetails.cpp
        ${SRC_DIR}/TestResults.cpp
        ${SRC_DIR}/ReportAssert.cpp
        ${SRC_DIR}/TestReporter.cpp
        ${SRC_DIR}/TimeConstraint.cpp
        ${SRC_DIR}/AssertException.cpp
        ${SRC_DIR}/MemoryOutStream.cpp
        ${SRC_DIR}/XmlTestReporter.cpp
        ${SRC_DIR}/DeferredTestResult.cpp
        ${SRC_DIR}/TestReporterStdout.cpp
        ${SRC_DIR}/DeferredTestReporter.cpp
        ${SRC_DIR}/Posix/TimeHelpers.cpp
        ${SRC_DIR}/Win32/TimeHelpers.cpp
        ${SRC_DIR}/Posix/SignalTranslator.cpp
        # SDCTests
        ${PATH_SDCTESTS_ROOT}/TestConnectionLost.cpp
        #${PATH_SDCTESTS_ROOT}/TestDICOM.cpp
        ${PATH_SDCTESTS_ROOT}/TestMultiSDC.cpp
        #${PATH_SDCTESTS_ROOT}/TestMultiStates.cpp
        ${PATH_SDCTESTS_ROOT}/TestSimpleSDC.cpp
        ${PATH_SDCTESTS_ROOT}/TestPeriodicEvents.cpp
        ${PATH_SDCTESTS_ROOT}/TestStreamSDC.cpp
        
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

# ...

