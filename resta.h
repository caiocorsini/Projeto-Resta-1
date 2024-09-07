#ifndef RESTA_H
#define RESTA_H
#include "jogada.h"

bool ehSolucao(int** matriz, int tamanho);
void resolver();

void fazerJogada();

void desfazerJogada();

bool jogadaEhValida();

void gerarTodasJogadasPossiveis(Jogada jogadas[]);

#endif