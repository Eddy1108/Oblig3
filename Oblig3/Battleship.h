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

void AI(char board[M][N], int &hits)
{
	while (true) 
	{
		int tempR = randomRow();
		int tempC = randomColumn();
		if (board[tempR][tempC] == SHIP) {
			board[tempR][tempC] = HIT;
			hits++;
			break;
		}
		else if (board[tempR][tempC] == BLANK) {
			board[tempR][tempC] = MISS;
			break;
		}
	}
}

void makeBoard3(int numberOfShips, char board[M][N]) 
{
	int dir{ 0 };	//1 = horizontal, 2 = vertical
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
	for (int i = 0; i < M + 1; i++)
	{
		std::cout << "--";
	}
	std::cout << std::endl << " ";
	for (int i = 0; i < M; i++)
	{
		std::cout << '|' << (char)('A' + i);
	}
	std::cout << "|\n\n";
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
	int totalShots{ (int)((M * N) * 0.75) };
	int AIhits{ 0 };
	char board[M][N]{};
	char playerBoard[M][N];
	char AIboard[M][N];

	makeEmptyBoard(board);
	makeEmptyBoard(AIboard);
	makeEmptyBoard(playerBoard);
	
	//makeBoard(numberOfShips, board);		////single unit ships
	makeBoard3(numberOfShips, board);
	makeBoard3(numberOfShips, AIboard);

	while (true) {
		system("cls");
		std::cout << "AI Board: \n";
		printBoard(playerBoard);
		std::cout << "\nYour Board: \n";
		printBoard(AIboard);

		std::cout << "\nShots: [" << numberOfShots << "]\tHits: [" << numberOfHits << "] \nShots left: [" << totalShots << "]";

		
		if (totalShots <= 0 || numberOfHits == numberOfShips * 3 || AIhits == numberOfShips * 3) {
			if (AIhits == numberOfShips * 3) {
				std::cout << "\nThe AI Wins!\n";
			}
			if (totalShots <= 0) {
				std::cout << "\nYou've run out of shots!";
			}
			if (numberOfHits == numberOfShips * 3) {
				std::cout << "\nYou sunk all the ships!";
			}
			
			break;
		}
		shoot(board, playerBoard, numberOfShots, numberOfHits);
		totalShots--;
		AI(AIboard, AIhits);
		
	}
	std::cout << "\n\nGame Over!\n";
	system("pause");
	
}