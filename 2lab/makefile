CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))

COMPILE=mkdir -p $(dir $@); $(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $< $(filter %.o,$^)

MAKE_OBJECT=$(COMPILE) -c
MAKE_EXECUTABLE=$(COMPILE)

DATE_FILENAMES=date mjd_offset_date western_date gregorian julian
DATE_HEADERS=$(foreach name,$(DATE_FILENAMES),$(name).h)
DATE_OBJECTS=$(foreach name,$(DATE_FILENAMES),build/$(name).o)
KATTISTIME=kurskatalog/kattistime.h

TEST_OBJECTS=$(patsubst %.cpp,build/%.o,$(wildcard test/*_test.cpp))

default: run_test run_given_test run_calendar_test

date_objects: $(DATE_OBJECTS)

valgrind: valgrind_test valgrind_given_test

clean:
	rm -r build

run_test: build/run_test
	$< $(GTEST_FLAGS)

valgrind_test: build/run_test
	valgrind $< $(GTEST_FLAGS)

autotest:
	while inotifywait -qqr -e close_write --exclude build/ . ; do make && echo "OK" || echo "FAILURE"; done

run_calendar_test: build/test/test_calendar test/test_calendar.out
	$< > build/test/test_calendar.out
	diff -u test/test_calendar.out build/test/test_calendar.out

run_given_test: build/test/datetest
	$<

valgrind_given_test: build/test/datetest
	valgrind $<

build/%.o: %.cpp $(DATE_HEADERS) $(KATTISTIME)
	$(MAKE_OBJECT)

build/run_test: test_runner.cpp $(TEST_OBJECTS) $(DATE_OBJECTS) build/kurskatalog/kattistime.o
	$(MAKE_EXECUTABLE) -lgtest

build/test/datetest: test/datetest.cpp $(DATE_OBJECTS) build/kurskatalog/kattistime.o $(DATE_HEADERS) $(KATTISTIME)
	$(MAKE_EXECUTABLE)

build/test/test_calendar: test/test_calendar.cpp calendar.h $(DATE_HEADERS) $(DATE_OBJECTS) $(KATTISTIME) build/kurskatalog/kattistime.o
	$(MAKE_EXECUTABLE)
