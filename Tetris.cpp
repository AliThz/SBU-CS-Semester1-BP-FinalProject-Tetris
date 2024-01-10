#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define KB_UpArrow 72
#define KB_DownArrow 80
#define KB_LeftArrow 75
#define KB_RightArrow 77
#define KB_ESC 27
#define KB_SPACE 32

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

struct Element
{
    int number;
    bool isMoveable = true;
};

struct Game
{
    string name;
    int mode;
    int boardLength;
    int boardWidth;
    int score;
    Element **board;
};

struct Shape
{
    int size;
    int **block;
    int positionX;
    int positionY;
    int rotation = 0; // needs further thinking
};

/*MENU*/
void displayMenu(); // displays the menu
void getCustomInfo(Game &); // sets data required for running the game quickly
void setQuickInfo(Game &); // gets data required for running a saving the game from the player  
void generateNewGame(); // calls "getInfo" and creats a new board and sends data to "playGame"
void exitGame();        // closes the game permanently

/*GAMEPLAY*/
void playGame(Game);                 // starts the main game sequence (the control panel of the game)
void displayUpcomingShapes(Shape[]); // Displays upcoming shapes
void displayBoardTable(Game);        // prints out the board table
string chooseColor(int);             // determines the color of an object
void insertShape(Game, Shape);       // inserts the shape into the board
void removeShape(Game, Shape);       // removes shape from previous location
void copyGameToTemp(Game, Game);     // copies game board into temp board
void copyTempToBoard(Game, Game);    // copies temp board into game board
void deallocate(Game);
void deallocate(Shape);

/*CONTROLS*/
bool checkDown(Game, Shape);     // to check down-move possibility
bool checkLeft(Game, Shape);     // to check lefr-move possibility
bool checkRight(Game, Shape);    // to check right-move possibility
bool checkRotation(Game, Shape); // to check rotation possibility
void rotateShapeClockwise(Shape);
void rotateShapeCounterClockwise(Shape);

/*SHAPES*/
int generateRandomNumber(int); // generates a random shape number
Shape generateShape();         // chooses a random shape from below
Shape generateShape1();        // shape I
Shape generateShape2();        // shape O
Shape generateShape3();        // shape J
Shape generateShape4();        // shape L
Shape generateShape5();        // shape S
Shape generateShape6();        // shape Z
Shape generateShape7();        // shape T

/*TERMINAL*/
void ShowConsoleCursor(bool); // makes the cursor not show in terminal

int main()
{
    // PlaySound(TEXT("Tetris.wav"), NULL, SND_FILENAME| SND_ASYNC);
    displayMenu();
    return 0;
}

/*MENU*/
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
        generateNewGame();
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

void setQuickInfo(Game &game)
{
    game.boardWidth = 10;
    game.boardLength = 20;
}

void getCustomInfo(Game &game)
{
    cout << "\nEnter your desirable board width: ";
    cin >> game.boardWidth;
    cout << "\nEnter your desirable board length: ";
    cin >> game.boardLength;
}

void generateNewGame()
{
    system("cls");
    Game game;

    cout << "New Game\n\n1 :  Quick Game\n2 :  Custom Game";
    char command = getch();
    system("cls");
    cout << "Please enter your name: ";
    cin >> game.name;
    cout << "\nEnter game mode:\n1.Normal\n2.Hard\n";
    cin >> game.mode;

    if (command == '1')
        setQuickInfo(game);
    else if (command == '2')
        getCustomInfo(game);

    // allocate board memory
    game.board = new Element *[game.boardLength];
    for (int i = 0; i < game.boardLength; i++)
        game.board[i] = new Element[game.boardWidth];

    // initialize primary board state
    for (int i = 0; i < game.boardLength; i++)
        for (int j = 0; j < game.boardWidth; j++)
            game.board[i][j].number = 0;

    playGame(game);
}

void exitGame()
{
    system("cls");
    cout << "Thanks for playing!";
    exit(0);
}

