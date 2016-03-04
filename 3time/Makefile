main:
	gcc -g -w -c test1.c

lib:
	gcc -g -w -c list2.c 

all: lib main
	gcc -g -o test list2.o test1.o

clean:
	rm test *.o
