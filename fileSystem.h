#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Tipo {
    NUMERICO,
    CARACTERE,
    BINARIO,
    PROGRAMA
};

typedef struct Fcb {
    char nome[100];
    int tamanho;
    enum Tipo tipo;
    time_t dataCriacao;
    time_t dataModificacao;
    time_t dataAcesso;
    int id;
    int permissao;
    char* conteudo;
    struct Fcb* prox;
} Fcb;

typedef struct Diretorio {
    char nome[100];
    struct Fcb* arquivos;
    struct Diretorio* filhos;
    struct Diretorio* prox;
    struct Diretorio* pai;
} Dir;

#endif