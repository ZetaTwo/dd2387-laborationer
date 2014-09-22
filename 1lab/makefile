CPPFLAGS=-std=c++11 -Wall -g -lgtest

COURSEDIR=../kurskatalog
CXXTEST_DIR=$(COURSEDIR)/cxxtest

EX01DIR=0.1_make_it_happen
EX02DIR=0.2_hello_world
EX03DIR=0.3_trainspotting
EX04DIR=0.4_does_it_fit
EX05DIR=0.5_will_it_float
EX06DIR=0.6_the_simple_container
EX07DIR=0.7_the_template_vector

EX14DIR=1.4_the_hypercube
EX15DIR=1.5_space_is_not_infinite
EX16DIR=1.6_walking_across_the_universe

lab1: ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex14 ex15 ex16

build/%.o: %.cpp %.h
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -c -o $@ $<

build/%.exe: %.cpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $<

run/%: build/%.exe
	./$^

valgrind/%: build/%.exe
	valgrind ./$^

ex01: run/$(EX01DIR)/hello_world

ex02: build/$(EX02DIR)/hello.exe
	./$<
	./$< DD2387
	./$< "KTH" 3
	-./$< "Malcom X" NaN
	-./$< kth dd2387 3
	./$< 5
	$(COURSEDIR)/lab1/0.2_hello_world/hw_verifier $<

ex03: run/$(EX03DIR)/float run/$(EX03DIR)/weird

ex04: run/$(EX04DIR)/simple_testrunner

ex05: valgrind/$(EX05DIR)/birth valgrind/$(EX05DIR)/bad_plumming

ex06: build/$(EX06DIR)/test_vec.exe
	valgrind ./$<

ex07: ex07_given_tests ex07_tests
ex07_given_tests: valgrind/$(EX07DIR)/test_template_vec
ex07_tests: run/$(EX07DIR)/vector_tests

ex14: run/$(EX14DIR)/hypercube_tests
ex15: run/$(EX15DIR)/vector_bool_tests
ex16: run/$(EX16DIR)/vector_iterator_tests

build/$(EX02DIR)/hello.exe: $(EX02DIR)/main.cpp build/$(EX02DIR)/hello.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX04DIR)/simple_testrunner.exe: build/$(EX04DIR)/simple_testrunner.cpp $(EX04DIR)/count_if_followed_by.o
	mkdir -p $(@D)
	g++ -o $@ -I $(CXXTEST_DIR)/ -I . $^

build/$(EX04DIR)/simple_testrunner.cpp: $(EX04DIR)/simple.cxxtest.cpp
	mkdir -p $(@D)
	python2 $(CXXTEST_DIR)/cxxtestgen.py --error-printer -o $@ $<

build/$(EX06DIR)/test_vec.exe: $(EX06DIR)/test_vec.cpp build/$(EX06DIR)/vector.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX07DIR)/vector_tests.o: $(EX07DIR)/vector_tests.cpp $(EX07DIR)/kth_cprog_vektor.cpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -c -o $@ $<

build/$(EX07DIR)/vector_tests.exe: ../test_runner.cpp build/$(EX07DIR)/vector_tests.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX14DIR)/hypercube_tests.o: $(EX14DIR)/hypercube_tests.cpp $(EX14DIR)/hypercube.hpp $(EX07DIR)/kth_cprog_vektor.cpp
	mkdir -p $(@D)
	g++ ${CPPFLAGS} -I $(EX07DIR) -c -o $@ $<

build/$(EX14DIR)/hypercube_tests.exe: ../test_runner.cpp build/$(EX14DIR)/hypercube_tests.o
	mkdir -p $(@D)
	g++ ${CPPFLAGS} -o $@ $^

build/$(EX15DIR)/vector_bool_tests.o: $(EX15DIR)/vector_bool_tests.cpp $(EX15DIR)/kth_cprog_vektor_bool.cpp $(EX07DIR)/kth_cprog_vektor.cpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -I $(EX07DIR) -c -o $@ $<

build/$(EX15DIR)/vector_bool_tests.exe: ../test_runner.cpp build/$(EX15DIR)/vector_bool_tests.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX16DIR)/vector_iterator_tests.o: $(EX16DIR)/vector_iterator_tests.cpp $(EX07DIR)/kth_cprog_vektor.cpp
	mkdir -p $(@D)
	g++ ${CPPFLAGS} -I $(EX07DIR) -c -o $@ $<

build/$(EX16DIR)/vector_iterator_tests.exe: ../test_runner.cpp build/$(EX16DIR)/vector_iterator_tests.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^
