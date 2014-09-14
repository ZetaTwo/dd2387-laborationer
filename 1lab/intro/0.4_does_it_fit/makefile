exercise: simple_testrunner.exe
	./$<

simple_testrunner.exe: simple_testrunner.cpp count_if_followed_by.o
	g++ -o $@ -I ../../../kurskatalog/cxxtest/ $^

simple_testrunner.cpp: simple.cxxtest.cpp
	python2 ../../../kurskatalog/cxxtest/cxxtestgen.py --error-printer -o simple_testrunner.cpp simple.cxxtest.cpp
