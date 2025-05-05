calculator.o: ../src/calculator.c ../include/stack.h \
 ../include/calculator.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/calculator.c -o  calculator.o
