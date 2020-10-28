#pragma once
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
    std::ifstream inf{ "Password.txt" };    //read from the file

    if (!inf)
    {
        setPassword = true;
    }

    std::string fileString;         //temp string to hold string from file
    inf >> fileString;              //get the string from file
    std::vector<char> lockPassword(fileString.begin(), fileString.end());       //save the string as a vector
    inf.close();
    int moves{ 0 };


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
            if (lockBoard[posY][posX] != '-')       //Make sure only numbers can be stored.
            {
                lockInput.push_back(lockBoard[posY][posX]);
                moves--;
            }
            lockBoard[posY][posX] = '*';            //Current location indicated with *
            printLockBoard(lockBoard);
            if (!setPassword)                       //If youre not setting the password, show how many moves remain
                std::cout << "Moves left: " << moves << std::endl;

            printVector(lockPassword);  //DEBUG
            std::cout << "Input: ";
            printVector(lockInput);

            if (setPassword)
                std::cout << "\n\nPlease input your password\nPress [Q] to save password...\n";

            if (compareVectors(lockInput, lockPassword) && setPassword == false)
            {
                std::cout << "PASSWORD ACCEPTED...\n";
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
                    std::ofstream outf{ "Password.txt" };
                    std::string save(lockInput.begin(), lockInput.end());
                    outf << save;
                    outf.close();
                    std::cout << "Password saved!\n";
                    system("pause");
                    return;
                }
                break;
            }
        }
    }
}