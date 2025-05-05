pong2.o: ../src/pong2.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/pong2.c -o  pong2.o
