#include <iostream> //cout
#include <string> //class string

#include <stdexcept> //exceptions
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <fcntl.h>
#include <thread> //threads

#include "../include/Server.h"
#include "../include/Client.h"
#include "../include/Constants.h"
#include "../include/HttpRequest.h"

using namespace std;

extern const int SERVER_PORT;
extern const int REQUEST_BUFFER_SIZE;
const int BUFFER_SIZE = 256;

void processClientRequests(int clientSocket){
	try{
		int odp = 0;

		cout<<"Enter thread"<<endl;
	    char bufor[BUFFER_SIZE];
	    memset(&bufor, 0, BUFFER_SIZE);
	    string message;
		while((odp = read (clientSocket, bufor, BUFFER_SIZE))>0){
			message+=bufor;
			if(message.size() > REQUEST_BUFFER_SIZE)
				throw runtime_error(string("Request is too long."));
			if(message.find("\r\n\r\n")!=string::npos){
				HttpRequest req = HttpRequest(message);
				string tmp = req.getResponseMessage();
				write(clientSocket,&tmp[0], tmp.size());
				message.clear();
			}
			memset(&bufor, 0, BUFFER_SIZE);
		}
		cout<<"End of thread"<<endl;
		close(clientSocket);
	}catch(exception &e){
		cout<<e.what()<<endl;
		cout<<"End of thread"<<endl;
		close(clientSocket);
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

   }
   return(0);
}