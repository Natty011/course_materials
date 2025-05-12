CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -pedantic -ansi
CXXFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-ldl

libcpp_static: libcpp.o
	ar rcs libcpp.a libcpp.o

libcpp_shared: libcpp.o
	$(CXX) -shared -o libcpp.so libcpp.o

libcpp.o: libcpp.cpp libcpp.hpp
	$(CXX) -fPIC -c libcpp.cpp -o libcpp.o

libc_static: libc.o
	ar rcs libc.a libc.o

libc_shared: libc.o
	$(CC) -shared -o libc.so libc.o

libc.o: libc.c libc.h
	$(CC) -fPIC -c libc.c -o libc.o

prog_static: main.c libcpp.a
	$(CC) $(CFLAGS) main.c libcpp.a -lstdc++ -o prog_static

prog_dyn: main.c libcpp.so
	$(CC) $(CFLAGS) main.c -L. -lcpp -lstdc++ -o prog_dyn

prog_explicit: main_explicit.c
	$(CC) $(CFLAGS) main_explicit.c $(LDFLAGS) -lstdc++ -o prog_explicit

cpp_static: main.cpp libc.a
	$(CXX) $(CXXFLAGS) main.cpp libc.a -o cpp_static

cpp_dyn: main.cpp libc.so
	$(CXX) $(CXXFLAGS) main.cpp -L. -lc -o cpp_dyn

cpp_explicit: main_explicit.cpp
	$(CXX) $(CXXFLAGS) main_explicit.cpp $(LDFLAGS) -o cpp_explicit

.PHONY: clean
clean:
	rm -f *.o *.a *.so prog_static prog_dyn prog_explicit cpp_static cpp_dyn cpp_explicit
