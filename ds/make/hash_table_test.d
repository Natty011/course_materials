hash_table_test.o: ../test/hash_table_test.c ../include/hash_table.h \
 ../include/aux_func.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/hash_table_test.c -o  hash_table_test.o
