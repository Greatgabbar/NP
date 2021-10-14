//Socket Programming - TCP
//Made By - Shubham Dhiman 102097007
//Assignment 5
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
    int socketId;

    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));


    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    int addrlen = sizeof(servaddr);

    char buffer[1024] = { 0 };
    char r[1000];
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

    int clientId = accept(socketId, (struct sockaddr*)&servaddr, (socklen_t*)&addrlen);

    if (clientId < 0) {
        printf("accept failed\n");
        exit(1);
    }


    char inputString[1024];
    char selected[1024];
    int returnValue;

    bzero(inputString, sizeof(inputString));


    char operations[] = { "Specifiy the Operation -\n 1: Sorting\n 2: Comparison\n 3: Copy\n 4: Insertion\n 5: Deletion" };
    send(clientId, operations, strlen(operations), 0);
    printf("Operations Sent Succesfully\n");

    bzero(selected, sizeof(selected));
    returnValue = read(clientId, selected, 1024);
    printf("Option selected :  %s\n", selected);


    if (strncmp("1", selected, 1) == 0) {
        printf("Operation Selected : Sorting\n");
        read(clientId, inputString, 1024);
        printf("String from client:  %s\n", inputString);

        char temp;
        int i, j;
        int n = strlen(inputString);
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                if (inputString[i] > inputString[j]) {
                    temp = inputString[i];
                    inputString[i] = inputString[j];
                    inputString[j] = temp;
                }
            }
        }

        send(clientId, inputString, strlen(inputString), 0);
        printf("Operation complete\n");
    }else if (strncmp("2", selected, 1) == 0) {
        printf("Operation Selected : Comparison\n");
        int value;
        char stringComp[1024];
        bzero(stringComp, sizeof(stringComp));
        printf("String from client:  %s\n", inputString);
        read(clientId, inputString, 1024);
        read(clientId, stringComp, 1024);        
        printf("Second String from client: %s\n", stringComp);

        value = strcmp(inputString, stringComp);
            char same[] = { "Both Strings are Same" };
            char diff[] = { "Both Strings are Different" };
        if (value == 0) {
            send(clientId, same, strlen(same), 0);
        }
        else {
            send(clientId, diff, strlen(diff), 0);
        }
        printf("Operation complete\n");

    }else if (strncmp("3", selected, 1) == 0) {
        printf("Operation Selected : Copy\n");
        char* copiedString;
        copiedString = (char*)malloc(100);
        strcpy(copiedString, inputString);

        printf("String Copied \n");
        char result[] = { "String Copied" };
        send(clientId, result, strlen(result), 0);

        printf("Copied String is: %s\n", copiedString);
        printf("Operation complete\n");
    }
    else {
        printf("Connection Terminated\n");
    }
    close(clientId);
    close(socketId);

    return 0;

}
