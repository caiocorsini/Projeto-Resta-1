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

void resolver(){

}

void fazerJogada(){

}

void desfazerJogada(){

}

bool jogadaEhValida(){
    return true;
}

void gerarTodasJogadasPossiveis(Jogada jogadas[]){
    
}