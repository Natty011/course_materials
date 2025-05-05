heap_pq_test.o: ../test/heap_pq_test.c ../include/heap_pq.h \
 ../include/heap.h ../include/aux_func.h ../include/heap.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/heap_pq_test.c -o  heap_pq_test.o
