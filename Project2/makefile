all: pre sort shhh

pre: pre.c
	gcc -o pre.o pre.c -std=c99

sort: sort.c
	gcc -o sort.o sort.c -std=c99

shhh: shhh.c
	gcc -o shhh.o shhh.c -std=c99

.PHONY: clean

clean:
	rm -f *.o
