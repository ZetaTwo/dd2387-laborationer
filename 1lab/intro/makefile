default: test_hello

bin/%: %.cpp
	g++ -g -o $@ $^

test_hello: bin/hello
	./$< | diff /dev/stdin test_hello/test..txt
	./$< C++ | diff /dev/stdin test_hello/test.C++.txt
	./$< 3 C++ | diff /dev/stdin test_hello/test.3_C++.txt
	./$< 2 | diff /dev/stdin test_hello/test.2.txt
