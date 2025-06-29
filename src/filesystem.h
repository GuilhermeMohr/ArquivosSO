#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "utils.h"

#include <stddef.h>
#include <time.h>

#define MAX_NOME 100
#define MAX_CONTEUDO 1024

// File Control Block
typedef struct Arquivo {
    char nome[MAX_NOME];
    int id;
    TipoArquivo tipo;
    char conteudo[MAX_CONTEUDO];
    size_t tamanho;
    time_t criado;
    time_t modificado;
    time_t acessado;
    Permissao permissao;
    char dono[MAX_NOME];
    struct Arquivo* prox;
} Arquivo;

typedef struct Diretorio {
    char nome[MAX_NOME];
    struct Diretorio* pai;
    struct Diretorio* subdirs;
    struct Diretorio* prox;
    Arquivo* arquivos;
} Diretorio;

extern Diretorio* raiz;
extern Diretorio* atual;
extern char usuarioAtual[MAX_NOME];

void iniciar_sistema();
void mkdir(const char* nome);
void cd(const char* nome);
void ls();
void touch(const char* nome);
void cat(const char* nome);
void echo(const char* nome, const char* conteudo);
void chmod(const char* nome, int valor);
void rm(const char* nome);

#endif