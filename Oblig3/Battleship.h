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

void shoot(char board[M][N], char playerBoard[M][N], int &shots, int &hits) 
{
	std::string input{ "" };

	std::cout << "\nWhere would you like to shoot? (Example: B2)\nInput: ";
	std::cin >> input;

	int tempR = input.at(1) - 48;
	int tempC = letterToNumber(input.at(0));

	if (board[tempR][tempC] == SHIP) {
		playerBoard[tempR][tempC] = HIT;
		hits++;
	}
	else {
		playerBoard[tempR][tempC] = MISS;
	}

	shots++;;
}

int randomRow()		//M
{
	return rand() % M + 1;
}

int randomColumn()		//N
{
	return rand() % N + 1;
}

void makeBoard3(int numberOfShips, char board[M][N]) 
{
	int dir{ 9 };	//0 = horizontal, 1 = vertical
	int tempR{ 0 };
	int tempC{ 0 };

	for (int i = 0; i < numberOfShips; i++)
	{
		bool placed = false;

		while (!placed) {
			dir = rand() % 2 + 1;
			tempR = randomRow();
			tempC = randomColumn();
			switch (dir)
			{
			case 1:
				if (tempR > (M - 3)) {
					tempR = (M - 3);
				}
				if (board[tempR][tempC] != SHIP && board[tempR + 1][tempC] != SHIP && board[tempR + 2][tempC] != SHIP)
				{
					for (int j = 0; j < 3; j++)
					{
						board[tempR + j][tempC] = SHIP;
						
					}
					placed = true;
				}

				break;
			case 2:
				if (tempC > (N - 3)) {
					tempC = (N - 3);
				}
				if (board[tempR][tempC] != SHIP && board[tempR][tempC + 1] != SHIP && board[tempR][tempC + 2] != SHIP)
				{
					for (int j = 0; j < 3; j++)
					{
						board[tempR][tempC + j] = SHIP;

					}
					placed = true;
				}
				break;
			}
		}
	}
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


void play() 
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int numberOfShips{ 3 };
	int numberOfHits{ 0 };
	int numberOfShots{ 0 };
	int totalShots{ 15 };
	char board[M][N]{};
	char playerBoard[M][N];

	makeEmptyBoard(board);
	makeEmptyBoard(playerBoard);
	//makeBoard(numberOfShips, board);
	makeBoard3(numberOfShips, board);

	while (true) {
		system("cls");
		printBoard(board);
		printBoard(playerBoard);

		std::cout << "\nShots: [" << numberOfShots << "]\tHits: [" << numberOfHits << "] \nShots left: [" << totalShots << "]";
		if (totalShots <= 0 || numberOfHits == numberOfShips) {
			break;
		}
		shoot(board, playerBoard, numberOfShots, numberOfHits);
		totalShots--;
		
	}
	std::cout << "\n\nGame Over!\n";
	system("pause");
}