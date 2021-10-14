// Rishabh Jain 102083054
// Assignment 7_2
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define PORT 8080

int main() {
  int socketId;
  
  struct sockaddr_in servaddr, cli;
  socketId = socket(AF_INET, SOCK_DGRAM, 0);
  int broadcastPermission = 1;
  setsockopt(socketId, SOL_SOCKET, SO_BROADCAST, 
    (void*)&broadcastPermission, sizeof(broadcastPermission));
  if (socketId == -1) {
    printf("Socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  
  char message[] = "This is a broadcast Message";
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("192.168.43.255");
  servaddr.sin_port = htons(PORT);
  sendto(socketId, message, sizeof(message), 0, 
    (struct sockaddr*)&servaddr, sizeof(servaddr));
  printf("Broadcast Sent\n");
  close(socketId);
}




