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



void fazerJogada(int** matriz, int tamanho, Jogada jogadaAtual) {
    // vertical
    if (jogadaAtual.daCol == jogadaAtual.ateCol) {
        // de cima para baixo
        if (jogadaAtual.daLin < jogadaAtual.ateLin) {
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 0;
            matriz[jogadaAtual.daLin + 1][jogadaAtual.daCol] = 0;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 1;
        }
            // de baixo para cima
        else {
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 0;
            matriz[jogadaAtual.daLin - 1][jogadaAtual.daCol] = 0;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 1;
        }
    }
        // horizontal
    else if (jogadaAtual.daLin == jogadaAtual.ateLin) {
        //  esquerda para direita
        if (jogadaAtual.daCol < jogadaAtual.ateCol) {
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 0;
            matriz[jogadaAtual.daLin][jogadaAtual.daCol + 1] = 0;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 1;
        }
            // direita para esquerda
        else {
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 0;
            matriz[jogadaAtual.daLin][jogadaAtual.daCol - 1] = 0;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 1;
        }
    }
}




void desfazerJogada(int** matriz, int tamanho, Jogada jogadaAtual) {

    // vertical
    if (jogadaAtual.daCol == jogadaAtual.ateCol) {
        // de cima para baixo
        if(jogadaAtual.daLin < jogadaAtual.ateLin) {
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 1;
            matriz[jogadaAtual.daLin + 1][jogadaAtual.daCol] = 1;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 0;
        } else {
            // de baixo para cima
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 1;
            matriz[jogadaAtual.daLin -1][jogadaAtual.daCol] = 1;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 0;
        }
        // horizontal
    } else if (jogadaAtual.daLin == jogadaAtual.ateLin) {
        // esquerda para direita
        if(jogadaAtual.daCol < jogadaAtual.ateCol) {
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 1;
            matriz[jogadaAtual.daLin][jogadaAtual.daCol + 1] = 1;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 0;
        } else {
            // direita para esquerda
            matriz[jogadaAtual.daLin][jogadaAtual.daCol] = 1;
            matriz[jogadaAtual.daLin][jogadaAtual.daCol - 1] = 1;
            matriz[jogadaAtual.ateLin][jogadaAtual.ateCol] = 0;
        }
    }

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

bool resolver(int** matriz, int tamanho, int maxJogadas, int nJogadas, Jogada* arrJogadas){
    if(nJogadas == maxJogadas){
        if(ehSolucao(matriz, tamanho)){
            return true;
        } else {
            return false;
        }
    }
    // Jogada arrJogadas[100]; // agora esse vetor é passado como parametro da função
    gerarTodasJogadasPossiveis(matriz, tamanho, arrJogadas);
    int i = 0;
    while(arrJogadas[i].daLin != -1){
        fazerJogada(matriz, tamanho, arrJogadas[i]);
        if(jogadaEhValida(matriz, tamanho)){
            bool result = resolver(matriz,tamanho,maxJogadas,nJogadas+1, arrJogadas);
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