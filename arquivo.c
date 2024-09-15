#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#include "jogada.h"
#include "resta.h"
#include "arquivo.h"

#define TAM_LINHA 50
#define TAM_LINHA_OUT 75

// função abre o arquivo, determina o tamanho do jogo, cria uma matriz adequada e popula com as informações
// função retorna um ponteiro para a matriz e atualiza o tamanho
// ao usar matrizes com alocação dinâmica, não usamos matriz[][] (!!!)
int** carregarArquivo(int* tamanho) {

    // abertura do arquivo
    FILE *arquivo = fopen("inicio.txt", "r");
    if (!arquivo) {
        printf("Eh necessario um arquivo inicio.txt no diretorio do programa para execucao.\nO arquivo nao foi encontrado. Tente novamente.\n");
        return NULL;
    }

    // criação de vetor temporário para armazenar cada linha do arquivo
    char temp[TAM_LINHA];

    // determinação do tamanho do jogo
    // aproveitei essa determinação para validar se existe algum problema com o arquivo (vazio)
    if (fgets(temp, TAM_LINHA, arquivo) != NULL) {
        *tamanho = determinarTamanho(temp);
        // printf("Tamanho: %d\n", *tamanho);  // print de teste
    } else {
        printf("Erro ao ler a primeira linha do arquivo.\n");
        fclose(arquivo);
        return NULL;
    }

    // criação da matriz dinâmica
    int** matriz = (int**)malloc(*tamanho * sizeof(int*));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria para a matriz.\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *tamanho; i++) {
        matriz[i] = (int*)malloc(*tamanho * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memoria para a linha %d da matriz.\n", i);
            // Liberar a memória já alocada
            for (int k = 0; k < i; k++) {
                free(matriz[k]);
            }
            free(matriz);
            fclose(arquivo);
            return NULL;
        }
    }

    // Popular a matriz com os valores no arquivo
    // antes de entrar no loop, a primeira linha já está em temp pois usamos para determinar o tamanho!
    char *token = strtok(temp, ",");
    for (int k = 0; k < *tamanho; k++) {
      matriz[0][k] = atoi(token); // Armazena o valor convertido
      token = strtok(NULL, ",");  // Pega o próximo token
    }

    // agora podemos entrar no loop e ler todo o arquivo
    int i = 1; // linha
    int j = 0; // coluna
    while (fgets(temp, TAM_LINHA, arquivo) != NULL) {
        //printf("Linha: %s\n", temp); // PRINT PARA TESTES
        char *token = strtok(temp, ","); // a declaração de char novamente parece redundante mas não é (por algum motivo)..
        for (j = 0; j < *tamanho; j++) { // percorre coluna
            if (token != NULL) {
                matriz[i][j] = atoi(token); // Armazena o valor convertido
                token = strtok(NULL, ",");  // Pega o próximo token
            } else {
                printf("Erro na linha %d.\n", i + 1);
                break;
            }
        }
        i++;
    }

    if (i != j) printf("ERRO! A matriz precisa ser quadrada!\n");
    fclose(arquivo);
    return matriz;
}

// recebe um vetor de jogadas e imprime o conteúdo, formatado, de tras para frente, em um .txt
void outputJogadas (Jogada jogadas[], int numJogadas, int *contadorSaidas) {
  char nomeArquivo[51];
  sprintf(nomeArquivo, "saida_%d.csv", *contadorSaidas);
  FILE *arquivo;
  arquivo = fopen(nomeArquivo, "w");
  if (!arquivo)
  {
    printf("Falha na criacao do arquivo!\n");
    // return 0;
  }

  // loop para percorrer todo o vetor de jogadas
  for (int i = numJogadas - 1; i = 0; i--) {
    char temp[TAM_LINHA_OUT]; // vetor temporario para armazenar cada linha

    // snprintf para formatar elementos do struct. ver documentacao.
    snprintf(temp, TAM_LINHA, "Jogada %2d: peça em (%d, %d) -> (%d, %d).\n",
             i - numJogadas, jogadas[i].daLin, jogadas[i].daCol, jogadas[i].ateLin, jogadas[i].ateCol);
    // printf("%s", temp);  // print para testes

    // agora imprimimos a string formatada no arquivo de saida
    fprintf(arquivo, "%s", temp);
  }
  fclose(arquivo);
  (*contadorSaidas)++;
  // return 1;
}

void printMatrizArquivo(int** matriz, int tamanho, FILE* arquivo) {
  for (int i = 0; i < tamanho; i++) {
    printf("| ");
    for (int j = 0; j < tamanho; j++) {
      if (matriz[i][j] == -1) fprintf(arquivo, "  ");
      else if (matriz[i][j] == 0) fprintf(arquivo, "○ ");
      else if (matriz[i][j] == 1) fprintf(arquivo, "● ");
      //else printf("%d ", matriz[i][j]);
    }
    printf("|\n");
  }
}

// recebe um vetor de jogadas e imprime o conteúdo, formatado, de tras para frente, em um .txt
void outputJogadasTabuleiro (Jogada jogadas[], int numJogadas, int *contadorSaidas) {
  char nomeArquivo[51];
  sprintf(nomeArquivo, "saida_%d.csv", *contadorSaidas);
  FILE *arquivo;
  arquivo = fopen(nomeArquivo, "w");
  if (!arquivo)
  {
    printf("Falha na criacao do arquivo!\n");
    // return 0;
  }

  int tamanho;
  int** tabuleiro = carregarArquivo(&tamanho);

  fprintf(arquivo, "Tabuleiro inicial:\n");
  printMatrizArquivo(tabuleiro, tamanho, arquivo);

  // loop para percorrer todo o vetor de jogadas
  for (int i = numJogadas - 1; i = 0; i--) {
    char temp[TAM_LINHA_OUT]; // vetor temporario para armazenar cada linha

    // snprintf para formatar elementos do struct. ver documentacao.
    snprintf(temp, TAM_LINHA, "Jogada %2d: peça em (%d, %d) -> (%d, %d).\n",
             i - numJogadas, jogadas[i].daLin, jogadas[i].daCol, jogadas[i].ateLin, jogadas[i].ateCol);
    // printf("%s", temp);  // print para testes

    // agora imprimimos a string formatada no arquivo de saida
    fprintf(arquivo, "%s", temp);

    // e imprimimos o tabuleiro
    fazerJogada(tabuleiro, tamanho, jogadas[i]);
    printMatrizArquivo(tabuleiro, tamanho, arquivo);
  }
  fclose(arquivo);
  (*contadorSaidas)++;
}