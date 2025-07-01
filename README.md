# ArquivosSO

Este projeto simula um sistema de arquivos simplificado, implementado em linguagem C, utilizando estruturas de diretórios, arquivos, permissões e controle de acesso.

## 📚 Objetivo

O projeto tem como foco demonstrar os conceitos de:
- Estrutura de diretórios (estilo árvore)
- Criação e manipulação de arquivos
- File Control Block (FCB)
- Controle de permissões com bitmask RWX
- Interface via linha de comando

## 🧱 Estrutura do Projeto
```bash
ArquivosSO/
├── src/
│ ├── main.c # Ponto de entrada do sistema
│ ├── shell.c # Interpretação de comandos do usuário
│ ├── filesystem.c # Lógica para arquivos e diretórios
│ ├── filesystem.h # Estruturas e protótipos principais
│ └── utils.h # Constantes e tipos auxiliares
```

## ⚙️ Como compilar e executar

**No terminal (WSL/Linux):**

```bash
cd seu/caminho/diretorio/ArquivosSO
make
./ArquivosSO
```

## 📄 Sobre o FCB (File Control Block)

O FCB é representado no código pela struct Arquivo localizada em filesystem.h, ele armazena:

- Nome do arquivo
- Tipo (TEXTO, NUMERICO, etc)
- Tamanho
- Conteúdo
- Timestamps (criado, modificado, acessado)
- ID único (inode simulado)
- Dono do arquivo
- Permissões

Este conceito simula o inode usado em sistemas reais como NTFS.

## 🔐 Permissões RWX com Bitmask

As permissões são representadas com bits (bitmask), cada tipo de permissão vale:

| Permissão | Valor Binário | Decimal |
| --- | --- | --- |
| R | 100 | 4 |
| W | 010 | 2 |
| X | 001 | 1 |

Com isso, podemos criar combinações como 7 = RWX, 6 = RW-, 4 = R--, essas permissões são aplicadas para:

- Owner
- Group
- Others

Na struct `Permissao` em `utils.h`, temos os campos `owner`, `group` e `others`, armazenando essas permissões.
Elas são verificadas no código com bitwise AND, por exemplo:
`if (!(perm & READ))` → bloqueia leitura se o bit de leitura não estiver presente.

## 💻 Comandos disponíveis no projeto

| Comando | Função |
| --- | --- |
| `mkdir <nomeDiretório>` | Criar diretório |
| `cd <nomeDiretório>` | Entrar no diretório |
| `cd ..` | Voltar para o diretório pai |
| `ls` | Listar conteúdo do diretório |
| `touch <nomeArquivo>` | Criar arquivo |
| `echo <nomeArquivo> <texto>` | Escrever no arquivo |
| `cat <nomeArquivo>` | Ler conteúdo do arquivo |
| `chmod <numero> <nomeArquivo>` | Alterar permissões numéricas |
| `rm <nomeArquivo>` | Excluir arquivo |
| `su <nomeUsuario>` | Trocar usuário atual |
| `menu` | Exbir comandos disponíveis |
| `exit` | Encerrar programa |

## 📺 Apresentação em vídeo
[Vídeo da apresentação](https://youtu.be/Y4YobGuh9Ok)
