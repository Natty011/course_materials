thread_4.o: ../src/thread_4.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/thread_4.c -o  thread_4.o
