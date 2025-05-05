heap.o: ../src/heap.c ../include/heap.h ../include/aux_func.h \
 ../include/vector.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/heap.c -o  heap.o
