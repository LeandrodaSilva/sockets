#include <stdio.h>

int main(void)
{
	char url[]="dados.dat",
	     nome[13];
	float nota1, nota2, nota3;
  char texto[] = "Maria";
	FILE *arq;

	arq = fopen(url, "w+");
	if(arq == NULL){
    printf("Erro, nao foi possivel abrir o arquivo\n");
  }
	else{
    if (fwrite("texto", sizeof(char), 13, arq) != EOF) {
      printf("\n Operacao realizada com sucesso!\n");
    }else{
      return 0;
    }
    while( (fscanf(arq,"%s\n", nome))!=EOF ){
      printf("%s\n", nome);
    }

  }


	fclose(arq);

	return 0;
}
