#CC = gcc # Flag for implicit rules
#OBJS = main.o foo.o

all:fooer.out

# Options for release


fooer.out : main.o foo.o
	gcc $(CFLAGS) main.o foo.o -o fooer.out

main.o : main.c foo.h
	gcc $(CFLAGS) -c main.c 

foo.o : foo.c foo.h
	gcc $(CFLAGS) -c foo.c

clean: 
	rm -f *.o fooer.out
	#rm -f fooer.out $(OBLS)
# Flag for implicit rules. Turn on debug info	
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
debug: fooer.out

# Options for release
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: fooer.out

TOUCH = fooer.out main.c foo.c
touch: 
	touch $(TOUCH)

