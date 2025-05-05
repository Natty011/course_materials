slist.o: ../src/slist.c ../include/slist.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/slist.c -o  slist.o
