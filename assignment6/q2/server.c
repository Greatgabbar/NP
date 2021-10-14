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

int main() {

  int socketId ,new_socket;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t addr_size;

  char buffer[MAX_BUFFER_SIZE];
  pid_t childpid;

  socketId = socket(AF_INET, SOCK_STREAM, 0);
  if (socketId < 0) {
    printf("master socket creation failed\n");
    exit(1);
  }
  else
    printf("Socket created successfully\n");

  memset(&servaddr, '\0', sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socketId, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    printf("bind failed\n");
    exit(1);
  }

  if (listen(socketId, 5) < 0) {
    printf("listen failed\n");
    exit(1);
  }
  else printf("Listening on port %d ... \n", PORT);

  while (1) {
    new_socket = accept(socketId, (struct sockaddr*)&cliaddr, &addr_size);
    if (new_socket < 0) {
      exit(1);
    }
    printf("New connection , socket fd is %d , ip is : %s , port : %d \n",
     new_socket, inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

    if ((childpid = fork()) == 0) {
      close(socketId);

      for (;;) {
        recv(new_socket, buffer, MAX_BUFFER_SIZE, 0);
        if (strcmp(buffer, ":exit") == 0) {
          printf("Disconnected from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
          break;
        }
        else {
          printf("Client %d: %s\n", new_socket,buffer);
          send(new_socket, buffer, strlen(buffer), 0);
          bzero(buffer, sizeof(buffer));
        }
      }
    }

  }

  close(new_socket);
  close(socketId);

  return 0;
}