// Rishabh Jain 102083054
//Assignment 4_2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {

  int socketId = socket(AF_INET, SOCK_DGRAM, 0);

  if (socketId < 0) {
    printf("socket creation failed\n");
    exit(1);
  }
  else
    printf("Socket created successfully\n");

  struct sockaddr_in	 servaddr;
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);


  char buffer[1024];
  bzero(buffer, sizeof(buffer));

  printf("Enter the String : ");
  scanf("%s", buffer);

  sendto(socketId, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));
  printf("Message sent to server.\n");

  recvfrom(socketId, buffer, 1024, MSG_WAITALL, (struct sockaddr*)&servaddr, sizeof(servaddr));

  printf("From Server: %s\n", buffer);

  close(socketId);
  return 0;
}
