#include "Server.h"

void Server::listenSocket(){
	int nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0)
    	throw runtime_error(string("Can't set queue size.")); 
}
