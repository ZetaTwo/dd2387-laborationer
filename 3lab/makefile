CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))

COMPILE=mkdir -p $(dir $@); $(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $< $(filter-out $<,$(filter %.o,$^))

MAKE_OBJECT=$(COMPILE) -c
MAKE_EXECUTABLE=$(COMPILE)

default: run_test

clean:
	rm -rf build

build/%.o: %.cpp %.h
	$(MAKE_OBJECT)

build/test: test.cpp build/map.o build/util.o $(wildcard %.h)
	$(MAKE_EXECUTABLE)

run_test: build/test
	./$<
