all: pubSub.out

pubSub.out: main.o doubleLinkedList.o linkedList.o sortedLinkedList.o
	gcc main.o doubleLinkedList.o linkedList.o sortedLinkedList.o -o pubSub.out

main.o: main.c
	gcc -c main.c

doubleLinkedList.o: ../../doubleLinkedList/doubleLinkedList.c
	gcc -c ../../doubleLinkedList/doubleLinkedList.c

linkedList.o: ../../linkedList/linkedList.c
	gcc -c ../../linkedList/linkedList.c

sortedLinkedList.o: ../../sortedLinkedList/sortedLinkedList.c
	gcc -c ../../sortedLinkedList/sortedLinkedList.c

clean:
	rm main.o doubleLinkedList.o pubSub.out
