LDFLAGS := -lpthread -lgtest -lgtest_main

.PHONY: all

tests:
	g++ -c matrix_tests.cpp -o matrix_tests.o
	g++ -c test_runner.cpp -o test_runner.o

runtest0%: tests
	g++ -o runtest0$* matrix_tests.o test_runner.o Matrix0$*.o $(LDFLAGS)

clean:
	touch runtest01 matrix_tests.o
	rm runtest0* matrix_tests.o
