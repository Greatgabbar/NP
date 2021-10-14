// Rishabh Jain 102083054
//Assignment 4
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 4040

int main() {
  int socketId;

  struct sockaddr_in servaddr;

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  int addrlen = sizeof(servaddr);

  socketId = socket(AF_INET, SOCK_STREAM, 0);
  if (socketId < 0) {
    printf("master socket creation failed\n");
    exit(1);
  }
  
  if (bind(socketId, (struct sockaddr*)&servaddr, addrlen) < 0) {
    printf("bind failed\n");
    exit(1);
  }

  if (listen(socketId, 5) < 0) {
    printf("listen failed\n");
    exit(1);
  }
  else printf("Listening on port %d ... \n", PORT);

  int clientId = accept(socketId, (struct sockaddr*)&servaddr, 
                      (socklen_t*)&addrlen);
  if (clientId < 0) {
    printf("accept failed\n");
    exit(1);
  }

  char input[1024];
  char output[1024];

  bzero(input, sizeof(input));
  bzero(output, sizeof(output));

  read(clientId, input, 1024);
  printf("From client:  %s\n", input);

  int l = strlen(input);
  int j = 0;
  for (int i = l-1;i >= 0; i--) {
    output[j++] = input[i];
  }
  output[j+1]='\0'; 

  printf("Sending to client:  %s\n", output);
  send(clientId, output, strlen(output), 0);

  close(clientId);
  close(socketId);

  return 0;

}
