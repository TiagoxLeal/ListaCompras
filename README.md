# Lista de Compras

Este é um programa simples de linha de comando em C para gerenciar uma lista de compras usando um banco de dados SQLite.

## Funcionalidades

- Adicionar itens à lista de compras.
- Exibir todos os itens da lista de compras.
- Armazenar itens e suas quantidades em um banco de dados SQLite.

## Pré-requisitos

- **C Compiler**: Certifique-se de ter um compilador de C instalado. Por exemplo, `gcc`.
- **SQLite3**: Instale a biblioteca de desenvolvimento SQLite3.

### Instalação do SQLite3

**Para Ubuntu/Debian:**
```bash
$ sudo apt-get update
$ sudo apt-get install libsqlite3-dev
```

**Para Fedora:**
```bash
$ sudo dnf install sqlite-devel
```

### Compilação e execução

**Clone o repositório para sua máquina local:**

```bash
$ git clone https://github.com/seu-usuario/lista-de-compras.git
$ cd lista-de-compras
```

**Compile o código usando gcc:**
```bash
$ gcc -o lista_compras lista_compras.c -lsqlite3
```

**Execute o programa:**
```bash
$ ./lista_compras
```
