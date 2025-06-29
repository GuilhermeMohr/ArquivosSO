#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileSystem.c"

#define MAX_CMD 1024

int main()
{
    char input[MAX_CMD];

    Dir *diretorioAtual = (Dir *)malloc(sizeof(Dir));
    strcpy(diretorioAtual->nome, "Topo");
    diretorioAtual->arquivos = NULL;
    diretorioAtual->filhos = NULL;
    diretorioAtual->prox = NULL;
    diretorioAtual->pai = NULL;

    printf("Mini Shell de Arquivos (digite 'exit' para sair)\n");

    while (1)
    {
        printf(">> ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        char *cmd = strtok(input, " \n");
        if (!cmd)
            continue;

        if (strcmp(cmd, "create") == 0)
        {
            char *filename = strtok(NULL, " \n");
            Create(&diretorioAtual->arquivos, filename, 0);
        }
        else if (strcmp(cmd, "write") == 0)
        {
            char *filename = strtok(NULL, " \n");
            char *content = strtok(NULL, "\n");
            if (filename && content)
            {
                WriteFile(diretorioAtual->arquivos, filename, content);
            }
        }
        else if (strcmp(cmd, "read") == 0)
        {
            char *filename = strtok(NULL, " \n");
            if (filename)
            {
                ReadFile(diretorioAtual->arquivos, filename);
            }
        }

        // } else if (strcmp(cmd, "seek") == 0) {
        //     char* filename = strtok(NULL, " \n");
        //     char* pos = strtok(NULL, " \n");
        //     seek_file(filename, atol(pos));

        else if (strcmp(cmd, "delete") == 0)
        {
            char *filename = strtok(NULL, " \n");
            if (filename)
            {
                DeleteFile(&diretorioAtual->arquivos, filename);
            }

            // } else if (strcmp(cmd, "truncate") == 0) {
            //     char* filename = strtok(NULL, " \n");
            //     char* size = strtok(NULL, " \n");
            //     truncate_file(filename, atol(size));
        }
        else if (strcmp(cmd, "mkdir") == 0)
        {
            char *dirname = strtok(NULL, " \n");
            Mkdir(diretorioAtual, dirname);
        }
        else if (strcmp(cmd, "rmdir") == 0)
        {
            char *dirname = strtok(NULL, " \n");
            if (dirname)
            {
                RemoveDir(diretorioAtual, dirname);
            }
        }
        else if (strcmp(cmd, "cp") == 0)
        {
            char *origem = strtok(NULL, " \n");
            char *destino = strtok(NULL, " \n");
            if (origem && destino)
            {
                CopyFile(diretorioAtual->arquivos, origem, destino);
            }
        }
        else if (strcmp(cmd, "ls") == 0)
        {
            Ls(diretorioAtual);
        }
        else if (strcmp(cmd, "cd") == 0)
        {
            char *dirname = strtok(NULL, " \n");
            if (dirname)
            {
                diretorioAtual = CD(diretorioAtual, dirname);
            }
        }
        else if (strcmp(cmd, "pwd") == 0)
        {
            Pwd(diretorioAtual);
            printf("\n");
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Comando desconhecido: %s\n", cmd);
        }
    }

    return 0;
}
