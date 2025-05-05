vector_test.o: ../test/vector_test.c ../include/vector.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/vector_test.c -o  vector_test.o
