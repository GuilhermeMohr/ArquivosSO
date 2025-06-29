#include "fileSystem.h"

long Id = 0;
long NewId()
{
    Id++;
    return Id;
}

void Mkdir(Dir *diretorioAtual, const char *nome)
{
    if (!diretorioAtual)
        return;

    Dir *novoDir = (Dir *)malloc(sizeof(Dir));
    if (!novoDir)
    {
        perror("Erro ao alocar novo diretorio");
        return;
    }

    strcpy(novoDir->nome, nome);
    novoDir->arquivos = NULL;
    novoDir->filhos = NULL;
    novoDir->prox = diretorioAtual->filhos;
    novoDir->pai = diretorioAtual;

    diretorioAtual->filhos = novoDir;
}

void RemoveDir(Dir *diretorioAtual, const char *nome)
{
    if (!diretorioAtual || !nome)
        return;

    Dir *anterior = NULL;
    Dir *atual = diretorioAtual->filhos;

    while (atual)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            if (atual->filhos || atual->arquivos)
            {
                printf("Diretorio '%s' nao esta vazio.\n", nome);
                return;
            }

            if (anterior)
            {
                anterior->prox = atual->prox;
            }
            else
            {
                diretorioAtual->filhos = atual->prox;
            }

            free(atual);
            printf("Diretorio '%s' removido com sucesso.\n", nome);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Diretorio '%s' nao encontrado.\n", nome);
}

void Create(Fcb **lista, const char *nome, int tipo)
{
    if (!lista)
        return;

    Fcb *novoArquivo = (Fcb *)malloc(sizeof(Fcb));
    if (!novoArquivo)
    {
        perror("Erro ao alocar memoria para FCB");
        return;
    }
    strcpy(novoArquivo->nome, nome);
    novoArquivo->prox = NULL;
    novoArquivo->id = NewId();
    novoArquivo->tipo = tipo;
    novoArquivo->dataCriacao = time(NULL);
    novoArquivo->dataModificacao = novoArquivo->dataCriacao;
    novoArquivo->dataAcesso = novoArquivo->dataCriacao;
    novoArquivo->conteudo = NULL;
    if (!(*lista))
    {
        (*lista) = novoArquivo;
    }
    else
    {
        novoArquivo->prox = (*lista)->prox;
        (*lista)->prox = novoArquivo;
    }
}

void DeleteFile(Fcb **lista, const char *nome)
{
    if (!lista || !(*lista))
    {
        printf("Lista de arquivos vazia.\n");
        return;
    }

    Fcb *atual = *lista;
    Fcb *anterior = NULL;

    while (atual)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            if (anterior == NULL)
            {
                *lista = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            if (atual->conteudo) free(atual->conteudo);

            printf("Arquivo '%s' deletado com sucesso.\n", nome);
            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Arquivo '%s' nao encontrado.\n", nome);
}

void Ls(Dir *diretorioAtual)
{
    if (!diretorioAtual)
        return;

    Dir *atual = diretorioAtual->filhos;
    while (atual)
    {
        printf("%s  -- dir\n", atual->nome);
        atual = atual->prox;
    }

    Fcb *arquivoAtual = diretorioAtual->arquivos;
    while (arquivoAtual)
    {
        printf("%s  -- arquivo\n", arquivoAtual->nome);
        arquivoAtual = arquivoAtual->prox;
    }
}

Dir *CD(Dir *atual, const char *nome)
{
    Dir *aux = atual;
    if (strcmp(nome, "..") == 0)
    {
        if (aux->pai)
            return aux->pai;
        printf("Ja esta na raiz.\n");
        return atual;
    }

    if (strcmp(nome, "/") == 0)
    {
        while (aux->pai)
            aux = aux->pai;
        return aux;
    }

    Dir *filho = aux->filhos;
    while (filho)
    {
        if (strcmp(filho->nome, nome) == 0)
        {
            return filho;
        }
        filho = filho->prox;
    }

    printf("Diretorio '%s' nao encontrado.\n", nome);
    return atual;
}

void Pwd(Dir *atual)
{
    if (!atual)
        return;
    if (atual->pai)
    {
        Pwd(atual->pai);
        printf("/%s", atual->nome);
    }
    else
    {
        printf("/%s", atual->nome);
    }
}

void CopyFile(Fcb *lista, const char *nomeOrigem, const char *nomeDestino)
{
    if (!lista)
    {
        printf("Nenhum arquivo para copiar.\n");
        return;
    }

    Fcb *atual = lista;
    while (atual)
    {
        if (strcmp(atual->nome, nomeOrigem) == 0)
        {
            // Achou o arquivo original
            Fcb *copia = (Fcb *)malloc(sizeof(Fcb));
            if (!copia)
            {
                perror("Erro ao alocar memória para cópia");
                return;
            }

            strcpy(copia->nome, nomeDestino);
            copia->tamanho = atual->tamanho;
            copia->tipo = atual->tipo;
            copia->dataCriacao = time(NULL);
            copia->dataModificacao = copia->dataCriacao;
            copia->dataAcesso = copia->dataCriacao;
            copia->id = NewId();
            copia->permissao = atual->permissao;

            copia->prox = lista->prox;
            lista->prox = copia;

            printf("Arquivo '%s' copiado como '%s'.\n", nomeOrigem, nomeDestino);
            return;
        }

        atual = atual->prox;
    }

    printf("Arquivo '%s' não encontrado.\n", nomeOrigem);
}

void WriteFile(Fcb* lista, const char* nome, const char* conteudo) {
    while (lista) {
        if (strcmp(lista->nome, nome) == 0) {
            if (lista->conteudo) free(lista->conteudo);

            lista->conteudo = strdup(conteudo);
            lista->tamanho = strlen(conteudo);
            lista->dataModificacao = time(NULL);

            printf("Arquivo '%s' informacoes registradas.\n", nome);
            return;
        }
        lista = lista->prox;
    }
    printf("Arquivo '%s' nao encontrado.\n", nome);
}

void ReadFile(Fcb* lista, const char* nome) {
    while (lista) {
        if (strcmp(lista->nome, nome) == 0) {
            lista->dataAcesso = time(NULL);
            if (lista->conteudo) {
                printf("Conteudo de '%s':\n%s\n", nome, lista->conteudo);
            } else {
                printf("Arquivo '%s' esta vazio.\n", nome);
            }
            return;
        }
        lista = lista->prox;
    }
    printf("Arquivo '%s' nao encontrado.\n", nome);
}