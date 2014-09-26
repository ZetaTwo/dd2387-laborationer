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

EX11DIR=1.1_the_matrix
EX13DIR=1.3_the_hypercube
EX14DIR=1.4_space_is_not_infinite

lab1: ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex11 ex13 ex14

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

ex11: run/$(EX11DIR)/matrix_tests ex11_compiler_tests run/$(EX11DIR)/example_test
ex13: run/$(EX13DIR)/hypercube_tests
ex14: run/$(EX14DIR)/vector_bool_tests run/$(EX14DIR)/vector_iterator_tests

build/$(EX02DIR)/hello.exe: $(EX02DIR)/main.cpp build/$(EX02DIR)/hello.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX04DIR)/simple_testrunner.exe: build/$(EX04DIR)/simple_testrunner.cpp $(EX04DIR)/count_if_followed_by.o
	mkdir -p $(@D)
	g++ -o $@ -I $(CXXTEST_DIR)/ -I . $^

build/$(EX04DIR)/simple_testrunner.cpp: $(EX04DIR)/simple.cxxtest.cpp
	mkdir -p $(@D)
	python2 $(CXXTEST_DIR)/cxxtestgen.py --error-printer -o $@ $<

run/$(EX04DIR)/simple_testrunner: build/$(EX04DIR)/simple_testrunner.exe
	-./$^

build/$(EX06DIR)/test_vec.exe: $(EX06DIR)/test_vec.cpp $(EX06DIR)/kth_cprog_simple_container.hpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -I $(EX06DIR) -I $(EX07DIR) -o $@ $^

build/$(EX07DIR)/vector_tests.o: $(EX07DIR)/vector_tests.cpp $(EX07DIR)/kth_cprog_template_container.hpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -c -o $@ $<

build/$(EX07DIR)/vector_iterator_tests.o: $(EX07DIR)/vector_iterator_tests.cpp $(EX07DIR)/kth_cprog_template_container.hpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -c -o $@ $<

build/$(EX07DIR)/vector_tests.exe: ../test_runner.cpp build/$(EX07DIR)/vector_tests.o build/$(EX07DIR)/vector_iterator_tests.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

ex11_compiler_tests: $(patsubst $(EX11DIR)/compiler_tests/%.cpp,ex11_compiler_test_%,$(wildcard $(EX11DIR)/compiler_tests/*.cpp))
ex11_compiler_test_%: $(EX11DIR)/compiler_tests/%.cpp build/$(EX11DIR)/Matrix.o
	mkdir -p $(@D)
	! g++ $(CPPFLAGS) -I $(EX11DIR) -I $(EX07DIR) $^ -o /dev/null &>/dev/null

build/$(EX11DIR)/Matrix.o: $(EX11DIR)/Matrix.cpp $(EX11DIR)/Matrix.h
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -I $(EX07DIR) -c -o $@ $<

build/$(EX11DIR)/matrix_tests.o: $(EX11DIR)/matrix_tests.cpp build/$(EX11DIR)/Matrix.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -I $(EX07DIR) -c -o $@ $<

build/$(EX11DIR)/matrix_tests.exe: ../test_runner.cpp build/$(EX11DIR)/matrix_tests.o build/$(EX11DIR)/Matrix.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX11DIR)/example_test.cpp: $(EX11DIR)/example_test.h
	mkdir -p $(@D)
	python2 $(CXXTEST_DIR)/cxxtestgen.py --error-printer -o $@ $<

build/$(EX11DIR)/example_test.exe: build/$(EX11DIR)/example_test.cpp build/$(EX11DIR)/Matrix.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -I $(CXXTEST_DIR) -I $(EX07DIR) -I . -o $@ $^

build/$(EX13DIR)/hypercube_tests.o: $(EX13DIR)/hypercube_tests.cpp $(EX13DIR)/hypercube.hpp $(EX07DIR)/kth_cprog_template_container.hpp
	mkdir -p $(@D)
	g++ ${CPPFLAGS} -I $(EX07DIR) -c -o $@ $<

build/$(EX13DIR)/hypercube_tests.exe: ../test_runner.cpp build/$(EX13DIR)/hypercube_tests.o
	mkdir -p $(@D)
	g++ ${CPPFLAGS} -o $@ $^

build/$(EX14DIR)/vector_bool_tests.o: $(EX14DIR)/vector_bool_tests.cpp $(EX14DIR)/kth_cprog_vektor_bool.hpp $(EX07DIR)/kth_cprog_template_container.hpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -I $(EX07DIR) -c -o $@ $<

build/$(EX14DIR)/vector_bool_tests.exe: ../test_runner.cpp build/$(EX14DIR)/vector_bool_tests.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^

build/$(EX14DIR)/vector_iterator_tests.o: $(EX14DIR)/vector_iterator_tests.cpp $(EX07DIR)/kth_cprog_template_container.hpp
	mkdir -p $(@D)
	g++ ${CPPFLAGS} -I $(EX07DIR) -c -o $@ $<

build/$(EX14DIR)/vector_iterator_tests.exe: ../test_runner.cpp build/$(EX14DIR)/vector_iterator_tests.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^
