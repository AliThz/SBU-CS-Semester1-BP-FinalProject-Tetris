#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

// Console Text Color
#define RESET_COLOR "\033[0m"
#define BLACK_COLOR "\033[30m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define PURPLE_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"
#define WHITE_COLOR "\033[37m"

// Console Background Color
#define RESET_BGCOLOR "\033[0m"
#define BLACK_BGCOLOR "\033[40m"
#define RED_BGCOLOR "\033[41m"
#define GREEN_BGCOLOR "\033[42m"
#define YELLOW_BGCOLOR "\033[43m"
#define BLUE_BGCOLOR "\033[44m"
#define PURPLE_BGCOLOR "\033[45m"
#define CYAN_BGCOLOR "\033[46m"
#define WHITE_BGCOLOR "\033[47m"

// Console Text Style
#define BOLDON_STYLE "\033[1m"
#define BOLDOFF_STYLE "\033[22m"

struct Game
{
    string name;
    int mode;
    int boardLength;
    int boardWidth;
    int score;
    int **board;
};

struct Shape
{
    string color;
    int size;
    int **block;
};

void getInfo(Game &);
void newGame();
void ShowConsoleCursor(bool);
void displayMenu();
void displayBoard(Game);
void displayBoardTable(Game);
void exitGame();
void mainGame(Game);
Shape generateShape1();
Shape generateShape2();
Shape generateShape3();
Shape generateShape4();
Shape generateShape5();
Shape generateShape6();
Shape generateShape7();
void insertShape(Game, Shape);
void generateShape(Game);

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
        exitGame();
        break;

    default:
        cout << "Invalid command!" << endl
             << "Please enter one of the commands above ...";

        Sleep(1500);

        displayMenu();
        break;
    }
}

void exitGame()
{
    system("cls");
    cout << "Thanks for playing!";
    exit(0);
}

void getInfo(Game &game)
{
    cout << "Please enter your name: ";
    cin >> game.name;
    cout << "\nEnter your desirable board width: ";
    cin >> game.boardWidth;
    cout << "\nEnter your desirable board length: ";
    cin >> game.boardLength;
    cout << "\nEnter game mode:\n1.Normal\n2.Hard\n";
    cin >> game.mode;
}

void newGame()
{
    system("cls");
    Game game;
    getInfo(game);

    // allocate board memory
    game.board = new int *[game.boardLength];
    for (int i = 0; i < game.boardLength; i++)
    {
        game.board[i] = new int[game.boardWidth];
    }

    // initiate primary board state
    for (int i = 0; i < game.boardLength; i++)
    {
        for (int j = 0; j < game.boardWidth; j++)
        {
            game.board[i][j] = 0;
        }
    }

    mainGame(game);
}

void mainGame(Game game)
{
    generateShape(game);
    displayBoard(game);
}

void displayBoardTable(Game game)
{
    // for (int i = 0; i < (game.boardLength + 2); i++)
    for (int i = 1; i < (game.boardLength + 2); i++) // First Line Removed
    {
        for (int j = 0; j < ((game.boardWidth * 2) + 2); j++)
        {
            // First Line
            if (i == 0)
            {
                if (j == 0)
                {
                    cout << "\u250F";
                    continue;
                }
                else if (j == ((game.boardWidth * 2) + 2) - 1)
                {
                    cout << "\u2513";
                    continue;
                }

                cout << "\u2501";
                continue;
            }

            // Last Line
            else if (i == (game.boardLength + 2) - 1)
            {
                if (j == 0)
                {
                    cout << "\u2517";
                    continue;
                }
                else if (j == ((game.boardWidth * 2) + 2) - 1)
                {
                    cout << "\u251B";
                    continue;
                }

                cout << "\u2501";
                continue;
            }

            // Mid Lines
            else
            {
                if (j == 0)
                    cout << "\u2503";
                else if (j == ((game.boardWidth * 2) + 2) - 1)
                    cout << "\u2503";
                else
                {

                    cout << game.board[i - 1][(j - 1) / 2];
                }
            }
        }
        cout << endl;
    }
}

void displayBoard(Game game)
{
    system("cls");

    displayBoardTable(game);
}

int generateRandomNumber(int n)
{
    int random = rand() % n;
    return random + 1;
}

Shape generateShape1()
{
    Shape shape;

    shape.color = CYAN_COLOR;
    shape.size = 4;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    // shape.block = {0};

    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    for (int j = 0; j < shape.size; j++)
        shape.block[3][j] = 1;

    return shape;
}

Shape generateShape2()
{
    Shape shape;

    shape.color = BLUE_COLOR;
    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    for (int j = 0; j < shape.size; j++)
        shape.block[2][j] = 1;
    shape.block[1][0] = 1;

    return shape;
}

Shape generateShape3()
{
    Shape shape;

    shape.color = WHITE_COLOR;
    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < 4; j++)
            shape.block[i][j] = 0;

    for (int j = 0; j < shape.size; j++)
        shape.block[2][j] = 1;
    shape.block[1][2] = 1;

    return shape;
}

Shape generateShape4()
{
    Shape shape;

    shape.color = YELLOW_COLOR;
    shape.size = 2;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 1;

    return shape;
}

Shape generateShape5()
{
    Shape shape;

    shape.color = GREEN_COLOR;
    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    shape.block[2][0] = 1;
    shape.block[2][1] = 1;
    shape.block[1][1] = 1;
    shape.block[1][2] = 1;

    return shape;
}

Shape generateShape6()
{
    Shape shape;

    shape.color = RED_COLOR;
    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    shape.block[2][2] = 1;
    shape.block[2][1] = 1;
    shape.block[1][1] = 1;
    shape.block[1][0] = 1;

    return shape;
}

Shape generateShape7()
{
    Shape shape;

    shape.color = CYAN_COLOR;
    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < 4; j++)
            shape.block[i][j] = 0;

    for (int j = 0; j < shape.size; j++)
        shape.block[2][j] = 1;
    shape.block[1][1] = 1;

    return shape;
}

void insertShape(Game game, Shape shape)
{
    for (int i = 0; i < shape.size; i++)
    {
        int k = 0;
        for (int j = (game.boardWidth - shape.size) / 2; j < (game.boardWidth + shape.size) / 2; j++)
        {
            game.board[i][j] = shape.block[i][k];
            k++;
        }
    }
}

void generateShape(Game game)
{
    Shape shape;
    int shapeNumber = generateRandomNumber(7);

    switch (shapeNumber)
    {
    case 1:
        shape = generateShape1();
        break;
    case 2:
        shape = generateShape2();
        break;
    case 3:
        shape = generateShape3();
        break;
    case 4:
        shape = generateShape4();
        break;
    case 5:
        shape = generateShape5();
        break;
    case 6:
        shape = generateShape6();
        break;
    case 7:
        shape = generateShape7();
        break;
    }

    insertShape(game, shape);
}