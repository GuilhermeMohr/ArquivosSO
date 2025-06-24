#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct No {
    int info;
    int altura;
    struct No* esq;
    struct No* dir;
} No;

typedef struct {
    No* raiz;
} ArvoreBinariaVLI;

int maxS(int a, int b) {
    return (a > b) ? a : b;
}

int calcularAltura(No* aux) {
    if (aux == NULL) return 0;
    return 1 + maxS(aux->esq ? aux->esq->altura : 0, aux->dir ? aux->dir->altura : 0);
}

int calcularDesequilibrio(No* esq, No* dir) {
    return (esq ? esq->altura : 0) - (dir ? dir->altura : 0);
}

No* equilibrar(No* aux, int n);

No* inserirVliR(int newInfo, No* aux) {
    if (aux == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->info = newInfo;
        novo->altura = 1;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (newInfo < aux->info) {
        aux->esq = inserirVliR(newInfo, aux->esq);
    } else {
        aux->dir = inserirVliR(newInfo, aux->dir);
    }

    aux->altura = calcularAltura(aux);
    int n = calcularDesequilibrio(aux->esq, aux->dir);
    if (n > 1 || n < -1) {
        aux = equilibrar(aux, n);
    }

    return aux;
}

No* equilibrar(No* aux, int n) {
    if (n > 1) {
        int ne = calcularDesequilibrio(aux->esq->esq, aux->esq->dir);
        if (ne >= 0) {
            No* x = aux->esq;
            aux->esq = x->dir;
            x->dir = aux;

            aux->altura = calcularAltura(aux);
            x->altura = calcularAltura(x);

            return x;
        } else {
            No* w = aux->esq->dir;

            aux->esq->dir = w->esq;
            w->esq = aux->esq;

            aux->esq = w->dir;
            w->dir = aux;

            w->esq->altura = calcularAltura(w->esq);
            w->dir->altura = calcularAltura(w->dir);
            w->altura = calcularAltura(w);

            return w;
        }
    } else {
        int nd = calcularDesequilibrio(aux->dir->esq, aux->dir->dir);
        if (nd <= 0) {
            No* y = aux->dir;
            aux->dir = y->esq;
            y->esq = aux;

            aux->altura = calcularAltura(aux);
            y->altura = calcularAltura(y);

            return y;
        } else {
            No* z = aux->dir->esq;

            aux->dir->esq = z->dir;
            z->dir = aux->dir;

            aux->dir = z->esq;
            z->esq = aux;

            z->dir->altura = calcularAltura(z->dir);
            z->esq->altura = calcularAltura(z->esq);
            z->altura = calcularAltura(z);

            return z;
        }
    }
}

void prefixadoR(No* aux) {
    if (aux == NULL) return;
    printf("%d  ", aux->info);
    prefixadoR(aux->esq);
    prefixadoR(aux->dir);
}

void infixadoR(No* aux) {
    if (aux == NULL) return;
    infixadoR(aux->esq);
    printf("%d  ", aux->info);
    infixadoR(aux->dir);
}

void posfixadoR(No* aux) {
    if (aux == NULL) return;
    posfixadoR(aux->esq);
    posfixadoR(aux->dir);
    printf("%d  ", aux->info);
}

int contarR(No* aux) {
    if (aux == NULL) return 0;
    return contarR(aux->esq) + contarR(aux->dir) + 1;
}

void liberarR(No* aux) {
    if (aux == NULL) return;
    liberarR(aux->esq);
    liberarR(aux->dir);
    free(aux);
}

No* verificaExisteR(int valor, No* aux) {
    if (aux == NULL) return NULL;
    if (valor == aux->info) return aux;
    if (valor < aux->info) return verificaExisteR(valor, aux->esq);
    return verificaExisteR(valor, aux->dir);
}

// Funções públicas

void inicializar(ArvoreBinariaVLI* a) {
    a->raiz = NULL;
}

void inserirVli(ArvoreBinariaVLI* a, int valor) {
    a->raiz = inserirVliR(valor, a->raiz);
}

void prefixado(ArvoreBinariaVLI* a) {
    prefixadoR(a->raiz);
}

void infixado(ArvoreBinariaVLI* a) {
    infixadoR(a->raiz);
}

void posfixado(ArvoreBinariaVLI* a) {
    posfixadoR(a->raiz);
}

int contar(ArvoreBinariaVLI* a) {
    return contarR(a->raiz);
}

int alturaRaiz(ArvoreBinariaVLI* a) {
    if (a->raiz == NULL) return 0;
    return a->raiz->altura;
}

void liberar(ArvoreBinariaVLI* a) {
    liberarR(a->raiz);
    a->raiz = NULL;
}

No* verificaExiste(ArvoreBinariaVLI* a, int valor) {
    return verificaExisteR(valor, a->raiz);
}

// ------------------------------------------------

int main() {
    ArvoreBinariaVLI arvore;
    inicializar(&arvore);

    inserirVli(&arvore, 5);
    inserirVli(&arvore, 12);
    inserirVli(&arvore, 35);
    inserirVli(&arvore, 23);
    inserirVli(&arvore, 25);
    inserirVli(&arvore, 16);
    inserirVli(&arvore, 10);

    printf("\nContador: %d", contar(&arvore));
    No* no = verificaExiste(&arvore, 5);
    if (no != NULL)
        printf("\nAltura raiz: %d\n", no->altura);

    liberar(&arvore);
    while (1) {
        Sleep(1);
    }

    return 0;
}
