/**
 * PROJETO E ANALISE DE ALGORITMOS II
 * TURMA 04P
 * PROJETO RESTA UM
 * ALAN MENIUK GLEIZER - 10416804
 * CAIO VINICIUS CORSINI FILHO - 10342005
 * GILBERTO DE MELO JÚNIOR - 10419275
 * **/
 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_LINHA 50

void printMatriz(int** matriz, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    printf("| ");
    for (int j = 0; j < tamanho; j++) {
      if (matriz[i][j] == -1) printf("  ");
      else if (matriz[i][j] == 0) printf("○ ");
      else if (matriz[i][j] == 1) printf("● ");
      //else printf("%d ", matriz[i][j]);
    }
    printf("|\n");
  }
}

// Fiz esta outra versao do printMatriz pois a versao antiga pode imprimir incorretamente dependendo do terminal (do Caio por exemplo)
void printMatrizASCII(int** matriz, int tamanho){
    for (int i = 0; i < tamanho; i++) {
    printf("| ");
    for (int j = 0; j < tamanho; j++) {
      if (matriz[i][j] == -1) printf("  ");
      else if (matriz[i][j] == 0) printf("0 ");
      else if (matriz[i][j] == 1) printf("1 ");
      //else printf("%d ", matriz[i][j]);
    }
    printf("|\n");
  }
}

// função determina o tamanho da matriz/tabuleiro analisando a qtd de elementos na primeira linha
// interessante validar, em algum momento, se linhas == colunas!
int determinarTamanho(char linha[]) {
    int i = 0;
    int tamanho = 0;

    while (linha[i] != '\n' && linha[i] != '\0') {
        char elemento = linha[i];
        if (elemento == '#' || elemento == 'o' || elemento == ' ') {
            tamanho++;
        }
        i++;
    }
    return tamanho - 2; // -2 pois agora temos # nas margens
}

// Retorna o numero de jogadas necessarias para finalizar o jogo
// Conta a quantidade de 1s presentes e faz um decremento no final
// Talvez seja interessante para o caso base e para o loop
int nJogadasNecessarias(int** matriz, int tamanho){
    int n = 0;
    for(int i=0; i<tamanho; i++){
        for(int j=0; j<tamanho; j++)
            if(matriz[i][j] == 1) n++;
    }
    return n-1;
}