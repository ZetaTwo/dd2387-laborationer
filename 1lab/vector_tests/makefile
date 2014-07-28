CXX=g++
CPPFLAGS = -g -std=c++11 -lgtest

test: run_test
	./$<

test_hypercube: run_test_hypercube
	./$<

vector_tests.o: vector_tests.cpp ../vector/kth_cprog_vektor.cpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

run_test: test_runner.cpp vector_tests.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $^

valgrind: run_test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$<

hypercube_tests.o: hypercube_tests.cpp ../vector/hypercube.hpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

run_test_hypercube: test_runner.cpp hypercube_tests.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $^

test_template_vec: test_template_vec.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

valgrind_test_template_vec: test_template_vec
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$<
