all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	clang++ $< -o $@ -std=c++2a -Xclang -fconcepts-ts -pedantic

clean:
	rm *.out