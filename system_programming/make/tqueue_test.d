tqueue_test.o: ../test/tqueue_test.c ../include/utils.h \
 ../include/tqueue.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/tqueue_test.c -o  tqueue_test.o
