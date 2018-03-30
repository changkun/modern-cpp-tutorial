#
# 1.1.cpp
#
# chapter 1 introduction
# c++1x tutorial
#
# created by changkun at changkun.de
#

C = gcc
CXX = g++

SOURCE_C = foo.c
OBJECTS_C = foo.o 

SOURCE_CXX = 1.1.cpp

TARGET = 1.1
LDFLAGS_COMMON = -std=c++1z

all:
	$(C) -c $(SOURCE_C)
	$(CXX) $(SOURCE_CXX) $(OBJECTS_C) $(LDFLAGS_COMMON) -o $(TARGET)
clean:
	rm -rf *.o $(TARGET)
