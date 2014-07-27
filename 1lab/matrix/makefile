# Change these
cxxtestpath = ../../cxxtest/
testcode    = example_test.h

CXX=g++
CPPFLAGS=-std=c++11 -lgtest

run_given_test: given_test
	./$<

clean:
	rm -f \
		given_test \
		testcode.cpp \
		*.o

testcode.cpp: $(testcode)
	python2 $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

given_test: testcode.cpp Matrix.o
	g++ -I $(cxxtestpath) -o $@ $^
