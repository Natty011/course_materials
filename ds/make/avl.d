avl.o: ../src/avl.c ../include/avl.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/avl.c -o  avl.o
