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
#include "uteis.h"
#include "jogada.h"
#include "resta.h"
#include "arquivo.h"

#define TAM_LINHA 50
#define TAM_LINHA_OUT 75

// função auxiliar para tranformar a matriz de chars de entrada em uma matriz de int
int converterEntrada (char c) {
  if (c == '#') return -1;
  if (c == 'o') return 1;
  if (c == ' ') return 0;
}

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
    // isso não é mais necessário pois, agora, a primeira linha é apenas a margem do tabuleiuro (#########)
    // antes de entrar no loop, a primeira linha já está em temp pois usamos para determinar o tamanho!
    // char *token = strtok(temp, ","); // resquício da implementação com strtok (entrada com peças separadas por ,)
    /*
    for (int k = 0; k < *tamanho; k++) {
      matriz[0][k] = converterEntrada(temp[k]); // Armazena o valor convertido
    }
    */

    // agora podemos entrar no loop e ler todo o arquivo
    int i = 0; // linha // era 1 na leitura original (pré formatação com margens), para não sobrescrever a primeira linha
    int j = 0; // coluna
    int l = 0; // 
    while (l < *tamanho) { // não é mais while fgets != null, pois precisamos ignorar a última linha
      fgets(temp, TAM_LINHA, arquivo);
        //printf("Linha: %s\n", temp); // PRINT PARA TESTES
        // char *token = strtok(temp, ","); // a declaração de char novamente parece redundante mas não é (por algum motivo)..
        for (j = 0; j < *tamanho; j++) { // percorre coluna
            if (temp != NULL) {
                matriz[i][j] = converterEntrada(temp[j+1]); // Armazena o valor convertido // j+1 em temp para ignorar a margem
                //token = strtok(NULL, ",");  // Pega o próximo token
            } else {
                printf("Erro na linha %d.\n", i + 1);
                break;
            }
        }
        i++;
        l++;
    }

    if (i != j) printf("ERRO! A matriz precisa ser quadrada!\n");
    fclose(arquivo);
    return matriz;
}

// recebe um vetor de jogadas e imprime o conteúdo, passo-a-passo (instruções)
int outputJogadas (Jogada jogadas[], int numJogadas, int *contadorSaidas) {
  char nomeArquivo[51];
  sprintf(nomeArquivo, "restaum_%d.out", *contadorSaidas);
  FILE *arquivo;
  arquivo = fopen(nomeArquivo, "w");
  if (!arquivo)
  {
    printf("Falha na criacao do arquivo!\n");
    return 0;
  }

  // loop para percorrer todo o vetor de jogadas
  for (int i = 0; i < numJogadas; i++) {
    char temp[TAM_LINHA_OUT]; // vetor temporario para armazenar cada linha

    // snprintf para formatar elementos do struct. ver documentacao.
    snprintf(temp, TAM_LINHA, "Jogada %2d: peça em (%d, %d) -> (%d, %d).\n",
             i, jogadas[i].daLin, jogadas[i].daCol, jogadas[i].ateLin, jogadas[i].ateCol);
    // printf("%s", temp);  // print para testes

    // agora imprimimos a string formatada no arquivo de saida
    fprintf(arquivo, "%s", temp);
  }
  fclose(arquivo);
  (*contadorSaidas)++;
  return 1;
}

// função auxiliar para imprimir a matriz atual em um arquivo
void printMatrizArquivo(int** matriz, int tamanho, FILE* arquivo) {
  fprintf(arquivo, "#########\n"); // margem superior
  for (int i = 0; i < tamanho; i++) {
    fprintf(arquivo, "#"); // margem esquerda
    for (int j = 0; j < tamanho; j++) {
      if (matriz[i][j] == -1) fprintf(arquivo, "#");
      else if (matriz[i][j] == 0) fprintf(arquivo, " ");
      else if (matriz[i][j] == 1) fprintf(arquivo, "o");
      //else printf("%d ", matriz[i][j]);
    }
    fprintf(arquivo, "#\n"); // margem direita
      }
  fprintf(arquivo, "#########\n\n"); // margem inferior
}

// recebe um vetor de jogadas e imprime cada etapa da resolução do tabuleiro
int outputJogadasTabuleiro (Jogada jogadas[], int numJogadas, int *contadorSaidas) {
  char nomeArquivo[51];
  sprintf(nomeArquivo, "restaum_%d.out", *contadorSaidas);
  FILE *arquivo;
  arquivo = fopen(nomeArquivo, "w");
  if (!arquivo)
  {
    printf("Falha na criacao do arquivo!\n");
    return 0;
  }

  // cramos um novo tabuleiro para realizar as jogadas
  int tamanho;
  int** tabuleiro = carregarArquivo(&tamanho);

  //fprintf(arquivo, "Tabuleiro inicial:\n");
  printMatrizArquivo(tabuleiro, tamanho, arquivo);

  // loop para percorrer todo o vetor de jogadas
  for (int i = 0; i < numJogadas; i++) {
    char temp[TAM_LINHA_OUT]; // vetor temporario para armazenar cada linha

    // imprimimos o tabuleiro
    fazerJogada(tabuleiro, tamanho, jogadas[i]);
    printMatrizArquivo(tabuleiro, tamanho, arquivo);
  }
  fclose(arquivo);
  (*contadorSaidas)++;
  return 1;
}