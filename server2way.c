#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){
	int server_socket,client_socket;
	struct sockaddr_in server_address,client_address;
	socklen_t client_add_length;
	char buffer[1000];
	
	//Create the socket	
	server_socket = socket(AF_INET,SOCK_STREAM,0);
	if(server_socket == -1){
		perror("Socket Creation Failed!");
		exit(0);
	}
	printf("Socket created successfully...\n");
	
	//Set the server details
	server_address.sin_family = AF_INET;
    	server_address.sin_addr.s_addr = INADDR_ANY;
    	server_address.sin_port = htons(12345);
    	
	//Bind the socket
	if(bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address)) < 0){
		perror("Binding error!");
		exit(0);
	}
	printf("Socket binded successfully...\n");
	
	//Listen for connections
	if(listen(server_socket,1)<0){
		perror("Listen failed!");
		exit(0);
	}
	printf("Server listening...\n");
	
	//Accept connection from client
	client_add_length = sizeof(client_address);
	client_socket = accept(server_socket,(struct sockaddr *)&client_address,&client_add_length);
	if(client_socket<0){
		perror("Accept failed!");
		exit(0);
	}
	printf("Connected to the client...\n");
	
	//Receive data from the client
	while(1){
		memset(buffer,0,sizeof(buffer));
		if(recv(client_socket,buffer,sizeof(buffer),0)<0){       
			printf("Receive failure!");
			exit(0);
		}
		printf("From Client: %s\n",buffer);
		if(strcmp(buffer,"exit")==0)
			break;
		
		printf("Enter response:");
		fgets(buffer,sizeof(buffer),stdin);
		
		//Send response
		if(send(client_socket,buffer,strlen(buffer),0)<0){
			perror("Send failure...");
			exit(0);
		}
	}
	
	//Close the sockets
	close(client_socket);
	close(server_socket);
	
	
	
	
	
	return 0;
}
	
