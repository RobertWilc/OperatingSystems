all: partA partB

partA: partA.c
	gcc -o partA.o partA.c -pthread -std=c99 -D_GNU_SOURCE

partB: partB.c
	gcc -o partB.o partB.c -pthread -std=c99 -D_GNU_SOURCE



.PHONY: clean

clean:
	rm -rf *.o
