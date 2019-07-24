#
# 1.1.cpp
#
# chapter 1 introduction
# modern cpp tutorial
#
# created by changkun at changkun.de
# https://github.com/changkun/modern-cpp-tutorial
#

C = gcc
CXX = clang++

SOURCE_C = foo.c
OBJECTS_C = foo.o 

SOURCE_CXX = 1.1.c.and.cpp

TARGET = 1.1.out
LDFLAGS_COMMON = -std=c++2a

all:
	$(C) -c $(SOURCE_C)
	$(CXX) $(SOURCE_CXX) $(OBJECTS_C) $(LDFLAGS_COMMON) -o $(TARGET)
clean:
	rm -rf *.o $(TARGET)
