hash_table.o: ../src/hash_table.c ../include/hash_table.h \
 ../include/aux_func.h ../include/dlist.h ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/hash_table.c -o  hash_table.o
