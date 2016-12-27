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

#include "Server.h"
using namespace std;
#define SERVER_PORT 7070
#define QUEUE_SIZE 5

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
           string message;  
           int odp = 1000;
           char bufor[1000];
           memset(&bufor, 0, 1000);
           while (odp==1000){
           		odp = read (nClientSocket, bufor, 1000);
           		cout<<bufor<<endl;

           		message+=bufor;
           		cout<<message.size()<<endl;
           		memset(&bufor, 0, 1000);

           }
           		cout<<message.size()<<endl;

           cout<<message<<endl;

           close(nClientSocket);
   }
   return(0);
}