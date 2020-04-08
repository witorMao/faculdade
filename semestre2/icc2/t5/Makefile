#Para escrever comentários ##
############################# Makefile ##########################
all: teste
teste: dynamiclist.o t5.o
	gcc -o teste dynamiclist.o t5.o
dynamiclist.o: dynamiclist.c dynamiclist.h
	gcc -o dynamiclist.o -c dynamiclist.c 
t5.o: t5.c dynamiclist.h
	gcc -o t5.o -c t5.c
clean:
	rm -rf *.o
mrproper: clean
	rm -rf teste
run: teste
	./teste

