CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))

COMPILE=mkdir -p $(dir $@); $(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $< $(filter %.o,$^)

MAKE_OBJECT=$(COMPILE) -c
MAKE_EXECUTABLE=$(COMPILE)

default: test

clean:
	rm -r build

test: build/run_test
	$<

build/%.o: %.cpp %.h
	$(MAKE_OBJECT)

build/mjd_offset_date.o: mjd_offset_date.cpp mjd_offset_date.h date.h
	$(MAKE_OBJECT)

build/test/%_test.o: test/%_test.cpp %.h
	$(MAKE_OBJECT)

build/run_test: test_runner.cpp $(patsubst %.cpp,build/%.o,$(wildcard test/*_test.cpp)) build/date.o
	$(MAKE_EXECUTABLE) -lgtest
