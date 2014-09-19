CPPFLAGS=-std=c++11 -Wall -g

COURSEDIR=../kurskatalog

EX02DIR=0.2_hello_world

lab1: ex02

build/%.o: %.cpp %.h
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -c -o $@ $<

ex02: build/$(EX02DIR)/hello.exe
	./$<
	./$< DD2387
	./$< "KTH" 3
	-./$< "Malcom X" NaN
	-./$< kth dd2387 3
	./$< 5
	$(COURSEDIR)/lab1/0.2_hello_world/hw_verifier $<

build/$(EX02DIR)/hello.exe: $(EX02DIR)/main.cpp build/$(EX02DIR)/hello.o
	mkdir -p $(@D)
	g++ $(CPPFLAGS) -o $@ $^
