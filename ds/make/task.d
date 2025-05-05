task.o: ../src/task.c ../include/task.h ../include/uid.h \
 ../include/scheduler.h ../include/uid.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/task.c -o  task.o
