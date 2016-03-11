all:  binaryTree

binaryTree: main.o binaryTree.o
	gcc main.o binaryTree.o -o binaryTree

main.o: main.c binaryTree.h
	gcc -c main.c

binaryTree.o: binaryTree.c binaryTree.h
	gcc -c binaryTree.c

clean:
	rm main.o binaryTree.o binaryTree
