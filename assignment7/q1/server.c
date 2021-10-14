#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  int socketId = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketId < 0) {
    printf("Error creating datagram socket\n");
    exit(1);
  }
  char message[] = "This is a Multicast Message";

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("225.1.1.1");
  servaddr.sin_port = htons(5555);
  
  char loopch = 0;
  if (setsockopt(socketId, IPPROTO_IP, IP_MULTICAST_LOOP,
    (char*)&loopch, sizeof(loopch)) < 0) {
    printf("Error setting IP_MULTICAST_LOOP:");
    close(socketId);
    exit(1);
  }

  struct in_addr multicastInterface;
  multicastInterface.s_addr = inet_addr("192.168.43.172");
  if (setsockopt(socketId, IPPROTO_IP, IP_MULTICAST_IF,
    (char*)&multicastInterface,
    sizeof(multicastInterface)) < 0) {
    printf("setting local interface");
    exit(1);
  }
  if (sendto(socketId, message, sizeof(message), 0,
    (struct sockaddr*)&servaddr,
    sizeof(servaddr)) < 0) {
    printf("Erro sending datagram message");
  }
}