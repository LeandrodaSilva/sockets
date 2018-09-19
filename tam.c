#include <stdio.h>
#include <stdlib.h>

int main() {

  //  char nomeArquivo[100]; // nome do arquivo
    FILE *arquivo; // ponteiro para o arquivo
    float tamanho; // tamanho em bytes do arquivo

    //printf("Digite o nome do arquivo: ");
    //scanf("%s", nomeArquivo);

    // abre o arquivo para leitura
    arquivo = fopen("imagem.jpg", "rb");

    // verifica se o arquivo foi aberto com sucesso
    if (arquivo != NULL) {
        // movimenta a posição corrente de leitura no arquivo
        // para o seu fim

        fseek(arquivo, 0, SEEK_END);

        // pega a posição corrente de leitura no arquivo
        tamanho = ftell(arquivo);

        rewind(arquivo);
        int a,i;

      for (i = 0; i < tamanho; i++) {

          fseek(arquivo, i, SEEK_SET);

          fread(&a,sizeof(a),1,arquivo);
          printf("letra: %c\n", a);
        }
          printf("tamanho: %0.0f bytes ou %0.3f kbytes\n", tamanho, (tamanho/1000));


    } else {
        printf("Arquivo inexistente");
    }
    fclose(arquivo);
    return 0;

}
