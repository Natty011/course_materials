slist_exercises.o: ../src/slist_exercises.c ../include/slist_exercises.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/slist_exercises.c -o  slist_exercises.o
