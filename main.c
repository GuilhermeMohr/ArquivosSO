#include "ArvoreVLI.h"

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
