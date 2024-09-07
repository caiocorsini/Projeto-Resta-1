#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINHA 50

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

void printMatriz(int** matriz, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    printf("| ");
    for (int j = 0; j < tamanho; j++) {
      if (matriz[i][j] == -1) printf("  ");
      else printf("%d ", matriz[i][j]);
    }
    printf("|\n");
  }
}

int determinarTamanho(char linha[]) {
    int i = 0;
    int tamanho = 0;

    while (linha[i] != '\n' && linha[i] != '\0') {
        char elemento = linha[i];
        if (elemento == '1' || elemento == '0' || (elemento == '-' && linha[i+1] == '1')) {
            tamanho++;
            if (elemento == '-') i++; // para não contar - e 1 (no caso de -1) como elementos separados
        }
        i++;
    }
    return tamanho;
}

// função abre o arquivo, determina o tamanho do jogo, cria uma matriz adequada e popula com as informações
// função retorna um ponteiro para a matriz e atualiza o tamanho
// ao usar matrizes com alocação dinâmica, não usamos matriz[][] (!!!)
int** carregarArquivo(int* tamanho) {

    // Abrir o arquivo
    FILE *arquivo = fopen("inicio.txt", "r");
    if (!arquivo) {
        printf("Eh necessario um arquivo inicio.txt no diretorio do programa para execucao.\nO arquivo nao foi encontrado. Tente novamente.\n");
        return NULL;
    }

    // Vetor temporário para armazenar cada linha do arquivo
    char temp[TAM_LINHA];

    // Determinação do tamanho do jogo
    if (fgets(temp, TAM_LINHA, arquivo) != NULL) {
        *tamanho = determinarTamanho(temp);
        printf("Tamanho: %d\n", *tamanho);
    } else {
        printf("Erro ao ler a primeira linha do arquivo.\n");
        fclose(arquivo);
        return NULL;
    }

    // Criação da matriz dinâmica
    int** matriz = (int**)malloc(*tamanho * sizeof(int*));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria para a matriz.\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *tamanho; i++) {
        matriz[i] = (int*)malloc(*tamanho * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memoria para a linha %d da matriz.\n", i);
            // Liberar a memória já alocada
            for (int k = 0; k < i; k++) {
                free(matriz[k]);
            }
            free(matriz);
            fclose(arquivo);
            return NULL;
        }
    }

    // Popular a matriz com os valores no arquivo
    // antes de entrar no loop, a primeira linha já está me temp pois usamos para determinar o tamanho!
    char *token = strtok(temp, ",");
    for (int k = 0; k < *tamanho; k++) {
      matriz[0][k] = atoi(token); // Armazena o valor convertido
      token = strtok(NULL, ",");  // Pega o próximo token
    }

    // agora podemos entrar no loop
    int i = 1; // linha
    while (fgets(temp, TAM_LINHA, arquivo) != NULL) {
        //printf("Linha: %s\n", temp); // PRINT PARA TESTES

        char *token = strtok(temp, ",");
        for (int j = 0; j < *tamanho; j++) { // percorre coluna
            if (token != NULL) {
                matriz[i][j] = atoi(token); // Armazena o valor convertido
                token = strtok(NULL, ",");  // Pega o próximo token
            } else {
                printf("Erro na linha %d.\n", i + 1);
                break;
            }
        }
        i++;
    }

    fclose(arquivo);
    return matriz;
}



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

void gerarTodasJogadasPossiveis(Jogada jogadas[]){
    
}

void main(){
    //printf("jogadas necessarias: %d\n", nJogadasNecessarias((int*)exemplo_matriz,7,7));
    //printf("%d", ehSolucao((int*)exemplo_matriz_solucionada,7,7));
    //imprimirTabuleiro((int*)exemplo_matriz,7,7);
    int tamanho;
    int** matriz = carregarArquivo(&tamanho);
    printMatriz(matriz, tamanho);
    
}