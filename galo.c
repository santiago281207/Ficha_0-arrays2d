#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int CheckInput(int tab[][4], int x, int y);
int GanhouCheck(int tab[][4], int x, int y);
int EmpateCheck(int tab[][4]);
void GerarCampo(int tabuleiro[][4]);
void MostrarCampo(int tab[][4]);
void PrintChar(int valor, int col);

int main() {
    int tab[4][4];
    int ganhou = 0;
    int jogada = 1;
    int x = 0, y = 0;

    GerarCampo(tab);

    while (ganhou == 0) {
        system("cls"); 
        MostrarCampo(tab);

        do {
            printf("Indique as coordenadas (x,y): ");
            scanf("%d %d", &x, &y);
            if (CheckInput(tab, x - 1, y - 1) == 0) {
                puts("Invalido.");
            }
        } while (CheckInput(tab, x - 1, y - 1) == 0);

        x--;
        y--;

        if (jogada == 1)
            tab[y][x] = 1; // Cruz
        else
            tab[y][x] = -1; // Bola

        jogada = !jogada;

        ganhou = GanhouCheck(tab, x, y);
        if (ganhou == 0) {
            ganhou = EmpateCheck(tab); 
        }
    }

    MostrarCampo(tab);

    if (ganhou == -1)
        puts("Empate.");
    else if (ganhou == 1)
        puts("Cruzes ganharam.");
    else if (ganhou == 2)
        puts("Bolas ganharam.");

    return 0;
}

void GerarCampo(int tabuleiro[][4]) {
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            tabuleiro[i][j] = 0;
}

void MostrarCampo(int tab[][4]) {
    int i, j;
    int numX = 1, numY = 1;

    for (i = 0; i <= 4; i++) {
        if (i < 4)
            printf("%d ", numY++);
        else
            printf("  ");

        for (j = 0; j < 4; j++) {
            if (i < 4)
                PrintChar(tab[i][j], j);
            else
                printf("%d   ", numX++);
        }
        puts("");
    }
}

void PrintChar(int valor, int col) {
    if (col < 3) {
        switch (valor) {
        case 1: printf("X | "); break;
        case -1: printf("O | "); break;
        case 0: printf("- | "); break;
        }
    } else {
        switch (valor) {
        case 1: printf("X"); break;
        case -1: printf("O"); break;
        case 0: printf("-"); break;
        }
    }
}

int CheckInput(int tab[][4], int x, int y) {
    if (x < 0 || x >= 4 || y < 0 || y >= 4)
        return 0;
    if (tab[y][x] != 0)
        return 0;
    return 1;
}

int GanhouCheck(int tab[][4], int x, int y) {
    int soma, i;

    // Linha
    soma = 0;
    for (i = 0; i < 4; i++)
        soma += tab[y][i];
    if (soma == 4) return 1;
    if (soma == -4) return 2;

    // Coluna
    soma = 0;
    for (i = 0; i < 4; i++)
        soma += tab[i][x];
    if (soma == 4) return 1;
    if (soma == -4) return 2;

    // Diagonal principal
    if (x == y) {
        soma = 0;
        for (i = 0; i < 4; i++)
            soma += tab[i][i];
        if (soma == 4) return 1;
        if (soma == -4) return 2;
    }

    // Diagonal secundária
    if (x + y == 3) {
        soma = 0;
        for (i = 0; i < 4; i++)
            soma += tab[i][3 - i];
        if (soma == 4) return 1;
        if (soma == -4) return 2;
    }

    return 0;
}

int EmpateCheck(int tab[][4]) {
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (tab[i][j] == 0)
                return 0;
    return -1;
}
