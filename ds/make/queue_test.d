queue_test.o: ../test/queue_test.c ../include/queue.h ../include/slist.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/queue_test.c -o  queue_test.o
