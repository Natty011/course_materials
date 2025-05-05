bst_test.o: ../test/bst_test.c ../include/bst.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/bst_test.c -o  bst_test.o
