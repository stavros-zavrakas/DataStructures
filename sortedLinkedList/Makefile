all:  sortedList

sortedList: main.o sortedLinkedList.o
	gcc main.o sortedLinkedList.o -o sortedList

main.o: main.c sortedLinkedList.h
	gcc -c main.c

sortedLinkedList.o: sortedLinkedList.c sortedLinkedList.h
	gcc -c sortedLinkedList.c

clean:
	rm main.o sortedLinkedList.o sortedList
