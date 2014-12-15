COURSEDIR=../kurskatalog
CXXTEST_DIR=$(COURSEDIR)/cxxtest

KATTISSUBMIT:=~/bin/kattissubmit

EX01DIR=0.1_make_it_happen
EX02DIR=0.2_hello_world
EX03DIR=0.3_trainspotting
EX04DIR=0.4_does_it_fit
EX05DIR=0.5_will_it_float
EX06DIR=0.6_the_simple_container
EX07DIR=0.7_the_template_vector

EX11DIR=1.1_the_matrix
EX11BUGSDIR=1.1_the_matrix/buggies
EX11BUGSPREFIX=
EX14DIR=1.4_the_hypercube
EX15DIR=1.5_space_is_not_infinite

CXX=clang++
CPPFLAGS=-std=c++11 -Wall -g
INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))
COMPILE=mkdir -p $(dir $@); $(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $(filter-out %.h %.hpp,$^)

MAKE_OBJECT=$(COMPILE) -c
MAKE_EXECUTABLE=$(COMPILE) -lgtest
MAKE_CXXTEST_CODE=mkdir -p $(@D); python2 $(CXXTEST_DIR)/cxxtestgen.py --error-printer -o $@ $<

TEMPLATE_VECTOR_HEADER=$(EX07DIR)/kth_cprog_template_container.hpp
MATRIX_HEADER=$(EX11DIR)/Matrix.h $(TEMPLATE_VECTOR_HEADER)
TEST_RUNNER_CODE=../test_runner.cpp
TEST_RUNNER_OBJECT=build/test_runner.o

lab1: ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex11 ex14 ex15

clean:
	rm -rf build

# Kep intermediate files
.SECONDARY:

build/%.o: %.cpp %.h
	$(MAKE_OBJECT)

build/%.exe: %.cpp
	$(MAKE_EXECUTABLE)

run/%: build/%.exe
	./$^ $(GTEST_FLAGS)

valgrind/%: build/%.exe
	valgrind ./$^

$(TEST_RUNNER_OBJECT): $(TEST_RUNNER_CODE)
	$(MAKE_OBJECT)

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

ex11: run/$(EX11DIR)/matrix_tests ex11_compiler_tests
ex11buggy: $(patsubst $(EX11BUGSDIR)/Matrix0%.o,run/$(EX11BUGSDIR)/test0%,$(wildcard $(EX11BUGSDIR)/Matrix0*.o))
ex14: run/$(EX14DIR)/hypercube_tests
ex15: run/$(EX15DIR)/vector_bool_tests

build/$(EX02DIR)/hello.exe: $(EX02DIR)/main.cpp build/$(EX02DIR)/hello.o
	$(MAKE_EXECUTABLE)

build/$(EX04DIR)/simple_testrunner.cpp: $(EX04DIR)/simple.cxxtest.cpp
	$(MAKE_CXXTEST_CODE)

build/$(EX04DIR)/simple_testrunner.exe: build/$(EX04DIR)/simple_testrunner.cpp $(EX04DIR)/count_if_followed_by.o
	$(MAKE_EXECUTABLE) -I $(CXXTEST_DIR) -I .

run/$(EX04DIR)/simple_testrunner: build/$(EX04DIR)/simple_testrunner.exe
	-./$^

build/$(EX06DIR)/test_vec.exe: $(EX06DIR)/test_vec.cpp $(EX06DIR)/kth_cprog_simple_container.hpp
	$(MAKE_EXECUTABLE)

build/$(EX07DIR)/%_tests.o: $(EX07DIR)/%_tests.cpp $(TEMPLATE_VECTOR_HEADER)
	$(MAKE_OBJECT)

build/$(EX07DIR)/vector_tests.exe: $(TEST_RUNNER_OBJECT) $(patsubst %.cpp,build/%.o,$(wildcard $(EX07DIR)/*_tests.cpp))
	$(MAKE_EXECUTABLE)

ex11_compiler_tests: $(patsubst $(EX11DIR)/compiler_tests/%.cpp,ex11_compiler_test_%,$(wildcard $(EX11DIR)/compiler_tests/*.cpp))
ex11_compiler_test_%: $(EX11DIR)/compiler_tests/%.cpp build/$(EX11DIR)/Matrix.o
	mkdir -p $(@D)
	! g++ $(CPPFLAGS) -I $(EX11DIR) -I $(EX07DIR) $^ -o /dev/null &>/dev/null

build/$(EX11DIR)/Matrix.o: $(EX11DIR)/Matrix.cpp $(MATRIX_HEADER)
	$(MAKE_OBJECT)

build/$(EX11DIR)/matrix_tests.o: $(EX11DIR)/matrix_tests.cpp build/$(EX11DIR)/Matrix.o $(MATRIX_HEADER)
	$(MAKE_OBJECT)

build/$(EX11DIR)/matrix_tests.exe: $(TEST_RUNNER_OBJECT) build/$(EX11DIR)/matrix_tests.o build/$(EX11DIR)/Matrix.o
	$(MAKE_EXECUTABLE)

build/$(EX11BUGSDIR)/test.o: $(EX11BUGSDIR)/matrix_tests.cpp $(EX11BUGSDIR)/Matrix.h
	$(MAKE_OBJECT)

build/$(EX11BUGSDIR)/test0%.exe: $(TEST_RUNNER_OBJECT) build/$(EX11BUGSDIR)/test.o $(EX11BUGSDIR)/$(EX11BUGSPREFIX)Matrix0%.o $(EX11BUGSDIR)/Matrix.h
	$(MAKE_EXECUTABLE)

build/$(EX14DIR)/hypercube_tests.o: $(EX14DIR)/hypercube_tests.cpp $(EX14DIR)/hypercube.hpp $(TEMPLATE_VECTOR_HEADER)
	$(MAKE_OBJECT)

build/$(EX14DIR)/hypercube_tests.exe: $(TEST_RUNNER_OBJECT) build/$(EX14DIR)/hypercube_tests.o
	$(MAKE_EXECUTABLE)

build/$(EX15DIR)/%.o: $(EX15DIR)/%.cpp $(EX15DIR)/kth_cprog_vektor_bool.h $(TEMPLATE_VECTOR_HEADER)
	$(MAKE_OBJECT)

build/$(EX15DIR)/%_tests.o: $(EX15DIR)/%_tests.cpp $(EX15DIR)/kth_cprog_vektor_bool.h $(TEMPLATE_VECTOR_HEADER)
	$(MAKE_OBJECT)

build/$(EX15DIR)/vector_bool_tests.exe: $(TEST_RUNNER_OBJECT) $(patsubst %.cpp,build/%.o,$(wildcard $(EX15DIR)/kth_cprog_vektor_bool*.cpp) $(wildcard $(EX15DIR)/*_tests.cpp))
	$(MAKE_EXECUTABLE)

BUGGIES_REMAINING=7 8
autotest_buggies:
	while inotifywait -e close_write 1.1_the_matrix/buggies/*; do make $(foreach i,$(BUGGIES_REMAINING),run/1.1_the_matrix/buggies/test0$i); done

kattis:
	$(KATTISSUBMIT) -f -p kth:cprog:lab1:templatecontainer -l c++ $(TEMPLATE_VECTOR_HEADER)
