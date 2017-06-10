all: hexeditplus

hexeditplus: hexeditplus.o
	gcc -g -m32 -Wall -o hexeditplus hexeditplus.o

hexeditplus.o: hexeditplus.c
	gcc -g -m32 -Wall -Iinclude -c -o hexeditplus.o hexeditplus.c
	
.PHONY: clean

clean:
	rm -f *.o hexeditplus