cbuffer_test.o: ../test/cbuffer_test.c ../include/cbuffer.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/cbuffer_test.c -o  cbuffer_test.o
