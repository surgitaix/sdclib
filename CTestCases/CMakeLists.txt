set(CTEST_SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CTEST_BINARY_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(Tools)

file(GLOB files "test_*.cpp")

foreach(file ${files})
	string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
	add_executable(${file_without_ext} ${file})
	target_link_libraries(${file_without_ext} SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS} Tools Statehandler)
	add_test(NAME ${file_without_ext} COMMAND ${file_without_ext} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
	set_tests_properties(${file_without_ext}
		PROPERTIES
		PASS_REGULAR_EXPRESSION "Test passed")
	set_tests_properties(${file_without_ext}
		PROPERTIES
		FAIL_REGULAR_EXPRESSION "(Exception|Test failed)")
	set_tests_properties(${file_without_ext}
		PROPERTIES
		TIMEOUT 120)
endforeach()
