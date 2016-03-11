all:	list.out

list.out:	main.o linkedList.o
	gcc main.o linkedList.o -o list.out

main.o: main.c linkedList.h
	gcc -c main.c

linkedList.o: linkedList.c linkedList.h
	gcc -c linkedList.c

clean:
	rm main.o linkedList.o list.out
