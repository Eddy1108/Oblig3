#pragma once
#include <time.h>
#include <cstdlib>

const int M = 6, N = 6;
const char BLANK = ' ';
const char SHIP = 'S';
const char MISS = 'M';
const char HIT = 'H';

int letterToNumber(char letter) // only big letters
{
	return (static_cast<int>(letter) - 64);
}

void shoot(char board[M][N]) 
{
	std::string input{ "" };

	std::cout << "\nWhere would you like to shoot? (Example: B2)\nInput: ";
	std::cin >> input;

	board[input.at(1) - 48][letterToNumber(input.at(0))] = MISS;
	
	//if(board[input.at(1)][letterToNumber(input.at(0))])

	
}

int randomRow()		//M
{
	return rand() % 6 + 1;
}

int randomColumn()		//N
{
	return rand() % 6 + 1;
}

void makeBoard(int numberOfShips, char board[M][N])
{
	int tempR;
	int tempC;

	for (int i = 0; i < numberOfShips; i++)
	{
		while (true)	//Make sure the ship is placed
		{		
			tempR = randomRow();
			tempC = randomColumn();
			if (board[tempR][tempC] == BLANK) {
				board[tempR][tempC] = SHIP;
				break;
			}
		}
	}
}

void makeEmptyBoard(char board[M][N]) 
{
	for (int i = 0; i < M; i++)	
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = BLANK;
		}
	}
}

void writeLetters() 
{
	std::cout << " -------------\n |A|B|C|D|E|F|\n\n";
}

void printBoard(char board[M][N]) 
{
	for (int i = M; i >= 1; i--)
	{
		std::cout << i << '|';
		for (int j = 1; j <= N; j++)
		{
			std::cout << board[i][j] << '|';
		}
		std::cout << "\n";
	}
	writeLetters();
}


void task2() 
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int numberOfHits;
	int numberOfShots;
	char board[M][N]{}; // 2d array with M rows and N columns
	makeEmptyBoard(board);
	makeBoard(6, board);

	while (true) {
		system("cls");

		printBoard(board);
		shoot(board);
		//system("pause");
	}
}