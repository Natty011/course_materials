dlist_test.o: ../test/dlist_test.c ../include/dlist.h \
 ../include/aux_func.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/dlist_test.c -o  dlist_test.o
