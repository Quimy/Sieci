
CC=g++

CFLAGS=-c -Wall -std=c++14

NAMES=NetworkEntity Server

all: http

http: main.o $(addsuffix .o,$(NAMES))
	$(CC) main.o $(addsuffix .o,$(NAMES)) -o http

main.o: $(addsuffix .h,$(NAMES)) $(addsuffix .cpp,$(NAMES))
	$(CC) $(CFLAGS) main.cpp

NetworkEntity.o: NetworkEntity.cpp NetworkEntity.h
	$(CC) $(CFLAGS) NetworkEntity.cpp

Server.o: Server.cpp Server.h NetworkEntity.o 
	$(CC) $(CFLAGS) Server.cpp

clean:
	rm *o http

