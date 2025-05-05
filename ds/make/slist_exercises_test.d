slist_exercises_test.o: ../test/slist_exercises_test.c \
 ../include/slist_exercises.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/slist_exercises_test.c -o  slist_exercises_test.o
