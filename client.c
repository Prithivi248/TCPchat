#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
	
	int client_socket;
	struct sockaddr_in server_address;
	char buffer[1000];
	
	//Create the socket
	client_socket = socket(AF_INET,SOCK_STREAM,0);
	if(client_socket==-1){
		perror("Socket creation failed!");
		exit(0);
	}
	printf("Socket created...\n");
	
	//server details
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(1028);
	
	inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr);
	
	//Connect the socket to the server
	if(connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address))<0){
		perror("Connection failed!");
		exit(0);
	}
	printf("Connected to server...\n");
	
	//Send data to the server
	while(true){
		printf("Enter message to send to client:");
		scanf("%s",buffer);
		if(send(client_socket,buffer,sizeof(buffer),0)<0){
			perror("Send failure!");
			exit(0);
		}
		if(strcmp(buffer,"exit")==0)
			break;
		/*printf("Message sent to server!\n");
		int ch;
		printf("Continue or stop(0/1):");
		scanf("%d",&ch);
		if(ch==1)
			break;*/
		else
			continue;
	}
	
	//Close the client socket
	close(client_socket);
	
	
	
	
	return 0;
}

