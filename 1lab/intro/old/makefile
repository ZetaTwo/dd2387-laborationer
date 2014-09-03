CXXTEST_DIR=../../cxxtest/
CXXTEST=python2 $(CXXTEST_DIR)cxxtestgen.py

CPP=g++
CPPFLAGS=-std=c++98

default: test_hello

clean:
	rm -f \
		1.2b.cpp

bin/%: %.cpp
	g++ -g -o $@ $^

test_hello: bin/hello
	./$< | diff /dev/stdin test_hello/test..txt
	./$< C++ | diff /dev/stdin test_hello/test.C++.txt
	./$< 3 C++ | diff /dev/stdin test_hello/test.3_C++.txt
	./$< 2 | diff /dev/stdin test_hello/test.2.txt

%.out:	%.cpp
	g++ -g -std=c++0x -Wall $*.cpp -o $*.out

1.2b.cpp: test_must_follow_a.cpp
	$(CXXTEST) --error-printer -o $@ $<

bin/test_1.2b.out: 1.2b.cpp must_follow_a.o
	$(CPP) $(CPPFLAGS) -o $@ -I $(CXXTEST_DIR) $^

run_test_1.2b.out: bin/test_1.2b.out
	./$<
