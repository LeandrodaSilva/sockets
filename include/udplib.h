#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT        8080
#define MAXLINE     1024
#define IP          "192.168.1.70"

char* currentIp(struct sockaddr_in server)
{
  return inet_ntoa(server.sin_addr);
}

void sendArq(int port, char *ip, char *arq)
{
  struct sockaddr_in servaddr;
  int socketOpen;

  if ((socketOpen = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = inet_addr(ip);

  sendto(socketOpen, (const char *)"texto", strlen("texto"), MSG_NOSIGNAL, (const struct sockaddr*)&servaddr, sizeof(servaddr));

  close(socketOpen);

}

void sendMsg(int port, char ip[], char msg[])
{
  struct sockaddr_in serverInfo;
  int socketOpen;
  char received[64];


  if ((socketOpen = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&serverInfo, 0, sizeof(serverInfo));

  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons(port);
  serverInfo.sin_addr.s_addr = inet_addr(ip);

  sendto(socketOpen, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr*)&serverInfo, sizeof(serverInfo));

  printf("Server : %s\n", received);

  close(socketOpen);
}
