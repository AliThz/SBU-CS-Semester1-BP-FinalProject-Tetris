#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

#define KB_1 49
#define KB_2 50
#define KB_3 51
#define KB_4 52
#define KB_UpArrow 72
#define KB_DownArrow 80
#define KB_LeftArrow 75
#define KB_RightArrow 77
#define KB_ESC 27

void ShowConsoleCursor(bool showFlag);
void displayMenu();
void exitBoard();

int main()
{
    ShowConsoleCursor(false);
    displayMenu();

    return 0;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void displayMenu()
{
    system("cls");
    ShowConsoleCursor(false);

    cout << "Tetris" << endl

         << "1 :  New Game" << endl
         << "2 :  Leaderboard" << endl
         << "3 :  How to play" << endl
         << "4 :  Exit" << endl;

    int command = getch();

    switch (command)
    {
    case KB_1:
        cout << "New Game";
        break;
    case KB_2:
        cout << "Leader Board";
        break;
    case KB_3:
        cout << "How to Play";
        break;
    case KB_4:
        exitBoard();
        break;

    default:
        cout << "Invalid command!" << endl
             << "Please enter one of the commands above ...";

        Sleep(1500);

        displayMenu();
        break;
    }
}

void exitBoard()
{
    system("cls");
    cout << "Thanks for playing!";
    exit(0);
}