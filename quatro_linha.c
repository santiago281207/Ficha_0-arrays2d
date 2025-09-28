#define _CRT_SECURE_NO_WARNINGS
#define AC_RESET "\x1b[m"	//Resetar a cor
#define AC_GREEN "\x1b[32m"
#define AC_RED "\x1b[31m"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

void Clear(void);	//Limpar o buffer depois do primeiro input
void RobotPlay(char game[][7], int board[][7]);	//Jogada do computador
void GerarCampo(char game[][7], int board[][7]);	//Esvaziar o campo todo
void MostrarJogo(char game[][7],int board[][7]);	//Mostrar tabuleiro com formatcoes
int CheckInput(char input,int board[][7]);		//Verificar se o input do jogador é valido
int Y_verify(char input, int board[][7]);	//Verificar se existe espaço livre na coluna que o jogador escolheu
int CheckWin(char game[][7], int board[][7]);	//Verificar se alguem ganhou


int main()
{
	char game[6][7];	//Tabuleiro de simbolos
	int board[6][7];	//Tabuleiro com numeros jgoador 1 = 1 | jogador 2 = -1
	char input;	//Input do jogador
	int x_alvo = 0, y_alvo = 0;	//Coordenadas
	int ganhou = 0;	//Se alguem ganhou ou nao
	int turn = 0;	//Turnos dos jogadores
	

	GerarCampo(game, board);	//Esvaziar o campo todo e preencher tudo de espacos vazios

	while (ganhou == 0)
	{
		system("cls");	//Limpar consola
		MostrarJogo(game,board);
		if (turn == 0)
		{
			
			do
			{
				printf("Indique onde quer jogar: ");
				scanf("%c", &input);
				Clear();
				if (CheckInput(input, board) == 0)
				{
					puts("Invalido. Tente novamente.\n");
				}
			} while (CheckInput(input, board) == 0);

			x_alvo = toupper(input) - 'A';	//Verificar qual coluna foi escolhida
			y_alvo = Y_verify(input,board);	//Simular "gravidade" fazendo a peca ir sempre para o fim da coluna escolhida

			//Atribuir jogada a posicao espicifica
			board[y_alvo][x_alvo] = 1;	
			game[y_alvo][x_alvo] = 'O';
		}
		else if (turn == 1)	//Jogada do robo
		{
			RobotPlay(game, board);	
		}

		turn = !turn;	//Mudar de jogada
		ganhou = CheckWin(game, board);	//Verificar se alguem ganhou
	}
	MostrarJogo(game, board);

	if (ganhou == 1)
	{
		puts("Jogador 1 ganhou!");
	}
	else if (ganhou == 2)
	{
		puts("Jogador 2 ganhou!");
	}
	return 0;
	
}

void GerarCampo(char game[][7], int board[][7])
{
	int i = 0, j = 0;

	//Passar por todas as linhas e colunas do tabuleiro e preencher com espaco vazio
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			game[i][j] = '-';
			board[i][j] = 0;
		}
	}
}

void MostrarJogo(char game[][7],int board[][7])
{
	int i = 0, j = 0;
	int numeracao = 1;
	char letra = 'A';

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (board[i][j] == 1 && j != 6 && i != 6)	//Representar pecas verdes que nao estao na ultima coluna
			{
				printf("%s%c%s || ",AC_GREEN,game[i][j],AC_RESET);
			}
			else if (board[i][j] == 1 && j == 6 && i != 6)	//Pecas verdes na ultima coluna
			{
				printf("%s%c%s",AC_GREEN,game[i][j],AC_RESET);
			}
			else if (board[i][j] == -1 && j != 6 && i != 6)	//Pecas vermelhas que nao estao na ultima coluna(robo)
			{
				printf("%s%c%s || ",AC_RED, game[i][j], AC_RESET);
			}
			else if (board[j][i] == -1 && j == 6 && i != 6)	//Pecas vermelhas na ultima coluna (robo)
			{
				printf("%s%c%s", AC_RED, game[i][j], AC_RESET);
			}
			else if (board[i][j] == 0 && j != 6 && i != 6)	//Pecas sem cor que nao estao na ultima coluna
			{
				printf("%c || ", game[i][j]);
			}else if (board[i][j] == 0 && j == 6 && i != 6)	//Pecas sem cor que estao na ultima coluna
			{
				printf("%c", game[i][j]);
			}
			if (i == 6)	//Coordenadas X
			{
				printf("%c    ", letra++);
			}
		}
		printf("\n");
	}
}

int CheckInput(char input, int board[][7])
{
	int x_alvo = 0, y_alvo = 0, i = 0, cheio = 0;

   //Verificar se input e uma letra e se é valido em relacao a quantidade de coluans que existem
   if (isalpha(input) == 0 || toupper(input) > 'G')
   {
       return 0;
   }

   //Converter input (char) em o numero da coluna
   x_alvo = toupper(input) - 'A';	

   for (i = 0;board[i][x_alvo] != 0;i++)	//Ate encontrar um espaco vazio
   {
	   cheio++;	//Conta espacos que estao cheios
   }
   if (cheio == 6)	//Se nao existir nenhum espaco vazio
   {
	   return 0;	//Input nao e valido
   }
   return 1;	//Input e valido
}

