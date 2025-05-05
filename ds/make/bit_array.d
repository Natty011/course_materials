bit_array.o: ../src/bit_array.c ../include/bit_array.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/bit_array.c -o  bit_array.o
