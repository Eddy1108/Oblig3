// Oblig3.cpp

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include "LockScreen.h"
#include "Battleship.h"

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
            play();
            break;
        case '3':
            exit(0);
            break;
        };
    }
}
