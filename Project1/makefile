all: pre sort num3

pre: pre.c
	gcc -o pre.o pre.c -std=c99

sort: sort.c
	gcc -o sort.o sort.c -std=c99

num3: num3.c
	gcc -o num3.o num3.c -std=c99

.PHONY: clean

clean:
	rm -rf *.o
