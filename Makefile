all: compile run

compile:
	g++ -std=c++17 *.cpp

run:
	./a.out