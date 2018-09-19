
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>



#define PORT     8080 //porta para a conexao
#define MAXLINE 1024


int main(int argc, char*argv[])
{
  //nome do socket
  int sockfd;
  //buffer utilizado para recepção de msg
  char buffer[MAXLINE];
  /*estrutura contendo as informações do servidor e cliente
  #include <netinet/in.h>

  struct sockaddr_in {
      short            sin_family;   // e.g. AF_INET
      unsigned short   sin_port;     // e.g. htons(3490)
      struct in_addr   sin_addr;     // see struct in_addr, below
      char             sin_zero[8];  // zero this if you want to
  };

  struct in_addr {
      unsigned long s_addr;  // load with inet_aton()
  };
  */
  struct sockaddr_in servaddr, cliaddr;

  /*Descrição da criaçao do socket
  #include <sys/types.h>
  #include <sys/socket.h>

  int socket(int domain, int type, int protocol);

  socket() retorna o socket com as descrições pedidas
  ou -1 caso ocorra erro
  */
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Falha  na criação do socket");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));
  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  //servaddr.sin_addr.s_addr = INADDR_ANY;
  //especifica o endereço do servidor de forma resumida
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);
  servaddr.sin_port = htons(PORT); //define a porta do servidor


  /*
  #include <sys/types.h>
  #include <sys/socket.h>

  int bind(int sockfd, struct sockaddr *my_addr, int addrlen);*/
  if (bind(sockfd,
          (const struct sockaddr*)&servaddr,
          sizeof(servaddr)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  //MSG_NOSIGNAL

  int len, n;


    n = recvfrom(sockfd, buffer, sizeof(buffer),  MSG_WAITALL,
                (struct sockaddr*)&cliaddr, (socklen_t*)&len);

    //buffer[n] = '\0';
    printf("Client say: %s\n", buffer);
    //MSG_NOSIGNAL ou MSG_CONFIRM



  sendto(sockfd, (const char*)"ok", strlen("ok"),  MSG_CONFIRM,
        (const struct sockaddr *)&cliaddr, len);

  printf("Send: \"%s\" to %s\n", "OK", inet_ntoa(cliaddr.sin_addr));

  return 0;
}
