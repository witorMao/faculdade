#Para escrever comentários ##
############################# Makefile ##########################
all: teste
teste: stackchar.o binarytree.o t4.o 
        # O compilador faz a ligação entre os dois objetos
	gcc -o teste stackchar.o binarytree.o t4.o -lm
#-----> Distancia com o botão TAB ### e não com espaços
stackchar.o: stackchar.c stackchar.h
	gcc -o stackchar.o -c stackchar.c 
binarytree.o: binarytree.c binarytree.h
	gcc -o binarytree.o -c binarytree.c 
t4.o: t4.c stackchar.h binarytree.h
	gcc -o t4.o -c t4.c 
clean:
	rm -rf *.o
mrproper: clean
	rm -rf teste
run: teste
	./teste
