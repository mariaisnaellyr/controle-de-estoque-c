#include <stdio.h>
#include <string.h>

int main() {
    int opcao, quantidade, qtd, encontrado;
    char nome[50], nomeArquivo[50], resposta;

    do {
        printf("\n==================================\n");
        printf("       Controle de Estoque\n");
        printf("==================================\n");
        printf("1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\n");
        printf("Opcao: ");

        while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
            printf("Opcao invalida! Tente novamente.\n");
            while (getchar() != '\n');
            printf("Opcao: ");
        }

        if (opcao == 1) {
            FILE *arquivo = fopen("inventory.txt", "a");
            printf("Digite o nome do item: ");
            scanf(" %[^\n]", nome);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            fprintf(arquivo, "%s\n%d\n", nome, quantidade);
            fclose(arquivo);
            printf("Item adicionado com sucesso!\n");
        }

        else if (opcao == 2) {
            FILE *arquivo = fopen("inventory.txt", "r");
            FILE *temporario = fopen("temp.txt", "w");
            printf("Digite o nome do item: ");
            scanf(" %[^\n]", nome);
            printf("Digite a quantidade a ser removida: ");
            scanf("%d", &quantidade);
            encontrado = 0;

            if (arquivo != NULL) {
                while (fscanf(arquivo, " %[^\n]", nomeArquivo) == 1) {
                    fscanf(arquivo, "%d", &qtd);
                    if (strcmp(nome, nomeArquivo) == 0) {
                        encontrado = 1;
                        if (quantidade > qtd) {
                            printf("Estoque insuficiente. Quantidade disponivel: %d\n", qtd);
                            fprintf(temporario, "%s\n%d\n", nomeArquivo, qtd);
                        }
                        else if (quantidade == qtd) {
                            printf("Item removido do estoque!\n");
                        }
                        else {
                            qtd = qtd - quantidade;
                            fprintf(temporario, "%s\n%d\n", nomeArquivo, qtd);
                            printf("Quantidade atualizada com sucesso!\n");
                        }
                    }
                    else {
                        fprintf(temporario, "%s\n%d\n", nomeArquivo, qtd);
                    }
                }
                fclose(arquivo);
            }

            fclose(temporario);
            if (encontrado == 0)
                printf("Item nao encontrado.\n");
            remove("inventory.txt");
            rename("temp.txt", "inventory.txt");
        }

        else if (opcao == 3) {
            FILE *arquivo = fopen("inventory.txt", "r");
            printf("\n=============================\n");
            printf("        Estoque Atual\n");
            printf("=============================\n");
            encontrado = 0;

            if (arquivo != NULL) {
                while (fscanf(arquivo, " %[^\n]", nomeArquivo) == 1) {
                    fscanf(arquivo, "%d", &qtd);
                    printf("Nome: %s\n", nomeArquivo);
                    printf("Quantidade: %d\n\n", qtd);
                    encontrado = 1;
                }
                fclose(arquivo);
            }
            if (encontrado == 0)
                printf("O estoque esta vazio.\n");
        }

        else if (opcao == 4) {
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
            return 0;
        }

        printf("\nDeseja realizar outra operacao? (s/n): ");
        scanf(" %c", &resposta);

    } while (resposta == 's' || resposta == 'S');

    printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
    return 0;
}
