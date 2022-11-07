	CC = g++
	CFLAGS = -std=c++11

all: src/ClientMain.cpp src/ServerMain.cpp Server.o Client.o
	$(CC) $(CFLAGS) -pthread src/ServerMain.cpp Server.o -o TCPServerClients_server
	$(CC) $(CFLAGS) -pthread src/ClientMain.cpp Client.o -o TCPServerClients_client

Server.o: src/Server.cpp src/Server.h src/CommonHead.h
	$(CC) $(CFLAGS) -c src/Server.cpp

Client.o: src/Client.cpp src/Client.h src/CommonHead.h
	$(CC) $(CFLAGS) -c src/Client.cpp

clean:
	rm -f *.o TCPServerClients_server TCPServerClients_client