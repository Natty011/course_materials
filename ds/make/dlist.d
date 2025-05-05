dlist.o: ../src/dlist.c ../include/dlist.h ../include/aux_func.h \
 ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/dlist.c -o  dlist.o
