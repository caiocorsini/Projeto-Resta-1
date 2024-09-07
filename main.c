#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//cd "DIRETORIO" && gcc -o main main.c && main


int exemplo_matriz[7][7] = {
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
      {1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 0, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1},
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1}
};

int exemplo_matriz_solucionada[7][7] = {
    {-1, -1, 0, 0, 0, -1, -1},
    {-1, -1, 0, 0, 0, -1, -1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {-1, -1, 0, 0, 0, -1, -1},
    {-1, -1, 0, 0, 0, -1, -1}
};


// Estrutura para jogada
typedef struct {
    int daLin;
    int daCol;
    int ateLin;
    int ateCol;
} Jogada;


// Retorna o numero de jogadas necessarias para finalizar o jogo
// Conta a quantidade de 1s presentes e faz um decremento no final
// Talvez seja interessante para o caso base e para o loop
int nJogadasNecessarias(int* matriz, int lin, int col){
    int n = 0;
    for(int i=0; i<lin; i++){
        for(int j=0; j<col; j++)
            if(*(matriz + i * col + j) == 1) n++;
    }
    return n-1;
}


// Retorna se a matriz esta solucionada ou nao
// Ve se soh tem uma bolinha restante
// checa se tem exatamente uma peca no meio
bool ehSolucao(int* matriz, int lin, int col) {
    int linhaMeio = lin / 2;
    int colunaMeio = col / 2;
    if (*(matriz + linhaMeio * col + colunaMeio) != 1) return false;

    int cont1 = 0;
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (*(matriz + i * col + j) == 1) cont1++;
            if (cont1 > 1) return false;
        }
    }
    return cont1 == 1;
}


// Funcao para imprimir tabuleiro
// Para ajudar no desenvolvimento
void imprimirTabuleiro(int* matriz, int lin, int col){
    for(int i=0; i<lin; i++){
        for(int j=0; j<col; j++)
            printf("%d ", *(matriz + i * col + j));
        printf("\n");
    }
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

void gerarTodasJogadasPossiveis(){
    
}

void main(){
    //printf("jogadas necessarias: %d\n", nJogadasNecessarias((int*)exemplo_matriz,7,7));
    //printf("%d", ehSolucao((int*)exemplo_matriz_solucionada,7,7));
    //imprimirTabuleiro((int*)exemplo_matriz,7,7);
}