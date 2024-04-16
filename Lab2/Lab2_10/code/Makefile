CXXFLAGS=-std=c++11
CROSS_COMPILE = aarch64-linux-gnu-
CXX= $(CROSS_COMPILE)g++   
LD = $(CROSS_COMPILE)ld        
OBJ=main.o
SRC=main.cpp
EXE=sha

all:$(EXE)
$(EXE):$(OBJ)
	$(CXX) $(CFLAGS) -o $@ $?
$(OBJ):$(SRC)
	$(CXX) -c $^

clean: 
	rm -f *.o
	rm -f sha


