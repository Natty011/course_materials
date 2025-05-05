heap_pq.o: ../src/heap_pq.c ../include/heap_pq.h ../include/heap.h \
 ../include/aux_func.h ../include/heap.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/heap_pq.c -o  heap_pq.o
