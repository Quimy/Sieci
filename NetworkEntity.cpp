#include "NetworkEntity.h"

NetworkEntity::NetworkEntity(int port){
	memset(&stAddr, 0, sizeof(struct sockaddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_port = htons(port);

    nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(nSocket<0) 
    	throw runtime_error(string("Can't create a socket."));

    int nFoo=1;
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));
}
void NetworkEntity::bindSocket(){
	int nBind = bind(nSocket, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
    if (nBind < 0)
    	throw runtime_error(string("Can't bind a name to a socket."));  
}
NetworkEntity::~NetworkEntity(){
	close(nSocket);
}