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
    int** tabuleiro = carregarArquivo(&tamanho);
    int qtdMaxJogadas = nJogadasNecessarias(tabuleiro, tamanho);
    Jogada jogadas[qtdMaxJogadas];
    int contadorSaidas;

    // print de teste - pos carregamento
    printf("Arquivo carregado: \n");
    printMatrizASCII(tabuleiro, tamanho);

    // inicio
    resolver(tabuleiro, tamanho, qtdMaxJogadas, 0);
    // TODO para poder imprimir o vetor, acho que precisamos fazer uma mudança sutil na função principal
    // ao inves de criar um vetor de Jogada dentro de resolver(), criamos em main e passamos como parâmetro, para termos acesso após a execução
    
    // Teste gerar jogadas
    Jogada exemploJogadas[100];
    gerarTodasJogadasPossiveis(tabuleiro,tamanho,exemploJogadas);
    int i=0;
    while(exemploJogadas[i].daLin != -1){
        imprimirJogada(exemploJogadas[i]);
        i++;
    }
    
}
