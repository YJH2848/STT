#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

struct Client {
	int index;

	int socket;
	struct sockaddr_in address;
	int address_size;
};
int client_cnt = 0;

struct Client clients[10];
pthread_t thread[10];

void * do_communicate(void * data) {
	struct Client* client = (struct Client*) data;
	
	int index = clients->index;
	int client_socket = clients->socket;
	// ->
	printf("Client conncected\n");

	char message[128];

	sprintf(message, "Now, Connected ! Please tell me something.");
	write(client_socket, message, sizeof(message));
}

int main(int argc, char *argv[]) {
	int server_socket;
	struct sockaddr_in server_address;

	// int client_socket;
	// struct sockaddr_in client_address;
	// int client_address_size;

	char message[128];

	if(argc != 2)
		exit(0);

	/* Create Server Socket */
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_socket == -1) {
		printf("socket() error\n");
		exit(0);
	}

	/* Socket Address Config */
	memset(&server_address, 0, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	/* Socket Address Bind */
	int rst;
	rst = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	if(rst == -1) {
		printf("bind() error\n");
		exit(0);
	}

	printf("Waiting for Client...\n");

	/* Pending for connection request */
	listen(server_socket, 5);

	while(1) {
		clients[client_cnt].socket = accept(server_socket, (struct sockaddr *)&clients[client_cnt].address, &clients[client_cnt].address_size);
		clients[client_cnt].index = client_cnt;
		
		pthread_create(&thread[client_cnt], NULL, do_communicate, (void *) &clients[client_cnt]);
	}


	for(int i=0;i<client_cnt;i++)
		pthread_join(thread[i], NULL);
/*
	client_address_size = sizeof(client_address);
	client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);

	sprintf(message, "Now, Connected ! Please tell me something.");
	write(client_socket, message, sizeof(message));
	while(1) {
		read(client_socket, message, sizeof(message));
		printf("message from client : %s\n", message);
		scanf("%s", message);
		write(client_socket, message, sizeof(message));
		if(strcmp(message, "bye") == 0)
			break;
	}
*/

	return 0;
}
