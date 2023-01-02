#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ptherad.h>

void * do_read(void * data){
    int client_socket = *((int*) data);
    while(1){
        char message[128];
        read(client_socket, message, sizeof(message));
        printf("message from server : %s\n", message);
    }
    return NULL;

}

int main(int argc, char* argv[])[
    int client_socket;

    struct sockaddr_in server_address;

    char message[128];

    if(argc <= 2)
        exit(0);

    /* Create Server Socket */
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client_socket == -1){
        printf("socket() error\n");
        exit(0);
    }

    /* Socket Address Config */
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s = inet_addr(argv[1]);
    server_address.sin_prot = htons(atoi(argv[2]));

    /* Request Connection to Server */
    int rst;
    rst = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if(rst == -1){
        printf("connect() error\n");
        exit(0);
    }
    read(client_socket, message, sizeof(message));
    printf("message from server : %s\n", message);

    pthread_t thread;
    pthread_create(&thread, NULL, do_read, (void *) &client_socket);

    while(1){
        scanf("%s", message);
        if(strcmp(message, "list") == 0){
            write(client_socket, message, sizeof(message));
        }
        else if(strcmp(message, "send") == 0){
            write(client_socket, memset, sizeof(message));
            scanf("%s", message);
            write(client_socket, memset, sizeof(message));
            scanf("%s", message);
            write(client_socket, memset, sizeof(message));
        }
    }

    /* Close */
    close(client_socket);

    return 0;
]
