// Oblig3.cpp

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>

void printVector(std::vector<char> array) 
{
    for (int i = 0; i < array.size(); i++)
    {
        std::cout << array.at(i) << " - ";
    }

    std::cout << std::endl;
}

bool compareVectors(std::vector<char> array1, std::vector<char> array2) 
{
    if (array1.size() != array2.size())
        return false;

    for (int i = 0; i < array1.size(); i++)
    {
        if (array1.at(i) != array2.at(i))
            return false;
    }

    return true;
}

void printLockBoard(char array[6][10]) 
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << array[i][j];
        }
        std::cout << std::endl;
    }
}

void task1(bool setPassword = false) 
{
    std::ifstream inf{ "Password.dat" };    //read from the file
    
    if (!inf) 
    {
        std::cout << "UNABLE TO READ FILE, EXITING PROGRAM";
        exit(0);
    }

    std::string fileString;         //temp string to hold string from file
    inf >> fileString;              //get the string from file
    std::vector<char> lockPassword(fileString.begin(), fileString.end());       //save the string as a vector
    int moves{0};


    while (true) {
        std::vector<char> lockInput{};
        int posX{ 1 };
        int posY{ 1 };
        char pInput{ ' ' };
        char lockBoard[6][10]{
            "+-------+",
            "|A|B|C|D|",
            "|E|F|G|H|",
            "|I|J|K|L|",
            "|M|N|O|P|",
            "+-------+",
        };

        if (lockPassword.size() != 0)
            moves = lockPassword.size();
        else
            setPassword = true;

        while (true)
        {
            system("cls");
            if (lockBoard[posY][posX] != '-') 
            {
                lockInput.push_back(lockBoard[posY][posX]);
                moves--;
            }
            lockBoard[posY][posX] = '*';
            printLockBoard(lockBoard);
            if(!setPassword)
                std::cout << "Moves left: " << moves << std::endl;

            printVector(lockPassword);
            printVector(lockInput);

            if (setPassword)
                std::cout << "\n\nPress [Q] to save password...\n";

            if (compareVectors(lockInput, lockPassword) && setPassword == false)
            {
                std::cout << "PASSWORD ACCEPTED...\n";
                std::ofstream outf{ "Password.dat" };
                std::string save(lockPassword.begin(), lockPassword.end());
                outf << save;
                system("pause");
                return;
            }

            if (moves <= 0 && setPassword == false) {
                std::cout << "\n\nMoves exhausted! Resetting...";
                _getch();
                break;
            }

            pInput = _getch();
            lockBoard[posY][posX] = '-';
            switch (pInput) {
            case 'W': case 'w':
                posY--;
                if (posY <= 0)
                    posY = 1;
                break;
            case 'A': case 'a':
                posX -= 2;
                if (posX <= 0)
                    posX = 1;
                break;
            case 'S': case 's':
                posY++;
                if (posY >= 5)
                    posY = 4;
                break;
            case 'D': case 'd':
                posX += 2;
                if (posX >= 8)
                    posX = 7;
                break;
            case 'Q': case 'q':
                if (setPassword) {
                    std::ofstream outf{ "Password.dat" };
                    std::string save(lockInput.begin(), lockInput.end());
                    outf << save;
                    std::cout << "Password saved!\n";
                    system("pause");
                    return;
                }
                break;
            }
        }
    }
}

int main()
{
    task1();

    while (true) 
    {
        system("cls");
        char input{ ' ' };
        std::cout << "Main Menu \nPlease make a selection: \n\n[1] Change Password \n[2] Play Battleship \n[3] Quit";

        input = _getch();
        switch (input) 
        {
        case '1':
            task1(true);
            break;
        case '2':
        case '3':
            exit(0);
            break;
        };
    }
}
