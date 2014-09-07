CPPFLAGS=-Wall -g

default: verify

verify: main.exe
	/info/DD2387/labs/lab1/0.2_hello_world/hw_verifier $<

main.exe: main.cpp hello.o
	g++ $(CPPFLAGS) -o $@ $^

clean:
	rm -f *.o *.exe
