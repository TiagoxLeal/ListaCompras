#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Definir o número máximo de itens e o tamanho máximo do nome do item
#define TAM_MAX_NOME 50

// Estrutura para um item da lista de compras
typedef struct {
    char nome[TAM_MAX_NOME];
    int quantidade;
} ItemCompras;

// Protótipos de funções
int conectarBanco(sqlite3 **db);
void criarTabela(sqlite3 *db);
void adicionarItem(sqlite3 *db);
void exibirLista(sqlite3 *db);

int main() {
    sqlite3 *db;
    int opcao;

    // Conectar ao banco de dados SQLite
    if (conectarBanco(&db) != SQLITE_OK) {
        return 1;
    }

    // Criar tabela se não existir
    criarTabela(db);

    while (1) {
        printf("\nMenu da Lista de Compras:\n");
        printf("1. Adicionar Item\n");
        printf("2. Exibir Lista\n");
        printf("3. Sair\n");
        printf("Digite sua opção (1-3): ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(db);
                break;
            case 2:
                exibirLista(db);
                break;
            case 3:
                printf("Saindo...\n");
                sqlite3_close(db); // Fechar o banco de dados antes de sair
                return 0;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    }

    return 0;
}

// Função para conectar ao banco de dados SQLite
int conectarBanco(sqlite3 **db) {
    int rc = sqlite3_open("lista_compras.db", db);
    if (rc != SQLITE_OK) {
        printf("Erro ao conectar ao banco de dados: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return SQLITE_OK;
}

// Função para criar a tabela no banco de dados
void criarTabela(sqlite3 *db) {
    char *erro;
    const char *sql = "CREATE TABLE IF NOT EXISTS Compras ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nome TEXT NOT NULL, "
                      "quantidade INTEGER NOT NULL);";

    int rc = sqlite3_exec(db, sql, 0, 0, &erro);
    if (rc != SQLITE_OK) {
        printf("Erro ao criar tabela: %s\n", erro);
        sqlite3_free(erro);
    }
}

// Função para adicionar um item ao banco de dados
void adicionarItem(sqlite3 *db) {
    char nome[TAM_MAX_NOME];
    int quantidade;
    char *erro;
    char sql[200];

    printf("Digite o nome do item: ");
    scanf(" %[^\n]%*c", nome); // Lê o nome com espaços
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    // Inserir item no banco de dados
    snprintf(sql, sizeof(sql), "INSERT INTO Compras (nome, quantidade) VALUES ('%s', %d);", nome, quantidade);

    int rc = sqlite3_exec(db, sql, 0, 0, &erro);
    if (rc != SQLITE_OK) {
        printf("Erro ao adicionar item: %s\n", erro);
        sqlite3_free(erro);
    } else {
        printf("Item adicionado com sucesso!\n");
    }
}

// Função para exibir todos os itens da tabela do banco de dados
void exibirLista(sqlite3 *db) {
    const char *sql = "SELECT id, nome, quantidade FROM Compras;";
    sqlite3_stmt *stmt;

    // Preparar a consulta para execução
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\nLista de Compras:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        int quantidade = sqlite3_column_int(stmt, 2);

        printf("%d. %s - Quantidade: %d\n", id, nome, quantidade);
    }

    // Finalizar a consulta
    sqlite3_finalize(stmt);
}
