vsa.o: ../src/vsa.c ../include/vsa.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/vsa.c -o  vsa.o
