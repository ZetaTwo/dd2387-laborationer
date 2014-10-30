CXX=clang++
CPPFLAGS=-std=c++11 -Wall -g

clean:
	rm -f *.o

mjd_offset_date.o: mjd_offset_date.cpp mjd_offset_date.h date.h
	$(CXX) $(CPPFLAGS) -c -o $@ $<
