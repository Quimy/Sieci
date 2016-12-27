#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdexcept>
#include <string.h>
#include <string>

using namespace  std;

class NetworkEntity{
protected:
	int nSocket;
	struct sockaddr_in stAddr;
public:
	NetworkEntity(){};
	NetworkEntity(int port);
	void bindSocket();
	int getSocket(){return nSocket;};
	~NetworkEntity();
};