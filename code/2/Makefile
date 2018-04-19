all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	clang++ $< -o $@ -std=c++17 -pedantic

clean:
	rm *.out