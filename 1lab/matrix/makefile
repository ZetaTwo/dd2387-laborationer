# Change these
cxxtestpath = ../../cxxtest/
testcode    = example_test.h

CXX=g++
CPPFLAGS=-std=c++11 -lgtest

run_%: %
	./$<

clean:
	rm -f \
		*test \
		testcode.cpp \
		*.o

test_matrix.o: test_matrix.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

test: test_runner.cpp test_matrix.o Matrix.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

testcode.cpp: $(testcode)
	python2 $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

given_test: testcode.cpp Matrix.o
	g++ -I $(cxxtestpath) -o $@ $^
