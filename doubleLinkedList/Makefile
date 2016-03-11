all:  doubleList.out

doubleList.out: main.o doubleLinkedList.o
	gcc main.o doubleLinkedList.o -o doubleList.out

main.o: main.c doubleLinkedList.h
	gcc -c main.c

doubleLinkedList.o: doubleLinkedList.c doubleLinkedList.h
	gcc -c doubleLinkedList.c

clean:
	rm main.o doubleLinkedList.o doubleList.out
