recursion.o: ../src/recursion.c ../include/recursion.h ../include/stack.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/recursion.c -o  recursion.o
