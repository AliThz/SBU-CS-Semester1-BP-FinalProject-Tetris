#include <iostream>
#include <windows.h>
#include <conio.h>

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
    string box[4][4];
};

void getInfo(Game &);
void newGame();
void ShowConsoleCursor(bool);
void displayMenu();
void displayBoard(Game);
void displayBoardTable(Game);
void exitGame();
void mainGame(Game);

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
    displayBoard(game);
}

void displayBoardTable(Game game)
{
    // for (int i = 1; i < (game.boardLength + 2); i++) // Remove First Line
    for (int i = 0; i < (game.boardLength + 2); i++)
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

// void generateShape1()
// {
// }

// void generateShape2()
// {
// }

// void generateShape3()
// {
// }

// void generateShape4()
// {
// }

// void generateShape5()
// {
// }

// void generateShape6()
// {
// }

// void generateShape7()
// {
// }

// void generateShape()
// {
//     Shape *shape;
//     int shapeNumber = generateRandomNumber(7);
//     switch (shapeNumber)
//     {
//     case 1:
//         shape = generateShape1();
//         break;
//     case 2:
//         shape = generateShape2();
//         break;
//     case 3:
//         shape = generateShape3();
//         break;
//     case 4:
//         shape = generateShape4();
//         break;
//     case 5:
//         shape = generateShape5();
//         break;
//     case 6:
//         shape = generateShape6();
//         break;
//     case 7:
//         shape = generateShape7();
//         break;
//     }

//     insertShape(shape);
// }