#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <thread>
#include <memory>

#include "Server.h"
#include "Client.h"
using namespace std;
#define SERVER_PORT 7070

void clientRequest(int cl){
	int odp = 0;
	cout<<"Enter thread"<<endl;
	int bufSize = 1000;
    char bufor[bufSize];
    memset(&bufor, 0, bufSize);
    string message;
	while((odp = read (cl, bufor, bufSize))>0){
		cout<<bufor;
		message+=bufor;
		memset(&bufor, 0, bufSize);
	}
	cout<<message<<endl;
	cout<<"End of thread"<<endl;
	close(cl);
}
int main(int argc, char* argv[])
{
   int nClientSocket;
   socklen_t nTmp;
   struct sockaddr_in stClientAddr;
   Server server(SERVER_PORT);

   server.bindSocket();
   
   server.listenSocket();
   while(1)
   {
       /* block for connection request */
        nTmp = sizeof(struct sockaddr);
        nClientSocket = accept(server.getSocket(), (struct sockaddr*)&stClientAddr, &nTmp);
        if (nClientSocket < 0) 
           throw runtime_error(string("Can't create a connection's socket."));

		printf("%s: [connection from %s]\n",
                  argv[0], inet_ntoa((struct in_addr)stClientAddr.sin_addr));
		//Client* cl = new Client(stClientAddr,nClientSocket);
		//cout<<cl<<endl;
		thread(clientRequest, nClientSocket).detach();
		//th.detach();
		cout<<"OK"<<endl;
   }
   return(0);
}