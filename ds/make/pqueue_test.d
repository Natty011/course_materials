pqueue_test.o: ../test/pqueue_test.c ../include/pqueue.h \
 ../include/sort_list.h ../include/dlist.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/pqueue_test.c -o  pqueue_test.o
