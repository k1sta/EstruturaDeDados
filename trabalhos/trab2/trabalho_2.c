#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *direita, *esquerda;
} NoArv;

void imprimirEmPreOrdem(NoArv *raiz) {
    if (raiz) {
        printf("%d ", raiz->chave);
        imprimirEmPreOrdem(raiz->esquerda);
        imprimirEmPreOrdem(raiz->direita);
    }
}

void inserirArvore(NoArv **raiz, int x) {
    if ((*raiz) == NULL) {
        *raiz = malloc(sizeof(NoArv));
        (*raiz)->chave = x;
        (*raiz)->direita = NULL;
        (*raiz)->esquerda = NULL;
    }
    else {
        if (x < (*raiz)->chave) 
            inserirArvore(&((*raiz)->esquerda), x);
        else
            inserirArvore((&(*raiz)->direita), x);
    }
}

// Busca que "retornará" o pai e o filho a serem removidos
void buscarArvore(NoArv *raiz, int x, NoArv **pai, NoArv **pt) {
    *pai = NULL;
    *pt = raiz;
    while ((*pt != NULL) && ((*pt)->chave != x)) {
        *pai = *pt;
        if (x < (*pt)->chave) *pt = (*pt)->esquerda;
        else *pt = (*pt)->direita;
    }
}

NoArv* removerArvore(NoArv *raiz, int x) {
    // Buscar o nó a ser removido e seu pai
    NoArv* pt = NULL;
    NoArv* pai = NULL;
    buscarArvore(raiz, x, &pai, &pt);

    // Não achei o nó a ser removido
    if (pt == NULL) return raiz;
        
    // Primeira possibilidade: O nó a ser removido é uma folha
    if (pt->esquerda == NULL && pt->direita == NULL) {
        // É folha e raíz
        if (pai == NULL) {
            free(pt);
            return NULL; // A árvore estava com apenas um nó (raiz)
        }
        // Precisamos setar NULL para resetar o lado direito ou esquerdo do pai para as próximas iterações
        if (pai->esquerda == pt) pai->esquerda = NULL; 
        else pai->direita = NULL; 
        
        // Liberamos nossa folha da memória
        free(pt);
    }
    // Segunda possibilidade: O nó a ser removido possui apenas 1 filho
    else if (pt->esquerda == NULL || pt->direita == NULL) {
        NoArv* filho = (pt->esquerda != NULL) ? pt->esquerda : pt->direita;
        if (pai == NULL) {
            free(pt);
            return filho; 
        }
        if (pai->esquerda == pt) {
            pai->esquerda = filho;
        } else {
            pai->direita = filho;
        }
        free(pt);
    }
    // Caso 3: Nó pt tem dois filhos
    else {
        NoArv* paiDoSucessor = pt;
        NoArv* sucessor = pt->direita;
        
        // Encontrar o menor nó na subárvore direita
        while (sucessor->esquerda != NULL) {
            paiDoSucessor = sucessor;
            sucessor = sucessor->esquerda;
        }
        
        // Substituir o valor do alvo pelo valor do sucessor
        pt->chave = sucessor->chave;
        
        // Ajustar ponteiros para remover o sucessor
        if (paiDoSucessor->esquerda == sucessor) {
            paiDoSucessor->esquerda = sucessor->direita;
        } else {
            paiDoSucessor->direita = sucessor->direita;
        }
        
        free(sucessor);
    }
    
    return raiz;
}

int main() {
    NoArv *raiz = NULL;
    int x;
    char str[2];

    while (scanf("%s", str) == 1) {
        if (str[0] == 'p') {
            imprimirEmPreOrdem(raiz);
            printf("\n");
        }
        if (str[0] == 'i') {
            scanf("%d", &x);
            inserirArvore(&raiz, x);
        }
        if (str[0] == 'r') {
            scanf("%d", &x);
            raiz = removerArvore(raiz, x);
        }
    }
    return 0;
}
