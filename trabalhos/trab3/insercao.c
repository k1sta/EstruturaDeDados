#include <stdio.h>
#include <stdlib.h>

enum NoCor { RUBRO, NEGRO };

struct No {
    int chave;
    enum NoCor cor;
    struct No *esquerda, *direita, *pai;
};

struct No* criaNo(int chave);
void rotacionaEsq(struct No **raiz, struct No *x);
void rotacionaDir(struct No **raiz, struct No *y);
void corrige(struct No **raiz, struct No *z);
void insere(struct No **raiz, int chave);
void printPreOrdem(struct No *raiz);

int main (void){
	struct No *arvore = NULL;
	int val;
	char c;

	while(fscanf(stdin, "%c", &c) >= 1){
		if (c == 'p') {
			printPreOrdem(arvore);
			printf("\n");
		}
		if (c == 'i') {
			fscanf(stdin, "%d", &val);
			insere(&arvore, val);
		}
	}
	return 0;
}

struct No* criaNo(int chave) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->chave = chave;
    novoNo->cor = RUBRO;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->pai = NULL;

    return novoNo;
}

void rotacionaEsq(struct No **raiz, struct No *x) {
    struct No *y = x->direita;
    x->direita = y->esquerda;
    if (x->direita != NULL)
        x->direita->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        (*raiz) = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
    y->esquerda = x;
    x->pai = y;
}

void rotacionaDir(struct No **raiz, struct No *y) {
    struct No *x = y->esquerda;
    y->esquerda = x->direita;
    if (y->esquerda != NULL)
        y->esquerda->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        (*raiz) = x;
    else if (y == y->pai->esquerda)
        y->pai->esquerda = x;
    else
        y->pai->direita = x;
    x->direita = y;
    y->pai = x;
}

void corrige(struct No **raiz, struct No *z) {
    struct No *pai = NULL;
    struct No *avo = NULL;

    while ((z != *raiz) && (z->cor != NEGRO) && (z->pai->cor == RUBRO)) {
        pai = z->pai;
        avo = z->pai->pai;

        if (pai == avo->esquerda) {
            struct No *tio = avo->direita;
            if (tio != NULL && tio->cor == RUBRO) {
                avo->cor = RUBRO;
                pai->cor = NEGRO;
                tio->cor = NEGRO;
                z = avo;
            } else {
                if (z == pai->direita) {
                    rotacionaEsq(raiz, pai);
                    z = pai;
                    pai = z->pai;
                }
                rotacionaDir(raiz, avo);
                int temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = temp;
                z = pai;
            }
        } else {
            struct No *tio = avo->esquerda;
            if ((tio != NULL) && (tio->cor == RUBRO)) {
                avo->cor = RUBRO;
                pai->cor = NEGRO;
                tio->cor = NEGRO;
                z = avo;
            } else {
                if (z == pai->esquerda) {
                    rotacionaDir(raiz, pai);
                    z = pai;
                    pai = z->pai;
                }
                rotacionaEsq(raiz, avo);
                int temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = temp;
                z = pai;
            }
        }
    }
    (*raiz)->cor = NEGRO;
}

void insere(struct No **raiz, int chave) {
    struct No *no = criaNo(chave);
    struct No *temp = *raiz;
    struct No *pai = NULL;

    while (temp != NULL) {
        pai = temp;
        if (no->chave < temp->chave)
            temp = temp->esquerda;
        else
            temp = temp->direita;
    }
    no->pai = pai;

    if (pai == NULL)
        *raiz = no;
    else if (no->chave < pai->chave)
        pai->esquerda = no;
    else
        pai->direita = no;

    corrige(raiz, no);
}

void printPreOrdem(struct No *raiz) {
    if (raiz == NULL)
        return;

    printf("%d", raiz->chave);
    if(raiz->cor == RUBRO) printf("%s", "R ");
    else printf("%s", "N ");

    printPreOrdem(raiz->esquerda);
    printPreOrdem(raiz->direita);
}