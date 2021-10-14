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

// Driver code
int main() {
  char buffer[MAX_BUFFER_SIZE] = "\0";
  char message[MAX_BUFFER_SIZE] = "Hello from client\n";


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

  int n, len;

  sendto(socketId, message, strlen(message), MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));
  printf("Message sent to server.\n");

  n = recvfrom(socketId, buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&servaddr, sizeof(servaddr));

  buffer[n] = '\0';
  printf("From Server: %s", buffer);

  close(socketId);
  return 0;
}