/*GAMEPLAY*/
void playGame(Game game)
{
    int command = 0;

    Game temp; // create temporary board to change shape status
    temp.boardLength = game.boardLength;
    temp.boardWidth = game.boardWidth;

    // allocate board memory
    temp.board = new Element *[temp.boardLength];
    for (int i = 0; i < temp.boardLength; i++)
        temp.board[i] = new Element[temp.boardWidth];

    Shape upcomingShapes[4];
    for (int i = 1; i < 4; i++)
    {
        upcomingShapes[i] = generateShape();
        upcomingShapes[i].positionX = 0;
        upcomingShapes[i].positionY = (temp.boardWidth - upcomingShapes[i].size) / 2;
    }

    while (command != KB_ESC)
    {
        for (int i = 0; i < 3; i++)
            upcomingShapes[i] = upcomingShapes[i + 1];

        upcomingShapes[3] = generateShape();
        upcomingShapes[3].positionX = 0;
        upcomingShapes[3].positionY = (temp.boardWidth - upcomingShapes[3].size) / 2;

        copyGameToTemp(game, temp); // initialize temp board equal to main game board
        insertShape(temp, upcomingShapes[0]);

        while (true) // start getting move commands
        {
            system("cls");
            displayUpcomingShapes(upcomingShapes);
            displayBoardTable(temp);

            Sleep(500);
            if (kbhit())
            {
                command = getch();
                if (command == 224)
                    command = getch();
            }
            else
                command = KB_SPACE;

            if (command == KB_SPACE)
            {
                if (checkDown(temp, upcomingShapes[0]))
                {
                    removeShape(temp, upcomingShapes[0]);
                    upcomingShapes[0].positionX++;
                    insertShape(temp, upcomingShapes[0]);
                    continue;
                }

                else
                    break;
            }

            if (command == KB_LeftArrow)
            {
                if (checkLeft(temp, upcomingShapes[0]))
                {
                    removeShape(temp, upcomingShapes[0]);
                    upcomingShapes[0].positionY--;
                    insertShape(temp, upcomingShapes[0]);
                }

                else
                    continue;
            }

            else if (command == KB_RightArrow)
            {
                if (checkRight(temp, upcomingShapes[0]))
                {
                    removeShape(temp, upcomingShapes[0]);
                    upcomingShapes[0].positionY++;
                    insertShape(temp, upcomingShapes[0]);
                }

                else
                    continue;
            }

            else if (command == KB_UpArrow)
            {
                if (checkRotation(temp, upcomingShapes[0]))
                {
                    rotateShapeClockwise(upcomingShapes[0]);
                }
                else
                    continue;
            }

            else if (command == KB_DownArrow)
            {
                if (checkRotation(temp, upcomingShapes[0]))
                {
                    rotateShapeCounterClockwise(upcomingShapes[0]);
                }

                else
                    continue;
            }

            else
            {
                cout << RED_COLOR << "Invalid move!" << RESET_COLOR;
                Sleep(500);
                continue;
            }
        }

        copyTempToBoard(game, temp); // complete the changes on the main board
    }
}

void displayUpcomingShapes(Shape shapes[])
{
    for (int i = 0; i < 4; i++)
    {
        for (int k = 1; k < 4; k++)
        {
            for (int j = 0; j < 4; j++)
            {

                if (i >= shapes[k].size || j >= shapes[k].size)
                {
                    cout << "  ";
                }
                else if (shapes[k].block[i][j])
                    cout << chooseColor(shapes[k].block[i][j]) << "\u2588\u2588";

                else
                    cout << "  ";
                cout << RESET_COLOR;
            }
            cout << " ";
        }
        cout << endl;
    }
}

void displayBoardTable(Game game)
{
    // for (int i = 0; i < (game.boardLength + 2); i++)
    for (int i = 1; i < (game.boardLength + 2); i++) // First Line Removed
    {
        for (int j = 0; j < (game.boardWidth + 2); j++)
        {
            // First Line
            if (i == 0)
            {
                if (j == 0)
                {
                    cout << "\u250F";
                    continue;
                }
                else if (j == (game.boardWidth + 2) - 1)
                {
                    cout << "\u2513";
                    continue;
                }

                cout << "\u2501\u2501";
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
                else if (j == (game.boardWidth + 2) - 1)
                {
                    cout << "\u251B";
                    continue;
                }

                cout << "\u2501\u2501";
                continue;
            }

            // Mid Lines
            else
            {
                if (j == 0)
                    cout << "\u2503";
                else if (j == (game.boardWidth + 2) - 1)
                    cout << "\u2503";
                else
                {
                    int block = game.board[i - 1][j - 1].number;
                    if (block != 0)
                        cout << chooseColor(block) << " " << game.board[i - 1][j - 1].isMoveable << RESET_COLOR;
                    else
                        cout << " " << game.board[i - 1][j - 1].isMoveable;
                }
            }
        }
        cout << endl;
    }
}

string chooseColor(int shapeNumber)
{
    switch (shapeNumber)
    {
    case 1:
        return CYAN_COLOR;
        break;
    case 2:
        return YELLOW_COLOR;
        break;
    case 3:
        return WHITE_COLOR;
        break;
    case 4:
        return BLUE_COLOR;
        break;
    case 5:
        return GREEN_COLOR;
        break;
    case 6:
        return RED_COLOR;
        break;
    case 7:
        return PURPLE_COLOR;
        break;
    default:
        return RESET_COLOR;
    }
}

void insertShape(Game game, Shape shape)
{
    int shapeRow = 0;
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        int shapeCol = 0;
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (shape.block[shapeRow][shapeCol] != 0)
            {
                game.board[i][j].number = shape.block[shapeRow][shapeCol];
            }
            shapeCol++;
        }
        shapeRow++;
    }
}

void removeShape(Game game, Shape shape)
{
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (game.board[i][j].isMoveable == true && game.board[i][j].number != 0)
                game.board[i][j].number = 0;
        }
    }
}

