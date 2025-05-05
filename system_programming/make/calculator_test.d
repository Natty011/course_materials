calculator_test.o: ../test/calculator_test.c ../include/calculator.h \
 ../include/stack.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/calculator_test.c -o  calculator_test.o
