CC=gcc
CFLAGS= -O3 -Wall

istravel: istravel.o funcoes.o GraphList.o heap.o Item.o
	$(CC) $(CFLAGS) istravel.o funcoes.o GraphList.o heap.o Item.o -o istravel

istravel.o: istravel.c
	$(CC) -c $(CFLAGS) istravel.c

funcoes.o: funcoes.c funcoes.h
	$(CC) -c $(CFLAGS) funcoes.c

GraphList.o: GraphList.c GraphList.h
	$(CC) -c $(CFLAGS) GraphList.c

heap.o: heap.c heap.h
	$(CC) -c $(CFLAGS) heap.c

Item.o:  Item.h Item.c
	$(CC) -c $(CFLAGS) Item.c

clean::
	rm -f *.o core a.out istravel *~



