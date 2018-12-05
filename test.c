#include <stdio.h>



int main(int argc, char const *argv[]) {
  int vet[3] = {0,1,2};
  int i;
  for (i = 0; i < 3; i++) {
    printf("valor em %d: %d\n",i,vet[i] );
  }
  return 0;
}
