uid_test.o: ../test/uid_test.c ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/uid_test.c -o  uid_test.o
