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
    Jogada* jogadas = NULL; // precisa ser criado em main, mas só saberemos o tamanho após o usuário informar.. oslução malloc
    int contadorSaidas = 1;
    int opcao;

    // menu

    do {
        printf("#####  RESTA UM  #####\n");
        printf("--- menu principal ---\n");
        printf("1. Carregar arquivo\n");
        printf("2. Resolver jogo\n");
        printf("3. Exportar solução\n");
        printf("4. Encerrar\n");
        printf("   Seleciona uma opção: ");
        scanf("%d", &opcao);
        if (opcao > 4 || opcao < 1) printf("Opção inválida! Tente novamente...\n");
    } while (opcao > 4 || opcao < 1);

    switch (opcao) {
        case 1:
            tabuleiro = carregarArquivo(&tamanho);

            // print de teste - pos carregamento
            printf("Arquivo carregado: \n");
            printMatrizASCII(tabuleiro, tamanho);

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
            // TODO para poder imprimir o vetor, acho que precisamos fazer uma mudança sutil na função principal
            // ao inves de criar um vetor de Jogada dentro de resolver(), criamos em main e passamos como parâmetro, para termos acesso após a execução
            break;
        
        case 3:
            if (outputJogadas(jogadas, qtdMaxJogadas, &contadorSaidas)) {
                printf("Arquivo exportado com sucesso!\n");
            }
            break;
        case 4:
        printf("Encerrando programa...\n");
            return 1;
    }

    


    
    // Teste gerar jogadas
    Jogada exemploJogadas[100];
    gerarTodasJogadasPossiveis(tabuleiro,tamanho,exemploJogadas);
    int i=0;
    while(exemploJogadas[i].daLin != -1){
        imprimirJogada(exemploJogadas[i]);
        i++;
    }
    
}
