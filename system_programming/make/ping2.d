ping2.o: ../src/ping2.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/ping2.c -o  ping2.o
