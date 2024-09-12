#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uteis.h"
#include "jogada.h"
#include "resta.h"

#define TAM_LINHA 50

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


void main(){
    int tamanho;
    int** matriz = carregarArquivo(&tamanho);
    printMatrizASCII(matriz, tamanho);

    // Teste gerar jogadas
    Jogada exemploJogadas[100];
    gerarTodasJogadasPossiveis(matriz,tamanho,exemploJogadas);
    int i=0;
    while(exemploJogadas[i].daLin != -1){
        imprimirJogada(exemploJogadas[i]);
        i++;
    }
}
