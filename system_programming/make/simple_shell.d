simple_shell.o: ../src/simple_shell.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/simple_shell.c -o  simple_shell.o
