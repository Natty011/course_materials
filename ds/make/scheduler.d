scheduler.o: ../src/scheduler.c ../include/scheduler.h ../include/uid.h \
 ../include/pqueue.h ../include/sort_list.h ../include/dlist.h \
 ../include/aux_func.h ../include/task.h ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/scheduler.c -o  scheduler.o
