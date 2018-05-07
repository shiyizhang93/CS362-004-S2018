CC = gcc

CFLAGS = -g -Wall -std=c90

all: testme

testme : testme.o
	$(CC) $(CFLAGS) -o $@ $^

testme.o : testme.c

clean :
	-rm *.o
	-rm testme