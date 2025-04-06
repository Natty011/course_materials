
ROOT := ..
CC = gcc

SRC_PATH = $(ROOT)/src/
TEST_PATH = ../test
HEAD_PATH = $(ROOT)/include/
DS_SRC_PATH = $(ROOT)/../ds/src/
DS_INC_PATH = $(ROOT)/../ds/include/
TEST_PATH = $(ROOT)/test/

BIN_DIR = $(ROOT)/bin
DEBUG_DIR = $(BIN_DIR)/debug
RELEASE_DIR = $(BIN_DIR)/release

# file related to watchdog
SRC_FILES = $(SRC_PATH)watchdog.c
DS_SRC_FILES = \
	$(DS_SRC_PATH)scheduler.c \
	$(DS_SRC_PATH)task.c \
	$(DS_SRC_PATH)uid.c \
	$(DS_SRC_PATH)pqueue.c \
	$(DS_SRC_PATH)sort_list.c \
	$(DS_SRC_PATH)dlist.c

TEST_SRCS = $(wildcard $(TEST_PATH)*_app.c)
DEBUG_TARGETS = $(patsubst %.c,$(DEBUG_DIR)/%.out,$(notdir $(TEST_SRCS)))
RELEASE_TARGETS = $(patsubst %.c,$(RELEASE_DIR)/%.out,$(notdir $(TEST_SRCS)))

DEBUG_OBJS = $(patsubst %.c,$(DEBUG_DIR)/%.o,$(notdir $(TEST_SRCS)))
RELEASE_OBJS = $(patsubst %.c,$(RELEASE_DIR)/%.o,$(notdir $(TEST_SRCS)))

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -fPIC
DEBUG = -g
RELEASE = -DNDEBUG -O3
CPPFLAGS = -I$(HEAD_PATH) -I$(DS_INC_PATH) -I$(TEST_PATH)

LIB_NAME = libwatchdog

.PHONY: all debug release test clean

all: release debug

debug: prepare $(DEBUG_DIR)/$(LIB_NAME)_debug.so $(DEBUG_OBJS) $(DEBUG_TARGETS)

release: prepare $(RELEASE_DIR)/$(LIB_NAME)_release.so $(RELEASE_OBJS) $(RELEASE_TARGETS)

prepare:
	@mkdir -p $(DEBUG_DIR) $(RELEASE_DIR)

test: debug

$(DEBUG_DIR)/%.out: $(DEBUG_DIR)/%.o $(DEBUG_DIR)/$(LIB_NAME)_debug.so
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ -L$(abspath $(DEBUG_DIR)) -l:$(notdir $(DEBUG_DIR)/$(LIB_NAME)_debug.so) -Wl,-rpath=$(abspath $(DEBUG_DIR))

$(RELEASE_DIR)/%.out: $(RELEASE_DIR)/%.o $(RELEASE_DIR)/$(LIB_NAME)_release.so
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ -L$(abspath $(RELEASE_DIR)) -l:$(notdir $(RELEASE_DIR)/$(LIB_NAME)_release.so) -Wl,-rpath=$(abspath $(RELEASE_DIR))

$(RELEASE_DIR)/%.o: $(SRC_PATH)%.c | prepare
	$(CC) $(CFLAGS) $(RELEASE) $(CPPFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(RELEASE_DIR)/%.o: $(DS_SRC_PATH)%.c | prepare
	$(CC) $(CFLAGS) $(RELEASE) $(CPPFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(DEBUG_DIR)/%.o: $(SRC_PATH)%.c | prepare
	$(CC) $(CFLAGS) $(DEBUG) $(CPPFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(DEBUG_DIR)/%.o: $(DS_SRC_PATH)%.c | prepare
	$(CC) $(CFLAGS) $(DEBUG) $(CPPFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(DEBUG_DIR)/%.o: $(TEST_PATH)%.c | prepare
	$(CC) $(CFLAGS) $(DEBUG) $(CPPFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(RELEASE_DIR)/%.o: $(TEST_PATH)%.c | prepare
	$(CC) $(CFLAGS) $(RELEASE) $(CPPFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(RELEASE_DIR)/$(LIB_NAME)_release.so: \
	$(patsubst $(SRC_PATH)%.c,$(RELEASE_DIR)/%.o,$(SRC_FILES)) \
	$(patsubst $(DS_SRC_PATH)%.c,$(RELEASE_DIR)/%.o,$(DS_SRC_FILES))
	$(CC) $(CFLAGS) $(RELEASE) $(CPPFLAGS) -shared $^ -o $@

$(DEBUG_DIR)/$(LIB_NAME)_debug.so: \
	$(patsubst $(SRC_PATH)%.c,$(DEBUG_DIR)/%.o,$(SRC_FILES)) \
	$(patsubst $(DS_SRC_PATH)%.c,$(DEBUG_DIR)/%.o,$(DS_SRC_FILES))
	$(CC) $(CFLAGS) $(DEBUG) $(CPPFLAGS) -shared $^ -o $@

-include $(wildcard $(DEBUG_DIR)/*.d) $(wildcard $(RELEASE_DIR)/*.d)


bin/debug/wd_test.out: test/wd_test.c bin/debug/watchdog.o bin/debug/utils.o
	gcc -ansi -pedantic-errors -Wall -Wextra -pthread -o $@ $^


clean:
	rm -f $(DEBUG_DIR)/*.o $(DEBUG_DIR)/*.d $(DEBUG_DIR)/*.out $(DEBUG_DIR)/*.so \
	      $(RELEASE_DIR)/*.o $(RELEASE_DIR)/*.d $(RELEASE_DIR)/*.out $(RELEASE_DIR)/*.so



#bin/debug/watchdog_test.out: src/wd_test.c
#	gcc -ansi -pedantic-errors -Wall -Wextra src/wd_test.c -Lbin/debug -lwd -o bin/debug/watchdog_test.out


#wd_test.out: wd_test.c watchdog.o utils.o
#	gcc -ansi -pedantic-errors -Wall -Wextra -pthread -o $@ $^

