sort.o: ../src/sort.c ../include/sort.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/sort.c -o  sort.o
