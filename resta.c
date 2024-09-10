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

}

void desfazerJogada(int** matriz, int tamanho, Jogada jogadaAtual){

}

bool jogadaEhValida(int** matriz, int tamanho){
    return true;
}

void gerarTodasJogadasPossiveis(Jogada jogadas[]){
    
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
    gerarTodasJogadasPossiveis(arrJogadas);
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