CXX=clang++
CPPFLAGS=-std=c++11 -Wall -Wextra -g

INCLUDE_PREREQUISITE_HEADER_DIRECTORIES=$(foreach file,$(filter %.h %.hpp,$^),-I $(dir $(file)))

COMPILE=mkdir -p $(dir $@); $(CXX) $(CPPFLAGS) $(INCLUDE_PREREQUISITE_HEADER_DIRECTORIES) -o $@ $< $(filter-out $<,$(filter %.o,$^))

MAKE_OBJECT=$(COMPILE) -c
MAKE_EXECUTABLE=$(COMPILE)

default: run_test

clean:
	rm -rf build

run_test: build/test
	./$<

build/%.o: %.cpp %.h
	$(MAKE_OBJECT)

build/actors/%.o: actors/%.cpp actors/%.h actor.h
	$(MAKE_OBJECT)

build/tiles/%.o: tiles/%.cpp tiles/%.h tile.h
	$(MAKE_OBJECT)

build/test.o: test.cpp actors/basic.h game.h map.h tile.h tiles/hazards.h renderer.h
	$(MAKE_OBJECT)

build/test: build/test.o $(foreach obj,actor entity game map player tile util world actors/basic tiles/hazards,build/$(obj).o)
	$(MAKE_EXECUTABLE)

build/actor.o: actor.cpp actor.h entity.h item.h util.h
	$(MAKE_OBJECT)

build/entity.o: entity.cpp entity.h map.h util.h
	$(MAKE_OBJECT)

build/game.o: game.cpp game.h inputer.h player.h renderer.h world.h
	$(MAKE_OBJECT)

build/item.o: item.cpp item.h actor.h entity.h

build/map.o: map.cpp map.h tile.h util.h

build/player.o: player.cpp player.h actors/basic.h actor.h
	$(MAKE_OBJECT)

build/renderer.o: renderer.cpp renderer.h game.h
	$(MAKE_OBJECT)

build/tile.o: tile.cpp tile.h
	$(MAKE_OBJECT)

build/world.o: world.cpp actors/basic.h tiles/hazards.h world.h entity.h map.h util.h
	$(MAKE_OBJECT)

build/actors/basic.o: actors/basic.cpp actors/basic.h actor.h entity.h
	$(MAKE_OBJECT)

build/tiles/basic.o: tiles/basic.cpp tiles/basic.h hazards.h tile.h
	$(MAKE_OBJECT)
