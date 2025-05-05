recursion_test.o: ../test/recursion_test.c ../include/recursion.h \
 ../include/stack.h ../include/stack.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/recursion_test.c -o  recursion_test.o
