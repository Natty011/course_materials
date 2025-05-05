thread_1.o: ../src/thread_1.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/thread_1.c -o  thread_1.o
