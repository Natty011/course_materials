vector.o: ../src/vector.c ../include/vector.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/vector.c -o  vector.o
