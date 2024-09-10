#ifndef RESTA_H
#define RESTA_H
#include "jogada.h"

bool ehSolucao(int** matriz, int tamanho);

bool resolver(int** matriz, int tamanho, int maxJogadas, int nJogadas);

void fazerJogada(int** matriz, int tamanho, Jogada jogadaAtual);

void desfazerJogada(int** matriz, int tamanho, Jogada jogadaAtual);

bool jogadaEhValida(int** matriz, int tamanho);

void gerarTodasJogadasPossiveis(Jogada jogadas[]);

#endif