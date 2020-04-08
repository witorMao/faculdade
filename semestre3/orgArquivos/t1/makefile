all: t1
t1: biblioT1.o mainT1.o
	gcc -o t1 -O3 -g biblioT1.o mainT1.o 
biblioT1.o: biblioT1.c biblioT1.h
	gcc -o biblioT1.o -c biblioT1.c 
mainT1.o: mainT1.c biblioT1.h
	gcc -o mainT1.o -c mainT1.c 
clean:
	rm -rf *.o
mrproper: clean
	rm -rf t1
run: t1
	./t1