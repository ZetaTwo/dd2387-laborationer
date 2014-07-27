# Change these
cxxtestpath = ../../cxxtest/
testcode    = example_test.h

CXX=g++
CPPFLAGS=-std=c++11 -lgtest

run_test: test run_compiler_tests
	./$<

run_given_test: given_test
	./$<

run_compiler_tests: $(patsubst compiler_tests/%.cpp,run_compiler_test_%,$(wildcard compiler_tests/*.cpp))
run_compiler_test_%: compiler_tests/%.cpp Matrix.o
	! $(CXX) -I . $^ -o /dev/stdout &>/dev/null

clean:
	rm -f \
		*test \
		testcode.cpp \
		*.o \
		compiler_test_failure

test_matrix.o: test_matrix.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

test: test_runner.cpp test_matrix.o Matrix.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

testcode.cpp: $(testcode)
	python2 $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

given_test: testcode.cpp Matrix.o
	g++ -I $(cxxtestpath) -o $@ $^
