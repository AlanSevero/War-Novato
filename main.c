#include <stdio.h>
#include <string.h>

// struct com o tipo de dados
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main()
{
    // lista de struct
    Territorio territorios[5];

    // repetição quantidade territorios
    for (int i = 0; i < 5; i++)
    {
        printf("--- Cadastro Territorio %d ---\n", i + 1);

        // colocar nome territorio
        printf("Nome do Territorio: ");
        scanf(" %[^\n]", territorios[i].nome);

        // cor exercito
        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf(" %[^\n]", territorios[i].cor);

        // quantidade tropas
        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); 
    }
    printf("\nCadastro inicial concluido com sucesso!\n");

    printf("=============================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL        \n");
    printf("=============================================\n");

    // saida struct
    for (int i = 0; i < 5; i++)
    {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  - Nome: %s\n", territorios[i].nome);
        printf("  - Dominado por: Exercito %s\n", territorios[i].cor);
        printf("  - Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------\n");
    }

    return 0;
}
