#CC = gcc # Flag for implicit rules
#OBJS = main.o foo.o

all:vector_test

# Options for release


vector_test : vector_test.o vector.o
	gcc $(CFLAGS) vector_test.o vector.o -o vector_test

vector_test.o : vector_test.c vector.h
	gcc $(CFLAGS) -c vector_test.c 

vector.o : vector.c vector.h
	gcc $(CFLAGS) -c vector.c

clean: 
	rm -f *.o vector_test
	#rm -f fooer.out $(OBLS)
# Flag for implicit rules. Turn on debug info	
debug: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
debug: vector_test

# Options for release
release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: vector_test

TOUCH = vector_test vector_test.c vector.c
touch: 
	touch $(TOUCH)

