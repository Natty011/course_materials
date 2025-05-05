thread_3.o: ../src/thread_3.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/thread_3.c -o  thread_3.o