int Y_verify(char input, int board[][7])
{
	//Esta funçao ira devolver sempre I pois quando é utilizada o input ja foi validado
	//Apenas coloquei o if para poder fazer uma decisao mais rapida sem precisar de passar por tudo

	int i = 0, y = 0;
	int x = toupper(input) - 'A';	//Converter input para numero correspondente a coordenada X 

	//Encontrar espaco vazio na coluna desejada
	for (i = 6;i >= 0;i--)	
	{
		y = board[i][x];	//Verificar se é um espaco livre no Y
		if (y == 0)
		{
			return i;	//Devolver coordenada do espaco livre
		}
	}
	return i;
}

void Clear(void) 
{
	int c;
	//Ler e descartar tudo do buffer até encontrar o '\n' ou o fim do ficheiro de buffer
	while ((c = getchar()) != '\n' && c != EOF);	
}

void RobotPlay(char game[][7], int board[][7])
{
	int i = 0, k = 0;
	int y = 0;

	//Verificar se o robo ja pode ganhar neste momento
	for (i = 0;i < 7;i++)
	{
		y = Y_verify('A' + i, board);	//Verificar se na coluna atual tem espaco vazio
		if (y >= 0)
		{
			board[y][i] = -1;	//Simular a jogada para ver se ganha
			if (CheckWin(game, board) == 2)	//Se ganhar
			{
				game[y][i] = 'O';	//Mudar simbolo
				return;
			}
			board[y][i] = 0;	//Desfazer a simulacao
		}
	}

	//Verificar se humano ja pode ganhar
	for (i = 0; i < 7;i++)
	{
		y = Y_verify('A' + i, board);
		board[y][i] = 1;	//Simular jogada do humano
		if (CheckWin(game, board) == 1)		//Verificar se humano ganha
		{	
			//	Defender contra a jogada
			board[y][i] = -1;
			game[y][i] = 'O';
			return;
		}
		board[y][i] = 0;	//Desfazer simulacao
	}

	//	Jogar no centro se houver espaco (Melhor sitio do tabuleiro)
	i = 3;
	y = Y_verify('A' + i, board);	//Verificar se existe espaco livre na coluna desejada

	if (y >= 0)	//Existe espaco
	{
		//Jogar no centro
		board[y][i] = -1;
		game[y][i] = 'O';
		return;
	}
	
	//Se nenhum das outras opcoes resultar jogar em outrs coluna valida qualquer
	for (i = 0;i < 7;i++)
	{
		y = Y_verify('A' + i, board);	//Encontrar espaco valido
		if (y >= 0)
		{
			//Jogar em qualquer espaco valido
			board[y][i] = -1;
			game[y][i] = 'O';
			return;
		}
	}
}

int CheckWin(char game[][7], int board[][7])
{
	int i = 0, k = 0;
	int soma = 0;

	//Linhas
	for (i = 5;i >= 0;i--)
	{
		for (k = 0;k <= 3;k++)
		{
			soma = board[i][k] + board[i][k + 1] + board[i][k + 2] + board[i][k + 3];
			if (soma == 4)
			{
				return 1;	//Jogador 1
			}
			else if (soma == -4)
			{
				return 2;	//Jogador 2
			}
		}
	}
	
	//Colunas 
	soma = 0;
	for (i = 5;i >= 3;i--)
	{
		for (k = 0;k < 6;k++)
		{
			soma = board[i][k] + board[i - 1][k] + board[i - 2][k] + board[i - 3][k];
			if (soma == 4)
			{
				return 1;	//Jogador 1
			}
			else if (soma == -4)
			{
				return 2;	//Jogador 2
			}
		}
	}

	//Diagonal direita - esquerda
	soma = 0;
	for (i = 5;i >= 3;i--)
	{
		for (k = 0;k <= 3;k++)
		{
			soma = board[i][k] + board[i - 1][k + 1] + board[i - 2][k + 2] + board[i - 3][k + 3];
			if (soma == 4)
			{
				return 1;	//Jogador 1
			}
			else if (soma == -4)
			{
				return 2;	//Jogador 2
			}
		}
	}

	//Diagonal esquerda - direita
	soma = 0;
	for (i = 0;i <= 3;i++)
	{
		for (k = 0;k <= 3;k++)
		{
			soma = board[i][k] + board[i + 1][k + 1] + board[i + 2][k + 2] + board[i + 3][k + 3];
			if (soma == 4)
			{
				return 1;	//Jogador 1
			}
			else if (soma == -4)
			{
				return 2;	//Jogador 2
			}
		}
	}
	return 0;	//Ninguem ganhou até agora
}
