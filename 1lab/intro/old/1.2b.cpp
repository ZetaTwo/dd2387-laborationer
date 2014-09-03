/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test_must_follow_a.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test_must_follow_a.cpp", 5, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_a_is_second_to_last : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 17, "test_a_is_second_to_last" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last(); }
} testDescription_MyTestSuite_test_a_is_second_to_last;

static class TestDescription_MyTestSuite_test_expect_it_to_return_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_expect_it_to_return_2() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 24, "test_expect_it_to_return_2" ) {}
 void runTest() { suite_MyTestSuite.test_expect_it_to_return_2(); }
} testDescription_MyTestSuite_test_expect_it_to_return_2;

static class TestDescription_MyTestSuite_test_make_sure_it_doesnt_look_outside_the_given_range : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_make_sure_it_doesnt_look_outside_the_given_range() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 31, "test_make_sure_it_doesnt_look_outside_the_given_range" ) {}
 void runTest() { suite_MyTestSuite.test_make_sure_it_doesnt_look_outside_the_given_range(); }
} testDescription_MyTestSuite_test_make_sure_it_doesnt_look_outside_the_given_range;

#include <cxxtest/Root.cpp>
