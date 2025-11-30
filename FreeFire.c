#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

void adicionarItem(Item mochila[], int *n) {
    if (*n >= MAX) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    printf("\n--- Adicionar Item ---\n");
    
    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*n].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[*n].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*n].quantidade);

    (*n)++;

    printf("\nItem adicionado com sucesso!\n");
}

void listarItens(Item mochila[], int n) {
    if (n == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    for (int i = 0; i < n; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

void buscarItemPorNome(Item mochila[], int n) {
    if (n == 0) {
        printf("\nA mochila está vazia! Não há itens para buscar.\n");
        return;
    }

    char busca[50];
    int encontrado = 0;

    printf("\n--- Buscar Item por Nome ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", busca);

    for (int i = 0; i < n; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem \"%s\" não encontrado na mochila.\n", busca);
    }
}

int main() {
    Item mochila[MAX];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Buscar item por nome\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &total);
                break;
            case 2:
                listarItens(mochila, total);
                break;
            case 3:
                buscarItemPorNome(mochila, total);
                break;
            case 4:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}
