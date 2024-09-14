#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogada.h"

// Retorna se a matriz esta solucionada ou nao
// Ve se soh tem uma bolinha restante
// checa se tem exatamente uma peca no meio
bool ehSolucao(int** matriz, int tamanho) {
    int meio = tamanho / 2;
    if (matriz[meio][meio] != 1) return false;

    int cont1 = 0;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] == 1) cont1++;
            if (cont1 > 1) return false;
        }
    }
    return cont1 == 1;
}

void fazerJogada(int** matriz, int tamanho, Jogada jogadaAtual){
    int linhaOrigem = jogadaAtual.daLin;
    int colunaOrigem = jogadaAtual.daCol;
    int linhaDestino = jogadaAtual.ateLin;
    int colunaDestino = jogadaAtual.ateCol;

    // ver se se é uma jogada vertical ou horizontal
    if (linhaOrigem == linhaDestino) {
        int colunaMeio = (colunaOrigem + colunaDestino) / 2;
        matriz[linhaOrigem][colunaMeio] = 0;
    } else if (colunaOrigem == colunaDestino) {
        int linhaMeio = (linhaOrigem + linhaDestino) / 2;
        matriz[linhaMeio][colunaOrigem] = 0;
    }


}

void desfazerJogada(int** matriz, int tamanho, Jogada jogadaAtual){

}

bool jogadaEhValida(int** matriz, int tamanho){
    return true;
}

void imprimirJogada(Jogada jog){
    printf("Linha: %d -> %d\n", jog.daLin+1, jog.ateLin+1);
    printf("Coluna: %d -> %d\n\n", jog.daCol+1, jog.ateCol+1);
}

void gerarTodasJogadasPossiveis(int** matriz, int tamanho, Jogada jogadas[]){
    int ind = 0;
    for(int i=0; i<tamanho; i++){
        for(int j=0; j<tamanho; j++){
            if(i+2 < tamanho && matriz[i][j] == 1){
                if(matriz[i+1][j] == 1 && matriz[i+2][j] == 0){ // Baixo
                    Jogada novaJogada;
                    novaJogada.daLin = i;
                    novaJogada.ateLin = i+2;
                    novaJogada.daCol = j;
                    novaJogada.ateCol = j;
                    jogadas[ind] = novaJogada;
                    ind++;
                }
            }
            if(i-2 >= 0 && matriz[i][j] == 1){
                if(matriz[i-1][j] == 1 && matriz[i-2][j] == 0){ // Cima
                    Jogada novaJogada;
                    novaJogada.daLin = i;
                    novaJogada.ateLin = i-2;
                    novaJogada.daCol = j;
                    novaJogada.ateCol = j;
                    jogadas[ind] = novaJogada;
                    ind++;
                }
            }
            if(j+2 < tamanho && matriz[i][j] == 1){
                if(matriz[i][j+1] == 1 && matriz[i][j+2] == 0){ // Direita
                    Jogada novaJogada;
                    novaJogada.daLin = i;
                    novaJogada.ateLin = i;
                    novaJogada.daCol = j;
                    novaJogada.ateCol = j+2;
                    jogadas[ind] = novaJogada;
                    ind++;
                }
            }
            if(j-2 >= 0 && matriz[i][j] == 1){
                if(matriz[i][j-1] == 1 && matriz[i][j-2] == 0){ // Esquerda
                    Jogada novaJogada;
                    novaJogada.daLin = i;
                    novaJogada.ateLin = i;
                    novaJogada.daCol = j;
                    novaJogada.ateCol = j-2;
                    jogadas[ind] = novaJogada;
                    ind++;
                }
            }
        }
    }
    Jogada sentinela;
    sentinela.daLin = -1;
    jogadas[ind] = sentinela;
}

bool resolver(int** matriz, int tamanho, int maxJogadas, int nJogadas){
    if(nJogadas == maxJogadas){
        if(ehSolucao(matriz, tamanho)){
            return true;
        } else {
            return false;
        }
    }
    Jogada arrJogadas[100];
    gerarTodasJogadasPossiveis(matriz, tamanho, arrJogadas);
    int i = 0;
    while(arrJogadas[i].daLin != -1){
        fazerJogada(matriz, tamanho, arrJogadas[i]);
        if(jogadaEhValida(matriz, tamanho)){
            bool result = resolver(matriz,tamanho,maxJogadas,nJogadas+1);
            if(result){
                // Imprimir jogada
                return true;
            }
        } else {
            desfazerJogada(matriz, tamanho, arrJogadas[i]);
        }
        i++;
    }
    return false;
}