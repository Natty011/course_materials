stack.o: ../src/stack.c ../include/stack.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/stack.c -o  stack.o
