// Rishabh Jain 102083054
//Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8888


void chat(int socketID) {

  char buffer[1025];
  bzero(buffer, sizeof(buffer));

  int n;

  for (;;) {

    read(socketID, buffer, sizeof(buffer));

    printf("Message from server: %s\n", buffer);

    printf("Enter message to be sent to the server:\n");
    bzero(buffer, sizeof(buffer));

    while ((buffer[n++] = getchar()) != '\n');

    if (strcmp(buffer, "exit") == 0) {
      printf("Client Exit... \n");
      break;
    }

    write(socketID, buffer, sizeof(buffer));

    printf("Message sent to server\n");

    bzero(buffer, sizeof(buffer));

  }

}

int main() {


  int socketID;

  struct sockaddr_in servaddr;

  int addrlen = sizeof(servaddr);

  socketID = socket(AF_INET, SOCK_STREAM, 0);

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  int conn = connect(socketID, (struct socketaddr*)&servaddr, addrlen);

  if (conn != 0) {
    printf("socket connection failed\n");
    exit(0);
  }
  else {
    printf("socket connection successful\n");
    chat(socketID);
    close(socketID);
  }

  return 0;

}
