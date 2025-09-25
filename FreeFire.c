#include <stdio.h>
#include <string.h>

// Define a estrutura para um item do inventário
struct Item {
    char nome[10];
    char tipo[10];
    int quantidade;
};

// Define o tamanho máximo do inventário
#define CAPACIDADE 10

// Protótipos das funções
void adicionarItem(struct Item inventario[], int *contador);
void removerItem(struct Item inventario[], int *contador);
void listarItens(struct Item inventario[], int contador);

int main() {
    struct Item inventario[CAPACIDADE];
    int contador = 0; // Conta o número de itens no inventário
    int escolha;

    // Menu principal
    do {
        printf("\n--- Inventário Básico ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer de entrada

        switch (escolha) {
            case 1:
                adicionarItem(inventario, &contador);
                break;
            case 2:
                removerItem(inventario, &contador);
                break;
            case 3:
                listarItens(inventario, contador);
                break;
            case 4:
                printf("Saindo do programa. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}

// Função para adicionar um novo item ao inventário
void adicionarItem(struct Item inventario[], int *contador) {
    if (*contador >= CAPACIDADE) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome: ");
    fgets(inventario[*contador].nome, 50, stdin);
    inventario[*contador].nome[strcspn(inventario[*contador].nome, "\n")] = 0; // Remove a quebra de linha

    printf("Tipo: ");
    fgets(inventario[*contador].tipo, 50, stdin);
    inventario[*contador].tipo[strcspn(inventario[*contador].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &inventario[*contador].quantidade);
    getchar();

    (*contador)++;
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(struct Item inventario[], int *contador) {
    if (*contador == 0) {
        printf("O inventário está vazio. Não há itens para remover.\n");
        return;
    }

    char nomeRemover[50];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, 50, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            // Move os itens seguintes para preencher o espaço
            for (int j = i; j < *contador - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            (*contador)--;
            encontrado = 1;
            printf("Item '%s' removido com sucesso.\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' não encontrado no inventário.\n", nomeRemover);
    }
}

// Função para listar todos os itens do inventário
void listarItens(struct Item inventario[], int contador) {
    if (contador == 0) {
        printf("\nO inventário está vazio.\n");
        return;
    }

    printf("\n--- Itens do Inventário ---\n");
    printf("%-20s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("%-20s %-20s %-10d\n", inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
    printf("--------------------------------------------------\n");
}