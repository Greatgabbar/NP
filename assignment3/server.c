// Rishabh Jain 102083054
//Assignment 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 256 

int main() {

    char buffer[MAX_BUFFER_SIZE];
    char* message = "Hello from server\n";

    int socketId = socket(AF_INET, SOCK_DGRAM, 0);

    if (socketId < 0) {
        printf("socket creation failed\n");
        exit(1);
    }
    else
        printf("Socket created successfully\n");

    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if (bind(socketId, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("bind failed\n");
        exit(1);
    }
    int len = sizeof(cliaddr);
    int  n = recvfrom(socketId, buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
    buffer[n] = '\0';
    printf("From Client: %s", buffer);

    sendto(socketId, message, strlen(message), MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);
    printf("Message sent to client.\n");

    return 0;
}
