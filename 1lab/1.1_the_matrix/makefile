# Change these
cxxtestpath = ../../kurskatalog/cxxtest/
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

Matrix.o: Matrix.cpp Matrix.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I ../0.7_the_template_vector -c -o $@ $<

matrix_tests.o: matrix_tests.cpp Matrix.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I ../0.7_the_template_vector -c -o $@ $<

test: ../../test_runner.cpp matrix_tests.o Matrix.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

testcode.cpp: $(testcode)
	python2 $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

given_test: testcode.cpp Matrix.o
	g++ $(CPPFLAGS) -I $(cxxtestpath) -I ../0.7_the_template_vector -o $@ $^
