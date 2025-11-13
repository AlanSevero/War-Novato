#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ----------------- Structs e Prototipos ----------------- */

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Mapa */
Territorio* alocarMapa(int total);
void cadastrarMapa(Territorio* mapa, int total);
void mostrarMapa(const Territorio* mapa, int total);
void liberarMapa(Territorio* mapa);
void limparEntrada(void);

/* Combate */
void atacar(Territorio* atacante, Territorio* defensor);

/* ----------------- Implementação ----------------- */

Territorio* alocarMapa(int total)
{
    Territorio* mapa = (Territorio*)calloc((size_t)total, sizeof(Territorio));
    return mapa;
}

void cadastrarMapa(Territorio* mapa, int total)
{
    if (mapa == NULL) return;

    for (int i = 0; i < total; i++)
    {
        Territorio* t = mapa + i;
        printf("--- Cadastro Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        if (fgets(t->nome, sizeof(t->nome), stdin) == NULL) t->nome[0] = '\0';
        else {
            size_t ln = strlen(t->nome);
            if (ln > 0 && t->nome[ln-1] == '\n') t->nome[ln-1] = '\0';
        }

        printf("Cor do Exercito (ex: Azul, Verde): ");
        if (fgets(t->cor, sizeof(t->cor), stdin) == NULL) t->cor[0] = '\0';
        else {
            size_t ln = strlen(t->cor);
            if (ln > 0 && t->cor[ln-1] == '\n') t->cor[ln-1] = '\0';
        }

        printf("Numero de Tropas: ");
        while (scanf("%d", &t->tropas) != 1 || t->tropas < 0) {
            printf("Valor invalido. Digite um numero inteiro >= 0: ");
            limparEntrada();
        }
        limparEntrada();

        printf("\n");
    }
}

void mostrarMapa(const Territorio* mapa, int total)
{
    if (mapa == NULL) return;
    printf("\n=============================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL        \n");
    printf("=============================================\n\n");
    for (int i = 0; i < total; i++)
    {
        const Territorio* t = mapa + i;
        printf("%d . %s (Exercito, %s, %d)\n", i + 1, t->nome, t->cor, t->tropas);
    }
}

void liberarMapa(Territorio* mapa)
{
    if (mapa != NULL) free(mapa);
}

void limparEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Simula um unico ataque entre atacante e defensor.


void atacar(Territorio* atacante, Territorio* defensor)
{
    if (atacante == NULL || defensor == NULL) return;

    int dadoA = (rand() % 6) + 1; // 1..6
    int dadoD = (rand() % 6) + 1; // 1..6

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante (%s) rolou um dado e tirou: %d\n", atacante->nome, dadoA);
    printf("O defensor (%s) rolou o dado e tirou: %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD)
    {
        if (defensor->tropas > 0) defensor->tropas -= 1;
        if (defensor->tropas < 0) defensor->tropas = 0;
        printf("VITORIA DO ATAQUE! %s perdeu 1 tropa.\n", defensor->nome);

        if (defensor->tropas == 0)
        {
            int transferencia = atacante->tropas / 2;
            if (transferencia <= 0 && atacante->tropas > 0) transferencia = 1;

            /* atualiza cor do defensor */
            strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor)-1);
            defensor->cor[sizeof(defensor->cor)-1] = '\0';

            defensor->tropas = transferencia;
            atacante->tropas -= transferencia;
            if (atacante->tropas < 0) atacante->tropas = 0;

            printf(">>> %s foi conquistado pelo exercito %s!\n", defensor->nome, defensor->cor);
            printf(">>> Transferidos %d tropas do atacante para o territorio conquistado.\n", transferencia);
        }
    }
    else if (dadoA < dadoD)
    {
        if (atacante->tropas > 0) atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("DEFESA SUSTENTADA! %s perdeu 1 tropa.\n", atacante->nome);
    }
    else
    {
        printf("EMPATE! Ninguem perde tropas nesta rodada.\n");
    }
}

/* ----------------- main ----------------- */

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    int total = 0;

    if (argc >= 2) {
        int tmp = atoi(argv[1]);
        if (tmp > 0) total = tmp;
    }

    if (total <= 0) {
        printf("Quantos territorios deseja criar? ");
        if (scanf("%d", &total) != 1 || total <= 0) {
            printf("Numero invalido. Encerrando.\n");
            return 1;
        }
        limparEntrada();
    }

    Territorio *mapa = alocarMapa(total);
    if (!mapa) {
        fprintf(stderr, "Falha na alocacao de memoria.\n");
        return 1;
    }

    cadastrarMapa(mapa, total);

    printf("\nCadastro inicial concluido com sucesso!\n");

    while (1)
    {
        mostrarMapa(mapa, total);

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", total);

        int idxA;
        if (scanf("%d", &idxA) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparEntrada();
            continue;
        }
        limparEntrada();

        if (idxA == 0) {
            printf("Encerrando o jogo.\n");
            break;
        }
        if (idxA < 1 || idxA > total) {
            printf("Atacante invalido. Deve ser entre 1 e %d.\n\n", total);
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d): ", total);
        int idxD;
        if (scanf("%d", &idxD) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparEntrada();
            continue;
        }
        limparEntrada();

        if (idxD < 1 || idxD > total) {
            printf("Defensor invalido. Deve ser entre 1 e %d.\n\n", total);
            continue;
        }

        idxA -= 1;
        idxD -= 1;

        if (idxA == idxD) {
            printf("Atacante e defensor nao podem ser o mesmo territorio.\n\n");
            continue;
        }

        Territorio *at = mapa + idxA;
        Territorio *df = mapa + idxD;

        if (strcmp(at->cor, df->cor) == 0) {
            printf("Nao e possivel atacar um territorio do mesmo exercito (mesma cor).\n\n");
            continue;
        }

        if (at->tropas <= 0) {
            printf("Territorio atacante nao possui tropas suficientes para atacar.\n\n");
            continue;
        }

        printf("\n--- INICIO DO COMBATE ---\n");
        printf("Atacante: %s (Exercito %s, Tropas: %d)\n", at->nome, at->cor, at->tropas);
        printf("Defensor: %s (Exercito %s, Tropas: %d)\n\n", df->nome, df->cor, df->tropas);

        atacar(at, df);

        printf("\n--- ESTADO APOS ATAQUE ---\n");
        mostrarMapa(mapa, total);

        printf("\nPressione ENTER para continuar...");
        getchar(); /* pausa simples */
    }

    liberarMapa(mapa);
    printf("Memoria liberada. Ate mais!\n");
    return 0;
}