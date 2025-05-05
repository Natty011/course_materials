tqueue.o: ../src/tqueue.c ../include/tqueue.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/tqueue.c -o  tqueue.o
