all: pubSub.out

pubSub.out: main.o doubleLinkedList.o linkedList.o
	gcc main.o doubleLinkedList.o linkedList.o -o pubSub.out

main.o: main.c
	gcc -c main.c

doubleLinkedList.o: ../../doubleLinkedList/doubleLinkedList.c
	gcc -c ../../doubleLinkedList/doubleLinkedList.c

linkedList.o: ../../linkedList/linkedList.c
	gcc -c ../../linkedList/linkedList.c

clean:
	rm main.o doubleLinkedList.o pubSub.out
