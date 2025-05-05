queue.o: ../src/queue.c ../include/slist.h ../include/queue.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/queue.c -o  queue.o
