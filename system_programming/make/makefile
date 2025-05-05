CC = gcc
OBJS = $(patsubst $(SRC_PATH)%.c,%.o,$(wildcard $(SRC_PATH)*.c))
TEST_OBJS = $(patsubst $(TEST_PATH)%.c,%.o,$(wildcard $(TEST_PATH)*_test.c))
TARGETS = $(patsubst $(TEST_PATH)%_test.c,%.out,$(wildcard $(TEST_PATH)*_test.c))


CFLAGS = -ansi -pedantic-errors -Wall -Wextra 
DEBUG = -g
RELEASE = -DNDEBUG -O3
CPPFLAGS = -I $(HEAD_PATH)

SRC_PATH = ../src/
TEST_PATH = ../test/
HEAD_PATH = ../include/

.PHONY : clean test debug release all

all : release debug

release : CFLAGS += $(RELEASE)
release : libds_release.so

debug : CFLAGS += $(DEBUG)
debug : libds_debug.so

test : $(TARGETS) 

%.out : %_test.o | libds_debug.so
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)  $< -L . -lds_debug -Wl,-rpath,.

libds_%.so : $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared $^ -o $@

-include $(OBJS:.o=.d) $(TEST_OBJS:_test.o=_test.d)

%.d : $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MM $< -MF $@
	echo "\t$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG) -c -fPIC $< -o  $(basename $@).o" >> $@

%_test.d : $(TEST_PATH)%_test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MM $< -MF $@
	echo "\t$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG) -c $< -o  $(basename $@).o" >> $@


clean : 
	$(RM) *.o *.d *.out

