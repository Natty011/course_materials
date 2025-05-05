avl_test.o: ../test/avl_test.c ../include/avl.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/avl_test.c -o  avl_test.o
