pqueue.o: ../src/pqueue.c ../include/pqueue.h ../include/sort_list.h \
 ../include/dlist.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/pqueue.c -o  pqueue.o
