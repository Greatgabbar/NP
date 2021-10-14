// Rishabh Jain 102083054
//Assignment 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

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

  char buffer[1024] = { 0 };
  char option[1] = { 0 };

  int ret;

  ret = read(socketId, buffer, 1024);
  printf("Message from Server : \n%s\n", buffer);

  int num = 0;
  char op;

  bzero(buffer, sizeof(buffer));
  printf("Choose operation : ");
  scanf("%s", option);

  send(socketId, option, strlen(option), 0);

 bzero(buffer, sizeof(buffer));
  num = 0;
  printf("Enter the String : ");

  scanf("%s", buffer);
  send(socketId, buffer, strlen(buffer), 0);
  printf("Message sent to Server: %s\n", buffer);
  bzero(buffer, sizeof(buffer));



  if (strncmp("2", option, 1) == 0) {
    int i = 0;
    char secondString[1024];
    bzero(secondString, sizeof(secondString));
    printf("Enter the Second String : ");
    scanf("%s", secondString);
    send(socketId, secondString, strlen(secondString), 0);
    printf("Message sent to Server: %s\n", secondString);

  }else if (strncmp("4", option, 1) == 0) {

    char ch;
    printf("Enter Character : \n");
    scanf(" %c", &ch);
    send(socketId, &ch, sizeof(ch), 0);
    printf("Character sent to Server: %c\n", ch);
    int n;
    printf("Enter position: ");
    scanf("%d", &n);
    send(socketId, &n, sizeof(n), 0);
    printf("Position sent to Server: %d\n", n);
  }else if (strncmp("5", option, 1) == 0) {
    int n;
    printf("Enter position: ");
    scanf("%d", &n);

    send(socketId, &n, sizeof(n), 0);
    printf("Position sent to Server: %d\n", n);
  }

  char result[1024];
  bzero(result, sizeof(result));
  ret = read(socketId, result, 1024);
  printf("Result from Server : %s\n", result);

  close(socketId);
  return 0;
}