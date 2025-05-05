scheduler_test.o: ../test/scheduler_test.c ../include/scheduler.h \
 ../include/uid.h ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/scheduler_test.c -o  scheduler_test.o
