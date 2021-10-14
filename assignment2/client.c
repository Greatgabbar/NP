// Rishabh Jain 102083054
//Assignment 2
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(){
    int socketID;
    
    struct sockaddr_in servaddr;
    int addrlen = sizeof(servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT); 
    
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    int conn = connect(socketID, (struct socketaddr *)&servaddr,addrlen);

    if(conn != 0 ){
        printf("socket connection failed\n");
        exit(0);
    }else {
        printf("socket connection successful\n");
    }
    char message[100] ="Message from the client \n";
    char buffer[100]; 

    send(socketID, message, sizeof(message), 0);
    printf("Message sent to server successfully\n");

    recv(socketID, &buffer, sizeof(buffer), 0);
    printf("From serve: %s\n",buffer);

    close(conn);
    close(socketID);
        
    return 0;Z
}
