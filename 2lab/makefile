CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))

COMPILE=mkdir -p $(dir $@); $(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $< $(filter %.o,$^)

MAKE_OBJECT=$(COMPILE) -c
MAKE_EXECUTABLE=$(COMPILE)

DATE_FILENAMES=date mjd_offset_date western_date gregorian_date
DATE_HEADERS=$(foreach name,$(DATE_FILENAMES),$(name).h)
DATE_OBJECTS=$(foreach name,$(DATE_FILENAMES),build/$(name).o)
KATTISTIME=kurskatalog/kattistime.h

TEST_OBJECTS=$(patsubst %.cpp,build/%.o,$(wildcard test/*_test.cpp))

default: test

clean:
	rm -r build

test: build/run_test
	$< $(GTEST_FLAGS)

build/%.o: %.cpp %.h
	$(MAKE_OBJECT)

build/mjd_offset_date.o: mjd_offset_date.cpp $(DATE_HEADERS)
	$(MAKE_OBJECT)

build/gregorian_date.o: gregorian_date.cpp $(DATE_HEADERS) $(KATTISTIME)
	$(MAKE_OBJECT)

build/test/%_test.o: test/%_test.cpp $(DATE_HEADERS)
	$(MAKE_OBJECT)

build/test/gregorian_date_test.o: test/gregorian_date_test.cpp $(DATE_HEADERS) $(KATTISTIME)
	$(MAKE_OBJECT)

build/run_test: test_runner.cpp $(TEST_OBJECTS) $(DATE_OBJECTS) build/kurskatalog/kattistime.o
	$(MAKE_EXECUTABLE) -lgtest
