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
#define IP          "127.0.0.1"


void gravar(char* string);
char* currentIp(struct sockaddr_in server);
void sendArq(int port, char *ip, char *arq);
void clientSocket(char* comando);




////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////



void gravar(char* string)
{
  FILE *arq;
  int tam = (int) strlen(string);
  int i;
  arq = fopen("skeleton", "w");

  for (i = 0; i < tam; i++) {
    if (string[i] == ',' || string[i] == ':') {
      fprintf(arq,"\n");
    }else{
      fprintf(arq,"%c", string[i]);
    }
  }
  fclose(arq);

}


////////////////////////////////////////////////////////////////////////////////////
void clientStub(char* func, char* parameters)
{
  //Empacota os parametros em uma unica mensagem
  printf("Empacotando\n");
  char comando[200];
  strcpy(comando, func);
  strcat(comando, ":");
  strcat(comando,parameters);
  strcat(comando, ":");
  strcat(comando, "\0");
  clientSocket(comando);
}

// void clientStub(char* func, int um, int dois)
// {
//   //Empacota os parametros em uma unica mensagem
//   char a[2] ;
//   a[0] =   (char)(um - '0');
//   a[1] = ',';
//   char b[2] ;
//   b[0] = (char)(dois - '0');
//   b[1] = ':';
//   char comando[MAXLINE];
//   strcpy(comando, func);
//   strcat(comando, ":");
//   strcat(comando,a);
//   strcat(comando, ",");
//   strcat(comando,b);
//   strcat(comando, ":");
//   clientSocket(comando);
// }

void clientSocket(char* comando)
{
  //trasmite a mensagem pela rede;
	printf("Entrou socket\n" );

  int sockfd;
  char buffer[MAXLINE];
  char *hello = comando;
  struct sockaddr_in     servaddr;

  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("Erro na criacao do socket");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int n, len;

  sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
  printf("Enviado: %s para o IP: %s:%d\n",hello,IP,PORT);

  n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,(socklen_t *)&len);
  buffer[n] = '\0';
  printf("Recebido: %s\n", buffer);

  close(sockfd);
}
