bst.o: ../src/bst.c ../include/bst.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/bst.c -o  bst.o
