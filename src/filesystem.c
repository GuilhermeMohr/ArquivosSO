#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

Diretorio* raiz = NULL;
Diretorio* atual = NULL;
char usuarioAtual[MAX_NOME] = "admin";
int contador_id = 1;

void iniciar_sistema() {
    raiz = (Diretorio*) malloc(sizeof(Diretorio));
    strcpy(raiz->nome, "/");
    raiz->pai = NULL;
    raiz->subdirs = NULL;
    raiz->prox = NULL;
    raiz->arquivos = NULL;
    atual = raiz;
}

void mkdir(const char* nome) {
    Diretorio* novo = malloc(sizeof(Diretorio));
    strcpy(novo->nome, nome);
    novo->pai = atual;
    novo->subdirs = NULL;
    novo->arquivos = NULL;
    novo->prox = atual->subdirs;
    atual->subdirs = novo;
}

void cd(const char* nome) {
    if (strcmp(nome, "..") == 0 && atual->pai != NULL) {
        atual = atual->pai;
        return;
    }
    Diretorio* temp = atual->subdirs;
    while (temp) {
        if (strcmp(temp->nome, nome) == 0) {
            atual = temp;
            return;
        }
        temp = temp->prox;
    }
    printf("Diretório não encontrado!\n");
}

void ls() {
    Diretorio* d = atual->subdirs;
    while (d) {
        printf("[DIR] %s\n", d->nome);
        d = d->prox;
    }
    Arquivo* a = atual->arquivos;
    while (a) {
        printf("[ARQ] %s (%s)\n", a->nome, a->dono);
        a = a->prox;
    }
}

void touch(const char* nome) {
    Arquivo* novo = malloc(sizeof(Arquivo));
    strcpy(novo->nome, nome);
    novo->id = contador_id++;
    novo->tipo = TEXTO;
    novo->conteudo[0] = '\0';
    novo->tamanho = 0;
    novo->criado = novo->modificado = novo->acessado = time(NULL);
    novo->permissao.owner = 7;
    novo->permissao.group = 5;
    novo->permissao.others = 5;
    strcpy(novo->dono, usuarioAtual);
    novo->prox = atual->arquivos;
    atual->arquivos = novo;
}

void cat(const char* nome) {
    Arquivo* a = atual->arquivos;
    while (a) {
        if (strcmp(a->nome, nome) == 0) {
            int perm = (strcmp(usuarioAtual, a->dono) == 0) ? a->permissao.owner : a->permissao.others;
            if (!(perm & READ)) {
                printf("Permissão negada para leitura.\n");
                return;
            }
            printf("%s\n", a->conteudo);
            return;
        }
        a = a->prox;
    }
    printf("Arquivo não encontrado!\n");
}

void echo(const char* nome, const char* conteudo) {
    Arquivo* a = atual->arquivos;
    while (a) {
        if (strcmp(a->nome, nome) == 0) {
            int perm = (strcmp(usuarioAtual, a->dono) == 0) ? a->permissao.owner : a->permissao.others;
            if (!(perm & WRITE)) {
                printf("Permissão negada para escrita.\n");
                return;
            }
            strncpy(a->conteudo, conteudo, MAX_CONTEUDO);
            a->conteudo[MAX_CONTEUDO - 1] = '\0';
            a->tamanho = strlen(a->conteudo);
            a->modificado = time(NULL);
            return;
        }
        a = a->prox;
    }
    printf("Arquivo não encontrado!\n");
}

void chmod(const char* nome, int valor) {
    Arquivo* a = atual->arquivos;
    while (a) {
        if (strcmp(a->nome, nome) == 0) {
            a->permissao.owner = (valor / 100) % 10;
            a->permissao.group = (valor / 10) % 10;
            a->permissao.others = valor % 10;
            return;
        }
        a = a->prox;
    }
    printf("Arquivo não encontrado!\n");
}

void rm(const char* nome) {
    Arquivo **prev = &atual->arquivos;
    Arquivo *a = atual->arquivos;
    while (a) {
        if (strcmp(a->nome, nome) == 0) {
            int perm = (strcmp(usuarioAtual, a->dono) == 0) ? a->permissao.owner : a->permissao.others;
            if (!(perm & WRITE)) {
                printf("Permissão negada para exclusão.\n");
                return;
            }
            *prev = a->prox;
            free(a);
            return;
        }
        prev = &a->prox;
        a = a->prox;
    }
    printf("Arquivo não encontrado!\n");
}