
CC=g++

CFLAGS=-c -Wall -std=c++14

NAMES=NetworkEntity Server Client HttpRequest

all: http

http: main.o $(addsuffix .o,$(NAMES))
	$(CC) main.o $(addsuffix .o,$(NAMES)) -o http -lpthread

main.o: $(addsuffix .h,$(NAMES)) $(addsuffix .cpp,$(NAMES)) main.cpp Constants.h
	$(CC) $(CFLAGS) main.cpp

NetworkEntity.o: NetworkEntity.cpp NetworkEntity.h
	$(CC) $(CFLAGS) NetworkEntity.cpp

Server.o: Server.cpp Server.h NetworkEntity.o 
	$(CC) $(CFLAGS) Server.cpp

Client.o: Client.cpp Client.h NetworkEntity.o 
	$(CC) $(CFLAGS) Client.cpp
HttpRequest.o: HttpRequest.h HttpRequest.cpp Constants.h 
	$(CC) $(CFLAGS) HttpRequest.cpp
clean:
	rm *o http

