CXX=g++
CPPFLAGS=-std=c++11 -lgtest

test: run_test
	./$<

vector_tests.o: vector_tests.cpp ../vector/Vector.hpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

run_test: test_runner.cpp vector_tests.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $^
