knights_tour.o: ../src/knights_tour.c ../include/pqueue.h \
 ../include/sort_list.h ../include/dlist.h ../include/aux_func.h \
 ../include/knights_tour.h ../include/pqueue.h ../include/bit_array.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/knights_tour.c -o  knights_tour.o
