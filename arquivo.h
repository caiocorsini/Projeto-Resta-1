#ifndef ARQUIVO_H
#define ARQUIVO_H

int** carregarArquivo(int* tamanho);
int outputJogadas (Jogada jogadas[], int numJogadas, int *contadorSaidas);
void printMatrizArquivo(int** matriz, int tamanho, FILE* arquivo);
int outputJogadasTabuleiro (Jogada jogadas[], int numJogadas, int *contadorSaidas);

#endif // ARQUIVO_H