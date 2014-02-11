CFLAGS=-Wall
CC=gcc

all: client server

client:
	$(CC) client.c -o $@ $^ $(CFLAGS)

server:
	$(CC) server.c -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f js client server code.zip

zip:
	zip code.zip client.c makefile server.c util.h