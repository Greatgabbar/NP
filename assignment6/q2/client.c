//Rishabh Jain 102083054
//Assignment 6
//Question 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAX_BUFFER_SIZE 1025

void chat(int socketId) {
  char buffer[MAX_BUFFER_SIZE];
  for (;;) {
    bzero(buffer, sizeof(buffer));

    printf("Enter message to be sent to the server:\n");
    scanf("%s", &buffer[0]);
    send(socketId, buffer, strlen(buffer), 0);

    if (strcmp(buffer, ":exit") == 0) {
      printf("Client Exit... \n");
      break;
    }

    printf("Message sent to server\n");

    bzero(buffer, sizeof(buffer));

    recv(socketId, buffer, MAX_BUFFER_SIZE, 0);
    printf("Message from server: %s\n", buffer);

  }

}

int main() {

  int socketId, conn;
  struct sockaddr_in servaddr;

  socketId = socket(AF_INET, SOCK_STREAM, 0);
  if (socketId < 0) {
    printf("Socket creation failed\n");
    exit(1);
  }
  printf("Socket creation successful.\n");

  bzero(&servaddr,  sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  
  conn = connect(socketId, (struct sockaddr*)&servaddr, sizeof(servaddr));
  if (conn < 0) {
    printf("socket connection failed\n");
    exit(0);
  }
  else {
    printf("socket connection successful\n");
    chat(socketId);
    close(socketId);
  }
  return 0;
}