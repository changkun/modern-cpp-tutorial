#
# modern cpp tutorial
#
# created by changkun at changkun.de
# https://github.com/changkun/modern-cpp-tutorial
#

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	clang++ $< -o $@ -std=c++2a -pedantic

clean:
	rm *.out