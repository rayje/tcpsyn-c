CXX = gcc
CXXFLAGS = -Wall -g -pthread

server: server.o util.o
	$(CXX) $(CXXFLAGS) -o server server.o util.o

client: client.o util.o
	$(CXX) $(CXXFLAGS) -o client client.o util.o

%.o: %.c
	$(CXX) -c  $(CXXFLAGS) $*.c -o $*.o

client.o: client.c util.h
	$(CXX) $(CXXFLAGS) -c client.c

server.o: server.c util.h
	$(CXX) $(CXXFLAGS) -c server.c

util.o: util.h

clean:
	rm -f client server *.o