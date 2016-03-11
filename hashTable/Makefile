all: hashTable.out

hashTable.out: main.o hashTable.o
	gcc main.o hashTable.o -o hashTable.out

main.o: main.c hashTable.h
	gcc -c main.c

hashTable.o: hashTable.c hashTable.h
	gcc -c hashTable.c

clean:
	rm main.o hashTable.o hashTable.out
