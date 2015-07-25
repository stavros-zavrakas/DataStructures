all:  doubleList

doubleList: main.o doubleLinkedList.o
	gcc main.o doubleLinkedList.o -o doubleList

main.o: main.c doubleLinkedList.h
	gcc -c main.c

doubleLinkedList.o: doubleLinkedList.c doubleLinkedList.h
	gcc -c doubleLinkedList.c

clean:
	rm main.o doubleLinkedList.o doubleList
