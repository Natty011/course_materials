heap_test.o: ../test/heap_test.c ../include/heap.h ../include/aux_func.h \
 ../include/vector.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/heap_test.c -o  heap_test.o
