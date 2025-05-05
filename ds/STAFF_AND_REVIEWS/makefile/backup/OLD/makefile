#CC = gcc # Flag for implicit rules
#CFLAGS = -g -Wall # Flag for implicit rules. Turn on debug info
#OBJS = main.o foo.o
all:fooer.out

# Options for release
# CFLAGS = -O -Wall –ansi

fooer.out : main.o foo.o
	gcc $(CFLAGS) main.o foo.o -o fooer.out

main.o : main.c foo.h
	gcc $(CFLAGS) -c main.c

foo.o : foo.c foo.h
	gcc $(CFLAGS) -c foo.c

clean: 
	rm -f *.o fooer.out
	
# Flag for implicit rules. Turn on debug info	
debug: CFLAGS += -ansi -pedantic-errors -Wall -Wextra -g
debug: fooer.out

# Options for release
release: CFLAGS += -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: fooer.out





