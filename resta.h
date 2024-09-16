#ifndef RESTA_H
#define RESTA_H
#include "jogada.h"

bool ehSolucao(int** matriz, int tamanho);

bool resolver(int** matriz, int tamanho, int maxJogadas, int nJogadas, Jogada* jogadasDeSolucao);

void fazerJogada(int** matriz, int tamanho, Jogada jogadaAtual);

void desfazerJogada(int** matriz, int tamanho, Jogada jogadaAtual);

void gerarTodasJogadasPossiveis(int** matriz, int tamanho, Jogada jogadas[]);

void imprimirJogada(Jogada jog);

#endif