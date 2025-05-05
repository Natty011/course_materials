heap_scheduler_test.o: ../test/heap_scheduler_test.c \
 ../include/heap_scheduler.h ../include/uid.h ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/heap_scheduler_test.c -o  heap_scheduler_test.o
