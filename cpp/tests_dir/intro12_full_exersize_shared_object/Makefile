
# Makefile אוטומטי לטיפול בקומפילציה דינאמית וסטטית עם ספרייה ב־C וקוד ב־C++

CXX = g++
CC = gcc
CFLAGS = -Wall -fPIC
CXXFLAGS = -std=c++98
LDFLAGS = -L. -lmyc
SRC_C = libc.c
SRC_CPP = main_imp.cpp

OBJ_C = libc_dyn.o
SO_LIB = libmyc.so
A_LIB = libmyc.a

TARGET_SO = cpp_dyn.out
TARGET_A = cpp_static.out

all: dynamic static

dynamic: $(SO_LIB) $(SRC_CPP)
	$(CXX) $(CXXFLAGS) $(SRC_CPP) $(LDFLAGS) -o $(TARGET_SO)

dynamic_force_ld_fix: $(SO_LIB) $(SRC_CPP)
	$(CXX) $(CXXFLAGS) $(SRC_CPP) $(LDFLAGS) -lc -Wl,--copy-dt-needed-entries -o $(TARGET_SO)

static: $(A_LIB) $(SRC_CPP)
	$(CXX) $(CXXFLAGS) $(SRC_CPP) -L. -lmyc -o $(TARGET_A)

$(SO_LIB): $(OBJ_C)
	$(CXX) -shared -o $@ $^

$(A_LIB): $(OBJ_C)
	ar rcs $@ $^

$(OBJ_C): $(SRC_C)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.so *.a *.out

run_dyn:
	LD_LIBRARY_PATH=. ./$(TARGET_SO)

run_static:
	./$(TARGET_A)
