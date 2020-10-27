#pragma once
 
const int M = 6, N = 6;
const char BLANK = ' ';
const char SHIP = 'S';
const char MISS = 'M';
const char HIT = 'H';
char board[M][N]; // 2d array with M rows and N columns
int numberOfHits;
int numberOfShots;

void generateBoard(char board[M][N]) 
{
	for (int i = 0; i < M; i++)	
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = BLANK;
		}
	}
}

void printBoard(char board[M][N]) 
{
	for (int i = M; i >= 0; i--)
	{
		std::cout << i << '|';
		for (int j = N; j >= 0; j--)
		{
			std::cout << board[i][j] << '|';
		}
		std::cout << "\n";
	}
	std::cout << " |A|B|C|D|E|F|\n\n";
}

//int letterToNumber(char letter) // only big letters
//{
//    return static_cast<int>(letter) - 65;
//}

void task2() 
{
	system("cls");
	generateBoard(board);
	printBoard(board);
	system("pause");
}