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
    char* nome;
    int tamanho;
    enum Tipo tipo;
    time_t dataCriacao;
    time_t dataModificacao;
    time_t dataAcesso;
    int id;
    int permissao;
} Fcb;

typedef struct DiretorioTopo {
    struct Fcb* arquivos;
    struct Diretorio* filhos;
} Dir;

typedef struct Diretorio {
    struct Fcb* arquivos;
    struct Diretorio* filhos;
    struct Diretorio* prox;
} Dir;

#endif