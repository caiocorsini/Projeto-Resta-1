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

int main(){
    // variaveis para o jogo
    int tamanho;
    int** tabuleiro;
    int qtdMaxJogadas;
    Jogada* jogadas = NULL; // precisa ser criado em main, mas só saberemos o tamanho após o usuário informar.. solução = malloc
    int contadorSaidas = 1;
    int opcao = 1;

    // menu

        while(opcao > 0 && opcao < 5) {
            printf("\n#####  RESTA UM  #####\n");
            //printf("--- menu principal ---\n");
            printf("1. Carregar arquivo\n");
            printf("2. Resolver jogo\n");
            printf("3. Exportar solução\n");
            printf("4. Encerrar\n");
            printf("   Selecione uma opção: ");
            scanf("%d", &opcao);
            if (opcao > 4 || opcao < 1) printf("Opção inválida! Tente novamente...\n");

            switch (opcao) {
                case 1:
                    tabuleiro = carregarArquivo(&tamanho);

                    // print de teste - pos carregamento
                    printf("Arquivo carregado!\n");
                    // printMatrizASCII(tabuleiro, tamanho); // print para testes

                    // criação do vetor de jogadas
                    qtdMaxJogadas = nJogadasNecessarias(tabuleiro, tamanho);
                    jogadas = (Jogada*)malloc(qtdMaxJogadas * sizeof(Jogada));
                    if (jogadas == NULL) {
                        printf("Erro ao alocar memória para a solução!\n");
                        return 1;
                    }
                    break;

                case 2:
                    if (jogadas == NULL) {
                            printf("Nenhum arquivo foi carregado. Carregue o arquivo primeiro.\n");
                            break;
                        }
                    // inicio
                    resolver(tabuleiro, tamanho, qtdMaxJogadas, 0, jogadas);
                    break;
                
                case 3:
                    if (outputJogadasTabuleiro(jogadas, qtdMaxJogadas, &contadorSaidas)) {
                        printf("Arquivo exportado com sucesso!\n");
                    }
                    break;

                case 4:
                printf("Encerrando programa...\n");
                    return 1;
            }
        }

}
