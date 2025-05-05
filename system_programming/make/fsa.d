fsa.o: ../src/fsa.c ../include/fsa.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/fsa.c -o  fsa.o
