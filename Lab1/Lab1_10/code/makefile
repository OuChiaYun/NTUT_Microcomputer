CXXFLAGS=-std=c++11
CROSS_COMPILE = aarch64-linux-gnu-
CXX= $(CROSS_COMPILE)g++   
LD = $(CROSS_COMPILE)ld        
INCLUDE=sort.h ellipse.h triangle.h circular_sector.h shape.h
OBJ=sort.o ellipse.o triangle.o circular_sector.o main.o
SRC=sort.cpp ellipse.cpp triangle.cpp circular_sector.cpp main.cpp
EXE=sha

all:$(EXE)
$(EXE):$(OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $?
$(OBJ):$(SRC)
	$(CXX) -c $^

clean: 
	rm -f *.o
	rm -f sha