vsa_test.o: ../test/vsa_test.c ../include/vsa.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/vsa_test.c -o  vsa_test.o
