CC = gcc
CFLAGS = -Wall -pedantic
OBJECTS = main.o printService.o parseService.o readerService.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)
main.o: main.c printService.h parseService.h
	$(CC) $(CFLAGS) -c main.c
printService.o: printService.c printService.h parseService.h readerService.h
	$(CC) $(CFLAGS) -c printService.c
parseService.o: parseService.c parseService.h 
	$(CC) $(CFLAGS) -c parseService.c
readerService.o: readerService.c readerService.h
	$(CC) $(CFLAGS) -c readerService.c

clean:
	rm -f main *.o