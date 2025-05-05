stack_test.o: ../test/stack_test.c ../include/stack.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/stack_test.c -o  stack_test.o
