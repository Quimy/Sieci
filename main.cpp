#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <thread>
#include <memory>

#include "Server.h"
#include "Client.h"
#include "Constants.h"
#include "HttpRequest.h"
using namespace std;

extern const int SERVER_PORT;
extern const int REQUEST_BUFFER_SIZE;
const int BUFFER_SIZE = 256;

void processClientRequests(int cl){
	try{
		int odp = 0;
		cout<<"Enter thread"<<endl;
	    char bufor[BUFFER_SIZE];
	    memset(&bufor, 0, BUFFER_SIZE);
	    string message;
		while((odp = read (cl, bufor, BUFFER_SIZE))>0){
			message+=bufor;
			if(message.size() > BUFFER_SIZE)
				throw runtime_error(string("Request is too long."));
			if(message.find("\r\n\r\n")!=string::npos){
				HttpRequest req=HttpRequest(message);
				message.clear();
			}
			memset(&bufor, 0, BUFFER_SIZE);
		}
		cout<<"End of thread"<<endl;
		close(cl);
	}catch(exception &e){
		cout<<e.what()<<endl;
		cout<<"End of thread"<<endl;
		close(cl);
	} 
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

		thread(processClientRequests, nClientSocket).detach();

		cout<<"OK"<<endl;
   }
   return(0);
}