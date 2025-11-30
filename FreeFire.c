#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;  // 1 a 5
} Item;

// Enumeração simples (compatível C antigo)
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} Criterio;

// ---------------- Funções --------------------

void adicionarItem(Item mochila[], int *n) {
    if (*n >= MAX) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    printf("\n--- Adicionar Item ---\n");

    printf("Nome: ");
    scanf(" %[^\n]", mochila[*n].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[*n].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*n].quantidade);

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &mochila[*n].prioridade);
    } while (mochila[*n].prioridade < 1 || mochila[*n].prioridade > 5);

    (*n)++;
    printf("\nItem adicionado!\n");
}

void listarItens(Item mochila[], int n) {
    int i;
    if (n == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    for (i = 0; i < n; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("Prioridade: %d\n", mochila[i].prioridade);
    }
}

int comparar(Item a, Item b, Criterio c) {
    if (c == ORDENAR_NOME)
        return strcmp(a.nome, b.nome);
    else if (c == ORDENAR_TIPO)
        return strcmp(a.tipo, b.tipo);
    else
        return a.prioridade - b.prioridade;
}

// Insertion Sort com contador
int ordenar(Item mochila[], int n, Criterio c) {
    int i, j;
    int comparacoes = 0;

    for (i = 1; i < n; i++) {
        Item chave = mochila[i];
        j = i - 1;

        while (j >= 0 && comparar(mochila[j], chave, c) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }

        if (j >= 0)
            comparacoes++;

        mochila[j + 1] = chave;
    }

    return comparacoes;
}

int buscaBinaria(Item mochila[], int n, char nome[]) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// ---------------- Main --------------------

int main() {
    Item mochila[MAX];
    int total = 0;
    int opcao;
    int ordenadoPorNome = 0;  // 0 = não, 1 = sim

    do {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Ordenar mochila\n");
        printf("4. Buscar item (Busca Binária)\n");
        printf("5. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            adicionarItem(mochila, &total);
            ordenadoPorNome = 0;
        }

        else if (opcao == 2) {
            listarItens(mochila, total);
        }

        else if (opcao == 3) {
            int escolha;
            int comp;

            if (total == 0) {
                printf("\nNão há itens para ordenar.\n");
                continue;
            }

            printf("\n--- Ordenar por ---\n");
            printf("1. Nome\n");
            printf("2. Tipo\n");
            printf("3. Prioridade\n");
            printf("Escolha: ");
            scanf("%d", &escolha);

            if (escolha < 1 || escolha > 3) {
                printf("\nOpção inválida!\n");
                continue;
            }

            comp = ordenar(mochila, total, (Criterio) escolha);

            printf("\nMochila ordenada!\n");
            printf("Comparações realizadas: %d\n", comp);

            if (escolha == ORDENAR_NOME)
                ordenadoPorNome = 1;
            else
                ordenadoPorNome = 0;
        }

        else if (opcao == 4) {
            char nomeBusca[50];
            int pos;

            if (!ordenadoPorNome) {
                printf("\nERRO: A mochila deve estar ordenada por NOME.\n");
                continue;
            }

            printf("\nNome do item: ");
            scanf(" %[^\n]", nomeBusca);

            pos = buscaBinaria(mochila, total, nomeBusca);

            if (pos >= 0) {
                printf("\nItem encontrado!\n");
                printf("Nome: %s\n", mochila[pos].nome);
                printf("Tipo: %s\n", mochila[pos].tipo);
                printf("Quantidade: %d\n", mochila[pos].quantidade);
                printf("Prioridade: %d\n", mochila[pos].prioridade);
            } else {
                printf("\nItem não encontrado.\n");
            }
        }

        else if (opcao != 5) {
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 5);

    printf("\nEncerrando...\n");
    return 0;
}
