// Rishabh Jain 102083054
// Assignment 7_2
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PORT 8080

int main() {
  char buffer[1024];
  int socketID, len, n;
  struct sockaddr_in servaddr;
  socketID = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketID < 0) {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(len));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if ((bind(socketID, (struct sockaddr_in*)&servaddr, sizeof(servaddr))) != 0) {
    printf("Error socket bind failed...\n");
    exit(0);
  }

  len = sizeof(servaddr);

  recvfrom(socketID, buffer, sizeof(buffer), 0, (struct sockaddr_in*)&servaddr, &len);
  printf("Message Recieved : %s\n", buffer);

  close(socketID);
}
