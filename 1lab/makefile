CPPFLAGS=-std=c++11 -Wall -g

COURSEDIR=../kurskatalog

EX01DIR=0.1_make_it_happen
EX02DIR=0.2_hello_world
EX03DIR=0.3_trainspotting

lab1: ex01 ex02 ex03

build/%.o: %.cpp %.h
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -c -o $@ $<

build/%.exe: %.cpp
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $<

run/%: build/%.exe
	./$^

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

build/$(EX02DIR)/hello.exe: $(EX02DIR)/main.cpp build/$(EX02DIR)/hello.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^
