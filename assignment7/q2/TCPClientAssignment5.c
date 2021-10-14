// Rishabh Jain 102083054
//Assignment 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

int main() {


    char buffer[1024] = { 0 };

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

    //The inet_pton() function converts an Internet address in its standard text 
    //format into its numeric binary form. The argument af specifies the family of the address.
    // if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
    //     printf("\nInvalid address/ Address not supported \n");
    //     return -1;
    // }


    if (connect(socketId, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("socket connection failed\n");
        exit(1);
    }

    char buff[1024];
    int num = 0;


    bzero(buff, sizeof(buff));

    int returnValue;
    returnValue = read(socketId, buffer, 1024);
    printf("Message from Server : \n%s\n",buff);

    printf("Enter the String : ");
    while ((buff[num++] = getchar()) != '\n');
    send(socketId, buff, strlen(buff), 0);

    num = 0;
    char buff1[1024];
    bzero(buff1, sizeof(buff1));
    // printf("Enter the String : ");
    // while ((buff1[num++] = getchar()) != '\n');
    // send(socketId, buff1, strlen(buff1), 0);
    // printf("Message sent to Server Succesfully- %s\n", buff1);
    // printf("%s", buff1);

    if (strncmp("2", buff1, 1) == 0) {
        int i = 0;
        char secondString[1024];
        bzero(secondString, sizeof(secondString));
        printf("Enter the Second String : ");
        while ((secondString[i++] = getchar()) != '\n');
        send(socketId, secondString, strlen(secondString), 0);
    }



    char buff2[1024];
    bzero(buff2, sizeof(buff2));
    returnValue = read(socketId, buff2, 1024);
    printf("Result from Server : %s\n",buff2);

    close(socketId);

    return 0;
}