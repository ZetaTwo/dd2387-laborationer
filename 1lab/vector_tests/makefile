CXX=g++
CPPFLAGS = -g -std=c++11 -lgtest

test: run_test
	./$<

test_hypercube: run_test_hypercube
	./$<

clean:
	rm -f \
		*.o \
		run_test* \
		test_vec \
		test_template_vec

vector_tests.o: vector_tests.cpp ../vector/kth_cprog_vektor.cpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

run_test: test_runner.cpp vector_tests.o vector_bool_tests.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $^

vector_bool_tests.o: vector_bool_tests.cpp ../vector/kth_cprog_vektor_bool.cpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

valgrind: run_test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$<

hypercube_tests.o: hypercube_tests.cpp ../vector/hypercube.hpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

run_test_hypercube: test_runner.cpp hypercube_tests.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $^

test_vec: test_vec.cpp ../vector/Vector_int.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

test_template_vec: test_template_vec.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

valgrind_test_vec: test_vec
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$<

valgrind_test_template_vec: test_template_vec
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$<
