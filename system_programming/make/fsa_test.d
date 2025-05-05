fsa_test.o: ../test/fsa_test.c ../include/fsa.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/fsa_test.c -o  fsa_test.o
