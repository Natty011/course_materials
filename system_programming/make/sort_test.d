sort_test.o: ../test/sort_test.c ../include/sort.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/sort_test.c -o  sort_test.o
