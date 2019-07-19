/**
 *  @file UnitTests.cpp
 *  @project SDCLib
 *  @date 18.07.2019
 *  @author besting, baumeister
 *  @copyright (c) SurgiTAIX AG
 */

// Testingframework
#include "UnitTest++/src/UnitTest++.h"
#include "UnitTest++/src/TestRunner.h"
#include "UnitTest++/src/TestReporterStdout.h"

int runAllTests() {
	return UnitTest::RunAllTests();
}

int runTestSuite(std::string suiteName) {
	UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
	return runner.RunTestsIf(UnitTest::Test::GetTestList(), suiteName.c_str(), UnitTest::True(), 0);
}

int runSingleTest(std::string testName) {
	std::string findTest = testName;
	UnitTest::TestReporterStdout reporter;
	UnitTest::TestRunner runner(reporter);
	UnitTest::TestList selectedTests;
	UnitTest::Test * currentTest = UnitTest::Test::GetTestList().GetHead();
	while (currentTest) {
		if (findTest == std::string(currentTest->m_details.testName)) {
			selectedTests.Add(currentTest);
		}
		// The tests are collected in a linked list. If we take a single test from the list,
		// the reference to the next one has to be reset to not accidentally add all following tests.
		UnitTest::Test * temp = currentTest;
		currentTest = currentTest->next;
		temp->next = NULL;
	}
	return runner.RunTestsIf(selectedTests, NULL, UnitTest::True(), 0);
}

int main()
{
    // ALL TESTS
	//runAllTests();

    // TEST SUITE
	runTestSuite("SDC");

    // SINGLE TESTS (Note: Name is case sensitive!) [ Chose ONE of the following]
    //runSingleTest("ConnectionLost"); // Should work
    //runSingleTest("MultiSDC"); // Should work
    //runSingleTest("SimpleSDC"); // Should work
    //runSingleTest("PeriodicEvents"); // Should work
    //runSingleTest("StreamSDC"); // Should work
	return 0;
}

