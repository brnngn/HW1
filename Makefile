
CC = gcc
CFLAGS = -Wall
OBJFILES = hangperson.o functions.o hangtest.o
TARGET = hangperson hangtest


all: $(TARGET)

test: hangtest
	./hangtest

hangperson: hangperson.o functions.o
	$(CC) hangperson.o functions.o -o hangperson $(CFLAGS)

hangtest: hangtest.o functions.o
	$(CC) hangtest.o functions.o -o hangtest $(CFLAGS)

functions.o: hangfunctions.c
	$(CC) -c hangfunctions.c -o functions.o $(CFLAGS)

hangperson.o: hangperson.c
	$(CC) -c hangperson.c -o hangperson.o $(CFLAGS)

hangtest.o: hangtest.c
	$(CC) -c hangtest.c -o hangtest.o $(CFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~


