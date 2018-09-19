#include <stdio.h>

#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *arq;
  char Linha[100];



  // Abre um arquivo TEXTO para LEITURA
  arq = fopen(argv[1], "r");


  while (!feof(arq))
  {


    if (fscanf(arq, "%s", Linha))  // Se foi possível ler
    printf("%s\n",Linha);

  }
  fclose(arq);
  printf("\n\n");
  system("PAUSE");
}
