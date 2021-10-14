// Rishabh Jain 102083054
//Assignment 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 4040

int main() {
  int socketId = socket(AF_INET, SOCK_STREAM, 0);

  if (socketId < 0) {
    printf("master socket creation failed\n");
    exit(1);
  }

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (connect(socketId, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    printf("socket connection failed\n");
    exit(1);
  }
  char buffer[1024];
  bzero(buffer, sizeof(buffer));

  printf("Enter the String : ");
  scanf("%s", buffer);

  printf("Sending to Server: %s\n", buffer);
  send(socketId, buffer, strlen(buffer), 0);

  bzero(buffer, sizeof(buffer));

  int n = read(socketId, buffer, 1024);
  buffer[n] = '\0';
  printf("From Server : %s\n", buffer);

  close(socketId);
  return 0;
}