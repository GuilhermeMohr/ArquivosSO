#define READ  4
#define WRITE 2
#define EXEC  1

typedef enum { NUMERICO, TEXTO, BINARIO, PROGRAMA } TipoArquivo;

typedef struct Permissao {
    int owner;
    int group;
    int others;
} Permissao;