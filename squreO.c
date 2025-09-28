#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int EntreAB(int x, int min, int max);

int main()
{
	int table[9][9];
	int solucao[10][10];
	int circulos = 0, win = 0;
	int valid = 0;
	int i = 0, j = 0, k = 0;
	int n = 0;

	//Ler dimensao
	do
	{
		printf("Indique a dimensao: ");
		scanf("%d", &n);
		if (EntreAB(n, 3, 8) == 0)
		{
			puts("Invalido.");
		}
	} while (EntreAB(n,3,8) == 0);

	//Ler tabuleiro principal
	puts("Indique tabuleiro:");
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
		{
			do
			{
				scanf("%d", &valid);
				if (EntreAB(valid, 1, 4) == 0)
				{
					puts("Invalido.");
				}
			} while (EntreAB(valid, 1, 4) == 0);
			table[i][j] = valid;
		}
	}
	circulos = (n + 1) * (n + 1);

	//Solucao do tabuleiro
	puts("Indique a sua solucao: ");
	for (i = 0;i < n + 1;i++)
	{
		for (j = 0;j < n+1;j++)
		{
			do
			{
				scanf("%d", &valid);
				if (EntreAB(valid, 0, 1) == 0)
				{
					puts("Apenas valores 1 e 0");
				}
			} while (EntreAB(valid,0,1) == 0);
			solucao[i][j] = valid;
		}
	}
	
	//Verificar a solucao

	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
		{
			k = solucao[i][j] + solucao[i + 1][j] + solucao[i][j + 1] + solucao[i + 1][j + 1];
			if (k != table[i][j])
			{
				win = -1;
			}
		}
	}
	if (win == -1)
	{
		puts("Solucao está incorreta");
	}
	else {
		puts("Solucao esta correta.");
	}

	return 0;
}

int EntreAB(int x, int min, int max)
{
	return x >= min && x <= max;
}