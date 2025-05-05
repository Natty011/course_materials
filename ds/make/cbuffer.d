cbuffer.o: ../src/cbuffer.c ../include/cbuffer.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/cbuffer.c -o  cbuffer.o
