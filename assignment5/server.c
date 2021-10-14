// Rishabh Jain 102083054
//Assignment 5
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main() {
  int socketId;

  struct sockaddr_in servaddr;

  bzero(&servaddr, sizeof(servaddr));


  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  int addrlen = sizeof(servaddr);

  int opt = 1;

  socketId = socket(AF_INET, SOCK_STREAM, 0);
  if (socketId < 0) {
    printf("master socket creation failed\n");
    exit(1);
  }

  if (setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    printf("setsockopt failed\n0");
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


  int clientId = accept(socketId, (struct sockaddr*)&servaddr, (socklen_t*)&addrlen);

  if (clientId < 0) {
    printf("accept failed\n");
    exit(1);
  }


  char input[1024];
  char choice[1024];
  int ret;

  bzero(input, sizeof(input));
  char operations[] = { "Specifiy the Operation :\n 1: Sorting\n 2: Comparison\n 3: Copy\n 4: Insertion\n 5: Deletion\0" };
  send(clientId, operations, strlen(operations), 0);
  printf("Operations Sent Succesfully\n");

  bzero(choice, sizeof(choice));
  ret = read(clientId, choice, 1024);
  printf("Option selected :  %s\n", choice);


  if (strncmp("1", choice, 1) == 0) {
    printf("Operation Selected : Sorting\n");
    read(clientId, input, 1024);
    printf("String from client:  %s\n", input);

    char temp;
    int i, j;
    int n = strlen(input);
    for (i = 0; i < n - 1; i++) {
      for (j = i + 1; j < n; j++) {
        if (input[i] > input[j]) {
          temp = input[i];
          input[i] = input[j];
          input[j] = temp;
        }
      }
    }

    send(clientId, input, strlen(input), 0);
    printf("Operation complete\n");
  }
  else if (strncmp("2", choice, 1) == 0) {
    printf("Operation Selected : Comparison\n");
    int value;
    char stringComp[1024];
    bzero(stringComp, sizeof(stringComp));
    read(clientId, input, 1024);
    printf("String from client:  %s\n", input);
    read(clientId, stringComp, 1024);
    printf("Second String from client: %s\n", stringComp);

    value = strcmp(input, stringComp);
    char same[] = { "Both Strings are Same" };
    char diff[] = { "Both Strings are Different" };
    if (value == 0) {
      send(clientId, same, strlen(same), 0);
    }
    else {
      send(clientId, diff, strlen(diff), 0);
    }
    printf("Operation complete\n");

  }
  else if (strncmp("3", choice, 1) == 0) {
    printf("Operation Selected : Copy\n");
    read(clientId, input, 1024);
    printf("String from client:  %s\n", input);
    char* copiedString;
    copiedString = (char*)malloc(100);
    strcpy(copiedString, input);

    printf("String Copied \n");
    char result[] = { "String Copied" };
    send(clientId, result, strlen(result), 0);

    printf("Copied String is: %s\n", copiedString);
    printf("Operation complete\n");
  }
  else if (strncmp("4", choice, 1) == 0) {
    printf("Operation Selected : Insertion\n");
    read(clientId, input, 1024);
    printf("String from client:  %s\n", input);

    char ch;
    read(clientId, &ch, sizeof(ch));
    printf("Character from client:  %c\n", ch);

    int pos;
    read(clientId, &pos, sizeof(pos));
    printf("Position from client:  %d\n", pos);


    int  l = strlen(input);
    int i;
    for (i = l; i > pos - 1; i--) {
      input[i] = input[i - 1];
    }
    input[pos - 1] = ch;
    send(clientId, input, strlen(input), 0);
    printf("Operation complete\n");
  }
  else if (strncmp("5", choice, 1) == 0) {
    printf("Operation Selected : Deletion\n");
    read(clientId, input, 1024);
    printf("String from client:  %s\n", input);
    int pos;
    read(clientId, &pos, sizeof(pos));
    printf("Position from client:  %d\n", pos);

    int  l = strlen(input);
    int i;
    for (i = 0; i < pos; i++);
    i--;
    for (i; i < l; i++) {
      input[i] = input[i + 1];
    }

    send(clientId, input, strlen(input), 0);
    printf("Operation complete\n");
  }
  else {
    printf("Connection Terminated\n");
  }
  close(clientId);
  close(socketId);

  return 0;

}
