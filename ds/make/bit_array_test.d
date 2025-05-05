bit_array_test.o: ../test/bit_array_test.c ../include/bit_array.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/bit_array_test.c -o  bit_array_test.o