void copyGameToTemp(Game game, Game temp)
{
    for (int i = 0; i < temp.boardLength; i++)
    {
        for (int j = 0; j < temp.boardWidth; j++)
        {
            temp.board[i][j].number = game.board[i][j].number;
            temp.board[i][j].isMoveable = game.board[i][j].isMoveable;
        }
    }
}

void copyTempToBoard(Game game, Game temp)
{
    for (int i = 0; i < temp.boardLength; i++)
    {
        for (int j = 0; j < temp.boardWidth; j++)
        {
            game.board[i][j].number = temp.board[i][j].number;

            if (game.board[i][j].number != 0 && game.board[i][j].isMoveable != false)
                game.board[i][j].isMoveable = false;
        }
    }
}

void deallocate(Game game)
{
    for (int i = 0; i < game.boardLength; i++)
    {
        delete[] game.board[i];
    }
    delete[] game.board;
}

void deallocate(Shape shape)
{
    for (int i = 0; i < shape.size; i++)
    {
        delete[] shape.block[i];
    }
    delete[] shape.block;
}
/*CONTROLS*/
bool checkDown(Game game, Shape shape)
{
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (game.board[i][j].number != 0 && game.board[i][j].isMoveable == true)
            {
                if (i + 1 == game.boardLength || game.board[i + 1][j].number != 0 && game.board[i + 1][j].isMoveable == false)
                    return false;
            }
        }
    }
    return true;
}

bool checkLeft(Game game, Shape shape)
{
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (game.board[i][j].number != 0 && game.board[i][j].isMoveable == true)
            {
                if (j == 0 || (game.board[i][j - 1].number != 0 && game.board[i][j - 1].isMoveable == false))
                    return false;
            }
        }
    }
    return true;
}

bool checkRight(Game game, Shape shape)
{
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (game.board[i][j].number != 0 && game.board[i][j].isMoveable == true)
            {
                if (j + 1 == game.boardWidth || game.board[i][j + 1].number != 0 && game.board[i][j + 1].isMoveable == false)
                    return false;
            }
        }
    }
    return true;
}

bool checkRotation(Game game, Shape shape)
{
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (game.board[i][j].number != 0 && game.board[i][j].isMoveable == false)
            {
                return false;
            }
        }
    }
    return true;
}

void rotateShapeClockwise(Shape shape)
{
    for (int i = 0; i < shape.size; i++)
    {
        for (int j = i + 1; j < shape.size; j++)
        {
            swap(shape.block[i][j], shape.block[j][i]);
        }
    }

    for (int i = 0; i < shape.size; i++)
    {
        for (int j = 0; j < shape.size / 2; j++)
        {
            swap(shape.block[i][j], shape.block[i][shape.size - 1 - j]);
        }
    }
}

void rotateShapeCounterClockwise(Shape shape)
{

    for (int i = 0; i < shape.size; i++)
    {
        for (int j = i + 1; j < shape.size; j++)
        {
            swap(shape.block[i][j], shape.block[j][i]);
        }
    }

    for (int j = 0; j < shape.size; j++)
    {
        for (int i = 0; i < shape.size / 2; i++)
        {
            swap(shape.block[i][j], shape.block[shape.size - 1 - i][j]);
        }
    }
}
/*SHAPES*/
int generateRandomNumber(int n)
{
    int random = rand() % n + 1;
    return random;
}

Shape generateShape()
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

    return shape;
}

Shape generateShape1()
{
    Shape shape;

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
        shape.block[2][j] = 1;

    return shape;
}

Shape generateShape2()
{
    Shape shape;

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
            shape.block[i][j] = 2;

    return shape;
}

Shape generateShape3()
{
    Shape shape;

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
        shape.block[2][j] = 3;
    shape.block[1][2] = 3;

    return shape;
}

Shape generateShape4()
{
    Shape shape;

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
        shape.block[2][j] = 4;
    shape.block[1][0] = 4;

    return shape;
}

Shape generateShape5()
{
    Shape shape;

    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    shape.block[2][0] = 5;
    shape.block[2][1] = 5;
    shape.block[1][1] = 5;
    shape.block[1][2] = 5;

    return shape;
}

Shape generateShape6()
{
    Shape shape;

    shape.size = 3;

    // Allocate block memory
    shape.block = new int *[shape.size];
    for (int i = 0; i < shape.size; i++)
        shape.block[i] = new int[shape.size];

    // Initialize block values
    for (int i = 0; i < shape.size; i++)
        for (int j = 0; j < shape.size; j++)
            shape.block[i][j] = 0;

    shape.block[2][2] = 6;
    shape.block[2][1] = 6;
    shape.block[1][1] = 6;
    shape.block[1][0] = 6;

    return shape;
}

Shape generateShape7()
{
    Shape shape;

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
        shape.block[2][j] = 7;
    shape.block[1][1] = 7;

    return shape;
}

/*TERMINAL*/
void ShowConsoleCursor(bool flagStatus)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flagStatus;
    SetConsoleCursorInfo(out, &cursorInfo);
}
