slist_test.o: ../test/slist_test.c ../include/slist.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/slist_test.c -o  slist_test.o
