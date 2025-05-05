heap_scheduler.o: ../src/heap_scheduler.c ../include/heap_scheduler.h \
 ../include/uid.h ../include/heap_pq.h ../include/heap.h \
 ../include/aux_func.h ../include/task.h ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/heap_scheduler.c -o  heap_scheduler.o
