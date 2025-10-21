all: compile run

compile:
	gcc src/*.c src/control/*.c src/memory/*.c -o cpu -Wall -O3

run:
	cpu

clean:
	del *.exe
