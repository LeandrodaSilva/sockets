#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "skeleton.h"

#define PORT        8080
#define MAXLINE     1024
#define IP          "127.0.0.1"


void gravar(char* string);
char* currentIp(struct sockaddr_in server);
void sendArq(int port, char *ip, char *arq);
void clientSocket(char* comando);

void clientStub(char* func, int um, int dois);



int serverStub(char* comandos)
{
  gravar(comandos);
  printf("Desempacotando\n");
  int qtd = -1;
  int i;
  FILE *arq;
  arq = fopen("skeleton", "r");
  rewind(arq);
  //------------------------------------
   char a = '.', b = '.', letra;
  // i = 0;
  // int start = 0;
  // while (!feof(arq)) {
  //   fscanf(arq, "%c", &letra);
  //   printf("Letra %c\n", letra);
  //   if (letra != ',' && a == '.') {
  //     a = letra;
  //     printf("a = %c\n", a);
  //   }
  //   if (letra != ';' && b == '.' && a != '.') {
  //     b = letra;
  //     printf("b = %c\n", b);
  //   }
  // }
  fscanf(arq, "add\n%c\n%c\n",&a,&b);

  printf("Calculando %c + %c\n", a,b);
  int resp = func(0, a,b);
  printf("Resultado da conta %d\n", resp);
  fclose(arq);
  return  resp;
}

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
    if (string[i] == ',' || string[i] == ':' || string[i] == ';') {
      fprintf(arq,"\n");
    }else{
      fprintf(arq,"%c", string[i]);
    }
  }
  fclose(arq);

}

void serverSocket()
{
  int sockfd;
  char buffer[MAXLINE];
  char hello[1];
  int resp;
  struct sockaddr_in servaddr, cliaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("Erro na criacao do socket");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = inet_addr(IP);
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
  {
    perror("falha no bind");
    exit(EXIT_FAILURE);
  }

  while (1) {
    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr,(socklen_t *)&len);

    int i;
    for (i = 0; i < MAXLINE; i++) {
      if (buffer[i] == ';') {
        buffer[i+1] = '\0';
      }
    }

    printf("Servidor recebe: %s\n", buffer);
    resp = serverStub(buffer);
    printf("Resposta socket: %d\n", resp);
    char a = resp + '0';
    hello[0] = a;
    hello[1] = '\0';

    sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
    printf("Enviado: %s para o IP: %s.\n", hello, currentIp(cliaddr));
  }

}

void serverSocket2()
{
  int sockfd;
  char buffer[MAXLINE];
  char hello[] = "soma";
  int resp;
  struct sockaddr_in servaddr, cliaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("Erro na criacao do socket");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = inet_addr(IP);
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
  {
    perror("falha no bind");
    exit(EXIT_FAILURE);
  }

  while (1) {
    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr,(socklen_t *)&len);
    printf("Recebido: %s\n", buffer);
    if (strcmp(buffer, "add")) {
      sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
      printf("Enviado: %s para o IP: %s.\n", hello, currentIp(cliaddr));
    }else{
      char nada[] = "nada";
      sendto(sockfd, (const char *)nada, strlen(nada),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
      printf("Enviado: %s para o IP: %s.\n", nada, currentIp(cliaddr));
    }

  }

}


////////////////////////////////////////////////////////////////////////////////////
// void clientStub(char* func, char* parameters)
// {
//   //Empacota os parametros em uma unica mensagem
//   printf("Empacotando\n");
//   char comando[200];
//   strcpy(comando, func);
//   strcat(comando, ":");
//   strcat(comando,parameters);
//   strcat(comando, ":");
//   strcat(comando, "\0");
//   clientSocket(comando);
// }

void clientStub(char* func, int um, int dois)
{
  //Empacota os parametros em uma unica mensagem
  char umC = um+'0';
  char doisC = dois+'0';
  printf("Valor1: %c Valor2: %c\n", umC,doisC);
  int i, i2, start = 0;

  char comando[MAXLINE];
  strcpy(comando, func);
  strcat(comando, ":");
  for (i = 0; comando[i] != ':'; i++) {
    start++;
  }
  comando[++start] = umC;
  comando[++start] = ',';
  comando[++start] = doisC;
  comando[++start] = ';';
  comando[++start] = '\0';
  printf("clientStub1 -> %s\n", comando);
  clientSocket(comando);
}

void clientSocket(char* comando)
{
  //trasmite a mensagem pela rede;
	printf("Entrou socket\n" );

  int sockfd;
  char buffer[MAXLINE];
  int tam = strlen(comando);
  int i;
  char msg[tam];
  for (i = 0; i < (tam+1); i++) {
    msg[i] = comando[i];
  }

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

  sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
  printf("Enviado: %s para o IP: %s:%d\n",msg,IP,PORT);

  n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,(socklen_t *)&len);
  buffer[n] = '\0';
  printf("Recebido: %s\n", buffer);

  close(sockfd);
}
