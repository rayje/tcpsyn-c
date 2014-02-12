CXX = gcc
CXXFLAGS = -Wall -g -pthread

main: server client

server: server.o util.o
	$(CXX) $(CXXFLAGS) -o server server.o util.o

client: client.o util.o
	$(CXX) $(CXXFLAGS) -o client client.o util.o

%.o: %.c
	$(CXX) -c  $(CXXFLAGS) $*.c -o $*.o

clean:
	rm -f client server *.o