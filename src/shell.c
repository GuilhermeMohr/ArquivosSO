#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem.h"

void loop_comandos() {
    char comando[256];
    char arg1[128], arg2[128];
    int valor;
    char nomeArquivo[128];

    while (1) {
        printf("%s@mini_fs:%s$ ", usuarioAtual, atual->nome);
        fgets(comando, 256, stdin);
        comando[strcspn(comando, "\n")] = '\0';

        if (strncmp(comando, "exit", 4) == 0) break;
        else if (sscanf(comando, "mkdir %s", arg1) == 1) mkdir(arg1);
        else if (sscanf(comando, "cd %s", arg1) == 1) cd(arg1);
        else if (strcmp(comando, "ls") == 0) ls();
        else if (sscanf(comando, "touch %s", arg1) == 1) touch(arg1);
        else if (sscanf(comando, "cat %s", arg1) == 1) cat(arg1);
        else if (sscanf(comando, "echo %s %[^\n]", arg1, arg2) == 2) echo(arg1, arg2);
        else if (sscanf(comando, "chmod %d %s", &valor, nomeArquivo) == 2) chmod(nomeArquivo, valor);
        else if (sscanf(comando, "rm %s", arg1) == 1) rm(arg1);
        else if (sscanf(comando, "su %s", arg1) == 1) strcpy(usuarioAtual, arg1);
        else printf("Comando inválido!\n");
    }
}
