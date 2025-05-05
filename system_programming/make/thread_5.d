thread_5.o: ../src/thread_5.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/thread_5.c -o  thread_5.o
