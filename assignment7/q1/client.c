#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char buffer[1024];
  int socketID = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketID < 0) {
    printf("Error opening datagram socket");
    exit(1);
  }
  int reuse = 1;
  if (setsockopt(socketID, SOL_SOCKET, SO_REUSEADDR,
    (char*)&reuse, sizeof(reuse)) < 0) {
    printf("Error setting SO_REUSEADDR\n");
    close(socketID);
    exit(1);
  }
  struct sockaddr_in serveraddr;
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(5555);;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(socketID, (struct sockaddr*)&serveraddr, sizeof(serveraddr))) {
    printf("Erro binding datagram socket\n");
    close(socketID);
    exit(1);
  }
  struct ip_mreq multicastGroup;
  multicastGroup.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
  multicastGroup.imr_interface.s_addr = inet_addr("192.168.43.172");
  if (setsockopt(socketID, IPPROTO_IP, IP_ADD_MEMBERSHIP,
    (char*)&multicastGroup, sizeof(multicastGroup)) < 0) {
    printf("Error adding multicast group");
    close(socketID);
    exit(1);
  }
  if (read(socketID, buffer, sizeof(buffer)) < 0) {
    printf("Error reading datagram message");
    close(socketID);
    exit(1);
  }
  else
    printf("Message from multicast datagram: %s\n", buffer);
}