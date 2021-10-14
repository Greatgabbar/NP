// Rishabh Jain 102083054
//Assignment 6
// Question 1

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 

#define PORT 8888
#define MAX_CLIENTS 30
#define BUFFER_SIZE 1025

int main() {
  int master_socketId, addrlen, new_socket, client_socket[MAX_CLIENTS],
    activity, i, valread, client_sd;
  int master_sd;

  char buffer[BUFFER_SIZE];

  fd_set readfds;

  char message[1025] = "Response from server\n";

  bzero(client_socket, sizeof(client_socket));

  master_socketId = socket(AF_INET, SOCK_STREAM, 0);

  if (master_socketId < 0) {
    printf("master socket creation failed\n");
    exit(1);
  }
  else
    printf("Socket created successfully\n");

  int opt = 1;


  if (setsockopt(master_socketId, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
    printf("setsockopt failed\n");
    exit(1);
  }

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if (bind(master_socketId, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    printf("bind failed\n");
    exit(1);
  }

  if (listen(master_socketId, 5) < 0) {
    printf("listen failed\n");
    exit(1);
  }
  else printf("Listening on port %d ... \n", PORT);

  addrlen = sizeof(servaddr);
  printf("Waiting for connections ...\n");

  while (1) {
    FD_ZERO(&readfds);

    FD_SET(master_socketId, &readfds);
    master_sd = master_socketId;

    for (i = 0; i < MAX_CLIENTS; i++) {
      client_sd = client_socket[i];

      if (client_sd > 0)
        FD_SET(client_sd, &readfds);

      if (client_sd > master_sd)
        master_sd = client_sd;
    }

    activity = select(master_sd + 1, &readfds, NULL, NULL, NULL);

    if (activity < 0 && errno != EINTR) {
      printf("select error\n");
      exit(1);
    }
    if (FD_ISSET(master_socketId, &readfds)) {
      new_socket = accept(master_socketId, (struct sockaddr*)&servaddr, (socklen_t*)&addrlen);
      if (new_socket < 0) {
        printf("accept error\n");
        exit(1);
      }
      printf("New connection , socket fd is %d , ip is : %s , port : %d \n", new_socket, inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
      
      send(new_socket, message, strlen(message), 0);      
      printf("Message sent to %d successfully\n", new_socket);

      for (i = 0; i < MAX_CLIENTS; i++) {
        if (client_socket[i] == 0) {
          client_socket[i] = new_socket;
          printf("Adding to list of sockets as %d\n", i);
          break;
        }
      }
    }

    for (i = 0; i < MAX_CLIENTS; i++) {
      client_sd = client_socket[i];

      if (FD_ISSET(client_sd, &readfds)) {
        if ((valread = read(client_sd, buffer, BUFFER_SIZE)) == 0) {
          getpeername(client_sd, (struct sockaddr*)&servaddr, (socklen_t*)&addrlen);
          printf("Host disconnected , ip %d , port %d \n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
          close(client_sd);
          client_socket[i] = 0;
        }else {
          buffer[valread] = '\0';
          printf("Message from client_id %d: %s\n",client_sd,buffer);
          send(client_sd, message, strlen(message), 0);
        }
      }
    }
  }

  return 0;
}
