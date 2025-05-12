# Makefile to build inline_test with and without optimization

CXX = g++
CXXFLAGS = -std=c++98

all: no_opt opt

no_opt: inline_test.cpp
	$(CXX) $(CXXFLAGS) -O0 -o no_opt.out inline_test.cpp

opt: inline_test.cpp
	$(CXX) $(CXXFLAGS) -O2 -o opt.out inline_test.cpp

clean:
	rm -f *.out
