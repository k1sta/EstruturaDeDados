#include <stdio.h>
#include <stdlib.h>
#define MAX 30000

/*
DESCRIÇÃO: Implementação da estrutura de dados Union-Find com alocação dinâmica de memória.
FUNÇÃO: Dado um conjunto de N elementos, a estrutura Union-Find permite realizar as seguintes operações:
    - Inicializar a estrutura
    - Encontrar o representante do conjunto de um elemento
    - Unir dois conjuntos
    - Liberar o espaço de memória usado pela estrutura
*/


int* id;    // vetor dos representantes do elemento i
int* tam;    // vetor com o tamanho dos conjuntos

void initialize(int N); // inicializa as estruturas
int find(int p); // encontrar o representante do conjunto de p
void Union(int p, int q); // une os conjuntos de p e q
void resetStructures(); // libera o espaço de memória usado por id e tam
int tamMax(int N); // retorna o tamanho do maior conjunto


int main() {
    unsigned int N, M, a, b, temp;
    scanf("%d", &temp);
    while (temp--) {
        scanf("%d %d", &N, &M);
        initialize(N);
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &a, &b);
            Union(--a, --b);
        }
        printf("%d\n", tamMax(N));
        resetStructures(id, tam);
    }
    return 0;
}

void initialize(int N) {
    id = (int*) malloc(N * sizeof(int));
    tam = (int*) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        id[i] = i;
        tam[i] = 1;
    }
}

int find(int p) {
    if (p != id[p])
        id[p] = find(id[p]);
    return id[p];
}

void Union(int p, int q) {
    int i = find(p);
    int j = find(q);
    
    // raiz com o menor número de elementos aponta para a raiz com o maior número de elementos
    if (i != j){
        if (tam[i] < tam[j]){ 
            id[i] = j; tam[j] += tam[i]; 
        } else {
            id[j] = i; tam[i] += tam[j];
        }
    }
}

void resetStructures(){
    free(id);
    free(tam);
}

int tamMax(int N){
    int max = 0;
    for (int i = 0; i < N; i++)
        if (tam[i] > max)
            max = tam[i];
    return max;
}