uid.o: ../src/uid.c ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/uid.c -o  uid.o
