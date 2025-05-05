v_sem.o: ../src/v_sem.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/v_sem.c -o  v_sem.o
