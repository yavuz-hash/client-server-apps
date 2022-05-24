#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



const char APRESSMESSAGE[] = "This is a hello message that send from server\n";

int main(int argc, char *argv[]) {
	int simpleSocket = 0;
	int simplePort = 0;
	int returnStatus = 0;
	
	
	struct sockaddr_in simpleServer;
	if (2 != argc) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	simpleSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (simpleSocket == -1) {
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}
	else {
		
		fprintf(stderr, "Socket created !\n");
	}
	/* retrieve the port number for listening */
	simplePort = atoi(argv[1]);
	/* set up the address structure */
	/* use INADDR_ANY to bind to all local addresses */
	bzero(&simpleServer, sizeof(simpleServer));
	simpleServer.sin_family = AF_INET;
	simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
	
	simpleServer.sin_port = htons(simplePort);
	
	
	/* bind to the address and port with our socket */
	returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));
	if (returnStatus == 0) {
		fprintf(stderr, "Bind completed Server is online !\n");
		printf("simpleServer.sin_addr.s_addr : %d\n", simpleServer.sin_addr.s_addr);
		printf("Server sin_port : %d\n",simpleServer.sin_port);
	}
	else {
		fprintf(stderr, "Could not bind to address!\n");
		close(simpleSocket);
		exit(1);
	}
	
	/* let's listen on the socket for connections */
	returnStatus = listen(simpleSocket, 5);
	
	
	if (returnStatus == -1) {
		fprintf(stderr, "Cannot listen on socket!\n");
		close(simpleSocket);
		exit(1);
	}
	while (1)
	{
		struct sockaddr_in clientName = { 0 };
		int simpleChildSocket = 0;
		int clientNameLength = sizeof(clientName);
		/* wait here */

		simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName,&clientNameLength);
			
		if (simpleChildSocket == -1) {
			fprintf(stderr, "Cannot accept connections!\n");
			close(simpleSocket);
			exit(1);
		}
		
		printf("client sin_port :%d\n",clientName.sin_port);
		printf("Connection accepted and client connected to server succesfully.\n");
		
		
		/* handle the new connection request */
		/* write out our message to the client */
		
		
		write(simpleChildSocket, APRESSMESSAGE, strlen(APRESSMESSAGE));
		printf("message succesfull send from server side.\n");
		close(simpleChildSocket);
	}
	close(simpleSocket);
	return 0;
}
