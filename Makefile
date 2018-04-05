CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
OBJ = LinkedList.o UnitTestLinkedList.o FileIO.o UnitTestFileIO.o ActionFunc.o SpellChecker.o

SpellChecker: SpellChecker.o ActionFunc.o FileIO.o LinkedList.o check.o
	$(CC) $(CFLAGS) SpellChecker.o ActionFunc.o FileIO.o LinkedList.o check.o -o SpellChecker

SpellChecker.o: SpellChecker.c ActionFunc.o FileIO.o
	$(CC) $(CFLAGS) -c SpellChecker.c

ActionFunc.o: ActionFunc.c ActionFunc.h check.h
	$(CC) $(CFLAGS) -c ActionFunc.c

UnitTestFileIO: UnitTestFileIO.o FileIO.o LinkedList.o
	$(CC) $(CFLAGS) LinkedList.o FileIO.o UnitTestFileIO.o -o UnitTestFileIO

UnitTestFileIO.o: UnitTestFileIO.c FileIO.o
	$(CC) $(CFLAGS) -c UnitTestFileIO.c

FileIO.o: FileIO.c FileIO.h spellconf.h LinkedList.o
	$(CC) $(CFLAGS) -c FileIO.c

UnitTestLinkedList: UnitTestLinkedList.o
	$(CC) $(CFLAGS) LinkedList.o UnitTestLinkedList.o -o UnitTestLinkedList

UnitTestLinkedList.o: UnitTestLinkedList.c LinkedList.o
	$(CC) $(CFLAGS) -c UnitTestLinkedList.c

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

clean:
	rm -f $(OBJ) UnitTestLinkedList UnitTestFileIO
