// hello
// Ali
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Game
{
    string name;
    int mode;
    int boardLength;
    int boardWidth;
    int score;
};

struct Shape
{
    string color;
    int box[4][4];
};

void getInfo(Game);
void newGame();
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

    char command = getch();

    switch (command)
    {
    case '1':
        newGame();
        break;
    case '2':
        cout << "Leader Board";
        break;
    case '3':
        cout << "How to Play";
        break;
    case '4':
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

void getInfo(Game game)
{

    cout << "Please enter your name: ";
    cin >> game.name;
    cout << "\nEnter your desirable board width: ";
    cin >> game.boardWidth;
    cout << "\nEnter your desirable board length: ";
    cin >> game.boardLength;
}

void newGame()
{
    Game game;
    getInfo(game);

    // allocate board memory
    int **board = new int *[game.boardLength];
    for (int i = 0; i < game.boardWidth; i++)
    {
        int *board = new int[game.boardWidth];
    }

    // initiate primary board state
    for (int i = 0; i < game.boardLength; i++)
    {
        for (int j = 0; j < game.boardWidth; i++)
        {
            board[i][j] = 0;
        }
    }
}

void displayBoard()