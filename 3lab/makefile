CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

default: run

clean:
	rm -rf build

INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))

define compile
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $< $(filter-out $<,$(filter %.o,$^))
endef

define make-executable
	$(compile)
endef

define make-object
	$(compile) -c
endef

define get-dependencies
$(wildcard $1.h) $(filter-out $(notdir $1.h),$(shell grep -E '^\#include ".*\.h"' $1.cpp $1.h 2>/dev/null | grep -oE '[^"]+\.h' | sort | uniq ))
endef

define make-object-rule
build/$1.o: $1.cpp $(call get-dependencies,$1)
	$$(make-object)
endef

OBJECT_NAMES = $(patsubst %.cpp,%,$(wildcard *.cpp */*.cpp))

$(foreach name,$(OBJECT_NAMES),$(eval $(call make-object-rule,$(name))))

run: build/main
	./$<

MAIN_DEPENDS_ON_OBJECTS=actor entity game map player renderer tile util world actors/basic tiles/hazards
build/main: build/main.o $(patsubst %,build/%.o,$(MAIN_DEPENDS_ON_OBJECTS))
	$(make-executable)
