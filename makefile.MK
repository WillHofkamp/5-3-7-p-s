CC = gcc
CFLAGS = -Wall -pedantic
OBJECTS = 537ps.o printService.o parseService.o readerService.o

537ps: $(OBJECTS)
	$(CC) $(CFLAGS) -o 537ps $(OBJECTS)
537ps.o: 537ps.c printService.h parseService.h
	$(CC) $(CFLAGS) -c 537ps.c
printService.o: printService.c printService.h parseService.h readerService.h
	$(CC) $(CFLAGS) -c printService.c
parseService.o: parseService.c parseService.h 
	$(CC) $(CFLAGS) -c parseService.c
readerService.o: readerService.c readerService.h
	$(CC) $(CFLAGS) -c readerService.c

clean:
	rm -f 537ps *.o