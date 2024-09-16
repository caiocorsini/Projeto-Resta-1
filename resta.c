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

void imprimirJogada(Jogada jog){
    printf("Linha: %d -> %d\n", jog.daLin+1, jog.ateLin+1);
    printf("Coluna: %d -> %d\n\n", jog.daCol+1, jog.ateCol+1);
}


// Gera todas as jogadas possiveis para um estado especifico do tabuleiro e popula a array de jogadas
// Essa array eh depois usada em resolver() para testar todas as possibilidades de jogadas
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
    sentinela.daLin = -1; // Usa variavel sentinela para marcar o fim da array de jogadas
    jogadas[ind] = sentinela;
}

// Funcao principal para resolver que usa backtracking
bool resolver(int** matriz, int tamanho, int maxJogadas, int nJogadas, Jogada* jogadasDeSolucao){
    // Casos base para checar se já alcancou o maximo de jogadas
    if (ehSolucao(matriz, tamanho)) return true;
    if (nJogadas == maxJogadas) return false;
    Jogada arrJogadas[66]; // Array auxiliar para armazenar todas as jogadas possiveis
    gerarTodasJogadasPossiveis(matriz, tamanho, arrJogadas);
    int i = 0;
    while(arrJogadas[i].daLin != -1){
        fazerJogada(matriz, tamanho, arrJogadas[i]);
        if(resolver(matriz,tamanho,maxJogadas,nJogadas+1,jogadasDeSolucao)){
            //printf("(%d,%d) -> (%d,%d)\n", arrJogadas[i].daLin, arrJogadas[i].daCol, arrJogadas[i].ateLin, arrJogadas[i].ateCol);
            jogadasDeSolucao[nJogadas] = arrJogadas[i];
            return true;
        }     
        desfazerJogada(matriz, tamanho, arrJogadas[i]);
        i++;
    }
    return false;
}