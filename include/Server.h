#pragma once
#include "NetworkEntity.h"

class Server: public NetworkEntity{

	const int QUEUE_SIZE = 5;

public:
	Server(int port):NetworkEntity(port){
		stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	};
	void listenSocket();
	

};