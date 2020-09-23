CC = gcc
CFLAGS = -Wall -pedantic
OBJECTS = main.o parseService.o printService.o readerService.o

main: $(OBJECTS)
 $(CC) $(CFLAGS) -o 537ps $(OBJECTS)

main.o: main.c parseService.h printService.h readerService.h
 $(CC) $(CFLAGS) -c 537ps.c

printService.o: printService.c printService.h readerService.h parseService.h
 $(CC) $(CFLAGS) -c printService.c

readerService.o: readerService.c readerService.h
 $(CC) $(CFLAGS) -c readerService.c

parseService.o: parseService.c parseService.h
 $(CC) $(CFLAGS) -c parseService.c

clean:
 rm -f $(OBJECTS) main