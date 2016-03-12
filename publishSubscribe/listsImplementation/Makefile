all: pubSub.out

pubSub.out: main.o doubleLinkedList.o
	gcc main.o doubleLinkedList.o -o pubSub.out

main.o: main.c
	gcc -c main.c

doubleLinkedList.o: ../../doubleLinkedList/doubleLinkedList.c
	gcc -c ../../doubleLinkedList/doubleLinkedList.c

clean:
	rm main.o doubleLinkedList.o pubSub.out
