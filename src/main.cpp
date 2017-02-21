#include <iostream> //cout
#include <string> //class string

#include <stdexcept> //exceptions
#include <thread> //threads

#include "../include/Server.h"
#include "../include/Client.h"
#include "../include/Constants.h"
#include "../include/HttpRequest.h"

using namespace std;

extern const int SERVER_PORT;
extern const int REQUEST_BUFFER_SIZE;

void processClientRequests(int clientSocket){
	try{

	    char bufor[REQUEST_BUFFER_SIZE];
	    memset(&bufor, 0, REQUEST_BUFFER_SIZE);

		read(clientSocket, bufor, REQUEST_BUFFER_SIZE);
		cout<<bufor<<endl;
		HttpRequest req = HttpRequest(string{bufor});

		string response = req.getResponseMessage();

		write(clientSocket,&response[0], response.size());

	}
	catch(exception &e){
		string response{"HTTP/1.0 400 Bad Request\r\n\r\n"};
		write(clientSocket,&response[0], response.size());	
	} 
	close(clientSocket);
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