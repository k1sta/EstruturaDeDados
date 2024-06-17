#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	struct no *esq, *dir;
	int val;
}tNo;

void insereNo(tNo** raiz, int val);
tNo* removeNo(tNo* raiz, int val);
tNo* valMin(tNo* no);
void imprimePreOrd(tNo* raiz);
void deletaArv(tNo* raiz);

int main (void){
	tNo *arvore = NULL;
	int val;
	char c;

	while(fscanf(stdin, "%c", &c) >= 1){
		if (c == 'p') {
			imprimePreOrd(arvore);
			printf("\n");
		}
		if (c == 'i') {
			fscanf(stdin, "%d", &val);
			insereNo(&arvore, val);
		}
		if (c == 'r') {
			fscanf(stdin, "%d", &val);
			arvore = removeNo(arvore, val);
		}
	}
	
	deletaArv(arvore);
	return 0;
}

void insereNo(tNo** raiz, int val){
	tNo* atual = *raiz;
	if(atual == NULL){
		atual = malloc(sizeof(tNo));
		if (atual == NULL){ exit(1); } //erro de alocacao
		atual->val = val;
		atual->dir = NULL;
		atual->esq = NULL;
		*raiz = atual;
	}
	else {
		if (val < atual->val) 
			insereNo(&(atual->esq), val);
		else
			insereNo(&(atual->dir), val);
	}	
}

tNo* removeNo(tNo* raiz, int val) {
    if (raiz == NULL) {
        return NULL;
    }
    if (val < raiz->val) {
        raiz->esq = removeNo(raiz->esq, val);
    } else if (val > raiz->val) {
        raiz->dir = removeNo(raiz->dir, val);
    } else {
        if (raiz->esq == NULL) {
            tNo *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL) {
            tNo *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        tNo* temp = valMin(raiz->dir);
        raiz->val = temp->val;
        raiz->dir = removeNo(raiz->dir, temp->val);
    }
    return raiz;
}

tNo* valMin(tNo* raiz) {
    tNo* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

void imprimePreOrd(tNo *raiz) {
    if (raiz) {
        printf("%d ", raiz->val);
        imprimePreOrd(raiz->esq);
        imprimePreOrd(raiz->dir);
    }
}

void deletaArv(tNo* raiz) {
    if (raiz == NULL) return;
    deletaArv(raiz->esq);
    deletaArv(raiz->dir);
    free(raiz);
}
