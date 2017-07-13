//master
#ifndef	_MAIN_CPP_
#define	_MAIN_CPP_

#include "Define.h"

char undo_board[GRID_NUM][GRID_NUM];
char undo_board_know[GRID_NUM][GRID_NUM];
SPlayer undo_player[3];	

int main()
{
	char	msg[100];
	int		numTi = 0;
	int		x,y;

	InitGame();

	while(1)
	{
		Sleep(50);
		fflush(stdin);
		Sleep(50);
		fflush(stdout);
		scanf("%s",msg);

		if (strcmp(msg, "accept") == 0)
		{
			fflush(stdin);
			moveSucceed();
		}else if (strcmp(msg, "refuse") == 0)
		{
			fflush(stdin);
			moveFail();
			move();
		}else if (strcmp(msg, "move") == 0)
		{
			scanf("%s",msg); // Read "go"
			fflush(stdin);
			player[opponentColor].total++;
			move();
		}else if (strcmp(msg, "access") == 0) //己方提子
		{

			scanf("%s",msg); // Read "take"
			scanf("%d%s",&numTi, msg);
			fflush(stdin);
			player[opponentColor].total -= numTi;
			//SMove moveList[81];
			for(int i = 0 ; i < numTi ; i++)
			{
				// moveList[i].x = msg[2 * i] - 'A' + 1;
				// moveList[i].y = msg[2 * i + 1] - 'A' + 1;
				// board[moveList[i].x][moveList[i].y] = NOSTONE;
				char x = msg[2 * i] - 'A' + 1;
				char y = msg[2 * i + 1] - 'A' + 1;
				board[x][y] = NOSTONE;
			}
		}else if (strcmp(msg, "taked") == 0) //对方提子
		{
			scanf("%d%s",&numTi, msg);
			player[chessColor].total -= numTi;
			//SMove moveList[81] ;
			for(int i = 0 ; i < numTi ; i++)
			{
				// x = moveList[i].x = msg[2 * i] - 'A' + 1;
				// y = moveList[i].y = msg[2 * i + 1] - 'A' + 1;
				char x = msg[2 * i] - 'A' + 1;
				char y = msg[2 * i + 1] - 'A' + 1;
				board[x][y] = NOSTONE;
				
				//对所提的子的边界进行探测，如果是空，肯定是对方的子
				if (board[x-1][y] == NOSTONE)
				{
					board[x-1][y] = opponentColor;
					player[chessColor].know++;
				}
				if (board[x+1][y] == NOSTONE)
				{
					board[x+1][y] = opponentColor;
					player[chessColor].know++;
				}
				if (board[x][y-1] == NOSTONE)
				{
					board[x][y-1] = opponentColor;
					player[chessColor].know++;
				}
				if (board[x][y+1] == NOSTONE)
				{
					board[x][y+1] = opponentColor;
					player[chessColor].know++;
				}
			}
		}else if (strcmp(msg,"name?") == 0)
		{
			fflush(stdin);
			printf("name BIT\n");
			fflush(stdout);
		}else if (strcmp(msg,"end") == 0)
		{
			break;
		}else if (strcmp(msg,"quit") == 0)
		{
			break;
		}else if (strcmp(msg,"new") == 0)
		{
			InitGame();
			scanf("%s",msg);
			fflush(stdin);
			if (strcmp(msg,"black") == 0)
			{
				chessColor = BLACK;
				opponentColor = WHITE;
				SearchMove(&bestMove);
				printf("move %c%c\n",bestMove.x + 'A' - 1, bestMove.y + 'A' - 1);
				fflush(stdout);
			}else
			{
				chessColor = WHITE;
				opponentColor = BLACK;
			}
		}else
		{
			printf("Error Input!!!\n");
			PrintBoard();
		}
	}

	return 0;
}

void move()
{
	if (SearchMove(&bestMove))
	{
		printf("move %c%c\n",bestMove.x + 'A' - 1, bestMove.y + 'A' - 1);
	}
	else
	{
		printf("move pass\n");
	}
	fflush(stdout);
}

void moveSucceed()
{
	player[chessColor].total++;
	board[bestMove.x][bestMove.y] = chessColor;
	clean(bestMove, opponentColor, board);
}

void moveFail()
{
	player[chessColor].know++;
	board[bestMove.x][bestMove.y] = opponentColor;
	board_know[bestMove.x][bestMove.y]++;
}

void record()
{
	int i, j;
	for (i=1; i<10; i++){
		for (j=1; j<10; j++){
			undo_board[i][j] = board[i][j];
			undo_board_know[i][j] = board_know[i][j];
		}
	}
	for (i=0; i<3; i++){
		undo_player[i] = player[i];
	}
}

void Undo()
{
	int i, j;
	for (i=1; i<10; i++){
		for (j=1; j<10; j++){
			board[i][j] = undo_board[i][j];
			board_know[i][j] = undo_board_know[i][j];
		}
	}
	for (i=0; i<3; i++){
		player[i] = undo_player[i];
	}
}


void InitGame()
{
	memset(player, 0, sizeof(player));
	memset(board, 0, sizeof(board));
	memset(board_know, 0, sizeof(board_know));
	memset(&bestMove, 0, sizeof(bestMove));
//	memset(mark, 0, sizeof(mark));

	for (int i = 0 ; i < 11 ; i++)
	{
		board[i][0] = BORDER;
		board[0][i] = BORDER;
		board[i][10] = BORDER;
		board[10][i] = BORDER;
	}
};

void PrintBoard()
{
	printf("  ");
	for(int j = 1 ; j < 10 ; j++)
	{
		printf("%2d",j);
	}
	printf("\n");

	for(int i = 1; i < 10 ; i++)
	{
		printf("%2d",i);
		for(int j = 1 ; j < 10 ; j++)
		{
			switch(board[i][j])
			{
			case 0:
				printf(" -");
				break;
			case 1:
				printf(" *");
				break;
			case 2:
				printf(" O");
				break;
			}
		}
		printf("\n");
	}
	return ;
}

#endif