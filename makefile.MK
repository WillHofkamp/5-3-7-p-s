CC = gcc
CFLAGS = -Wall -pedantic

main: main.o parseService.o printService.o readerService.o
	$(CC) $(CFLAGS) -o main main.o parseService.o printService.o readerService.o
main.o: main.c parseService.h printService.h
	$(CC) $(CFLAGS) -c main.c
parseService.o: parseService.c parseService.h printService.h readerService.h
	$(CC) $(CFLAGS) -c parseService.c
printService.o: printService.c printService.h
	$(CC) $(CFLAGS) -c printService.c
readerService.o: readerService.c readerService.h
	$(CC) $(CFLAGS) -c readerService.c

clean:
	rm -f main *.o