#
# Makefile
#
# exercise solution 7.1 - chapter 7
# modern cpp tutorial
#
# created by changkun at changkun.de/modern-cpp
#

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	clang++ $< -o $@ -std=c++2a -pedantic

clean:
	rm *.out