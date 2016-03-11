main:
	gcc -g -c main.c

lib:
	gcc -g -c list2.c 

all: lib main
	gcc -g -o srt list2.o main.o

clean:
	rm test *.o
