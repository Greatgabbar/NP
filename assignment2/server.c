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
    char message[100] ="Message from the server \n";
    char buffer[100];
    int socketID;

    struct sockaddr_in servaddr,cliaddr;    
    int serv_addrlen = sizeof(servaddr);    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT); 

    socketID = socket(AF_INET, SOCK_STREAM, 0);

    if(bind(socketID, (struct sockaddr *)&servaddr, serv_addrlen) < 0){
        printf("socket bind failed\n");
        exit(0);
    }else 
        printf("socket bind successful\n");
    
    if (listen(socketID, 5) != 0){
        printf("socket listen failed\n");
        exit(0);
    }else
        printf("socket listening successfully...\n");
    
    int client_addrlen = sizeof(cliaddr); 
    int clientId =  accept(socketID, (struct sockaddr *)&cliaddr, (socklen_t*)&client_addrlen); 

    recv(clientId, &buffer, sizeof(buffer), 0);
    printf("From client: %s\n", buffer); 
    
    send(clientId, message, sizeof(message), 0);
    printf("Message sent to client successfully\n");

    close(clientId);
    close(socketID);
    return 0;
}
