#CC = gcc # Flag for implicit rules
#OBJS = main.o foo.o

all:slist_test

# Options for release


slist_test : slist_test.o slist.o
	gcc $(CFLAGS) slist_test.o slist.o -o slist_test

slist_test.o : slist_test.c slist.h
	gcc $(CFLAGS) -c slist_test.c 

slist.o : slist.c slist.h
	gcc $(CFLAGS) -c slist.c

clean: 
	rm -f *.o slist_test
	#rm -f fooer.out $(OBLS)
# Flag for implicit rules. Turn on debug info	
debug: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
debug: slist_test

# Options for release
release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: slist_test

TOUCH = slist_test slist_test.c slist.c
touch: 
	touch $(TOUCH)



# gd slist.c slist_test.c -o slist_test
# gc slist.c slist_test.c -o slist_test
# ./slist_test
# vlg ./slist_test
