knights_tour_test.o: ../test/knights_tour_test.c \
 ../include/knights_tour.h ../include/pqueue.h ../include/sort_list.h \
 ../include/dlist.h ../include/aux_func.h ../include/bit_array.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/knights_tour_test.c -o  knights_tour_test.o
