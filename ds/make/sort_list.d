sort_list.o: ../src/sort_list.c ../include/dlist.h ../include/aux_func.h \
 ../include/sort_list.h ../include/dlist.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/sort_list.c -o  sort_list.o
