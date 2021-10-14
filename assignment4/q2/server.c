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

  char input[1024];
  char output[1024];
  bzero(input, sizeof(input));
  bzero(output, sizeof(output));

  int len = sizeof(cliaddr);
  int  n = recvfrom(socketId, input, 1024, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
  printf("From Client: %s\n", input);

  int l = strlen(input);
  int j = 0;
  for (int i = l - 1;i >= 0; i--) {
    output[j++] = input[i];
  }
  output[j + 1] = '\0';


  printf("Sending to client:  %s\n", output);
  sendto(socketId, output, strlen(output), MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);

  return 0;
}
