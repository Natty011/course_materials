sort_list_test.o: ../test/sort_list_test.c ../include/sort_list.h \
 ../include/dlist.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/sort_list_test.c -o  sort_list_test.o
