CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

default: run

clean:
	rm -rf build

INCLUDES=-I gameengine -I examplegame

define compile
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -o $@ $< $(filter-out $<,$(filter %.o,$^))
endef

define make-executable
	$(compile)
endef

define make-object
	$(compile) -c
endef

define get-dependencies
$(wildcard $1.h) $(filter-out $(notdir $1.h),$(shell grep -E '^\#include ".*\.h"' gameengine/$1.cpp gameengine/$1.h 2>/dev/null | grep -oE '[^"]+\.h' | sort | uniq ))
endef

define make-object-rule
build/$1.o: $1.cpp $(call get-dependencies,$1)
	$$(make-object)
endef

define expand-depencencies
$(patsubst %,build/$2/%.o,$1)
endef

OBJECT_NAMES = $(patsubst %.cpp,%,$(wildcard */*.cpp */*/*.cpp))

$(foreach name,$(OBJECT_NAMES),$(eval $(call make-object-rule,$(name))))

run: build/examplegame/main
	./$<

valgrind: build/examplegame/main
	valgrind ./$<

build/examplegame/main: build/examplegame/main.o $(patsubst %.cpp,build/%.o,$(wildcard */*.cpp */*/*.cpp))
	$(make-executable)

build/inputer_test: inputer_test.cpp build/inputer.o
	$(make-executable)
