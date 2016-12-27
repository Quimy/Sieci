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

string readBuffer(int nClientSocket){
	int bufSize = 2000;
    char bufor[bufSize];
    memset(&bufor, 0, bufSize);
    int odp = read (nClientSocket, bufor, bufSize);
    return string(bufor);
}
void test(int cl){
	cout<<&cl<<endl;
	sleep(3);
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
		thread(test, nClientSocket).detach();
		//th.detach();
		cout<<"OK"<<endl;
		close(nClientSocket);
   }
   return(0);
}