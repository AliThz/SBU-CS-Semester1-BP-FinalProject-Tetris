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

struct Shape
{
    int size;
    int **block;
    int positionX;
    int positionY;
};

struct Game
{
    string playerName;
    int mode;
    int boardLength;
    int boardWidth;
    int score;
    Shape upcomingShapes[4];
    Element **board;
};

/*MENU*/
void displayMenu(); // displays the menu
void printCharacterByCharacter(string, int, int, char);
void displayHowToPlay();
void getCustomInfo(Game &); // sets data required for running the game quickly
void setQuickInfo(Game &);  // gets data required for running a saving the game from the player
void generateNewGame();     // calls "getInfo" and creats a new board and sends data to "playGame"
void exitGame();            // closes the game permanently

/*GAMEPLAY*/
void playGame(Game); // starts the main game sequence (the control panel of the game)
void makeMove(Game &);
void moveLeft(Game &);
void moveRight(Game &);
bool moveDown(Game &);
void displayUpcomingShapes(Shape[]); // Displays upcoming shapes
void displayBoardTable(Game);        // prints out the board table
string chooseColor(int);             // determines the color of an object
void insertShape(Game);              // inserts the shape into the board
void removeShape(Game);              // removes shape from previous location

void fixBlocks(Game); // copies game board into game board
void deallocate(Game);
void deallocate(Shape);
void popRow(Game, int);

/*CONTROLS*/
void checkIfRowIsFull(Game);
bool checkIfLost(Game);
bool checkDown(Game);     // to check down-move possibility
bool checkLeft(Game);     // to check lefr-move possibility
bool checkRight(Game);    // to check right-move possibility
bool checkRotation(Game); // to check rotation possibility
void rotateShapeClockwise(Shape);
void rotateShapeCounterClockwise(Shape);

/*SHAPES*/
int generateRandomNumber(int); // generates a random shape number
Shape generateShape();         // chooses a random shape from below
Shape generateShape1();        // shape I
Shape generateShape2();        // shape O
Shape generateShape3();        // shape L
Shape generateShape4();        // shape J
Shape generateShape5();        // shape S
Shape generateShape6();        // shape Z
Shape generateShape7();        // shape T

/*TERMINAL*/
void setCursor(int x = 0, int y = 0);
void showConsoleCursor(bool); // makes the cursor not show in terminal

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    // cout << "\e[8;30;50t";
    // PlaySound(TEXT("Tetris.wav"), NULL, SND_FILENAME| SND_ASYNC);
    displayMenu();
    return 0;
}

/*MENU*/
void displayMenu()
{
    system("cls");
    showConsoleCursor(false);

    string title = "+-+ +-+ +-+ +-+ +-+ +-+\n|T| |E| |T| |R| |I| |S|\n+-+ +-+ +-+ +-+ +-+ +-+\n\n1 :  New Game\n2 :  Leaderboard\n3 :  How to play\n4 :  Exit\n\n";
    printCharacterByCharacter(title, 1, 1000, '~');

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
        displayHowToPlay();
        break;
    case '4':
        exitGame();
        break;

    default:
        cout << RED_COLOR << "Invalid command!" << endl
             << "Please enter one of the commands above ..." << RESET_COLOR;

        Sleep(1500);

        displayMenu();
        break;
    }
}

void printCharacterByCharacter(string message, int shortSleep, int longSleep, char longSleepDetector = '~')
{
    for (int i = 0; i < message.length(); i++)
    {
        if (kbhit())
        {
            getch();
            for (int j = i; j < message.length(); j++)
            {
                if (message[j] != longSleepDetector)
                    cout << message[j];
                else
                    continue;
            }

            break;
        }

        if (message[i] == longSleepDetector)
            Sleep(longSleep);
        else
        {
            cout << message[i];
            Sleep(shortSleep);
        }
    }
}

void displayHowToPlay()
{
    system("cls");
    string explaination = "Hi\nI'm Ali Taherzadeh\n~and this is a test description";
    printCharacterByCharacter(explaination, 5, 1000);
    getch();
}

void setQuickInfo(Game &game)
{
    system("cls");

    game.boardWidth = 10;
    game.boardLength = 20;
    game.mode = 1;
}

void getCustomInfo(Game &game)
{
    system("cls");

    cout << "\nEnter your desirable board width: ";
    cin >> game.boardWidth;
    cout << "\nEnter your desirable board length: ";
    cin >> game.boardLength;
    cout << "\nEnter game mode: ";
    cin >> game.mode;
}

void generateNewGame()
{
    system("cls");

    Game game;

    cout << "New Game\n\n1 :  Quick Game\n2 :  Custom Game\n";
    char command = getch();

    if (command == '1')
        setQuickInfo(game);
    else if (command == '2')
        getCustomInfo(game);
    else
    {
        cout << RED_COLOR << "\nPlease choose one of the above options" << RESET_COLOR;
        Sleep(500);
        generateNewGame();
    }

    cout << "\nPlease enter your name: ";
    cin >> game.playerName;

    // allocate board memory
    game.board = new Element *[game.boardLength];
    for (int i = 0; i < game.boardLength; i++)
        game.board[i] = new Element[game.boardWidth];

    // initialize primary board state
    for (int i = 0; i < game.boardLength; i++)
        for (int j = 0; j < game.boardWidth; j++)
            game.board[i][j].number = 0;

    for (int i = 1; i < 4; i++)
    {
        game.upcomingShapes[i] = generateShape();
        game.upcomingShapes[i].positionX = 0;
        game.upcomingShapes[i].positionY = (game.boardWidth - game.upcomingShapes[i].size) / 2;
    }

    system("cls");
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
    while (true)
    {
        for (int i = 0; i < 3; i++)
            game.upcomingShapes[i] = game.upcomingShapes[i + 1];

        game.upcomingShapes[3] = generateShape();
        game.upcomingShapes[3].positionX = 0;
        game.upcomingShapes[3].positionY = (game.boardWidth - game.upcomingShapes[3].size) / 2;

        insertShape(game);

        makeMove(game);

        fixBlocks(game);

        checkIfRowIsFull(game);

        if (checkIfLost(game))
            break;
    }
}

void makeMove(Game &game)
{
    int command = 0;
    bool flag = true;
    while (flag) // start getting move commands
    {
        displayUpcomingShapes(game.upcomingShapes);
        displayBoardTable(game);

        Sleep(300);
        if (kbhit())
        {
            command = getch();
            if (command == 224)
                command = getch();
        }
        else
            command = KB_SPACE;

        switch (command)
        {
        case KB_SPACE:
            flag = moveDown(game);

            break;
        case KB_LeftArrow:
            moveLeft(game);
            break;
        case KB_RightArrow:
            moveRight(game);
            break;
        case KB_UpArrow:
            if (checkRotation(game))
                rotateShapeClockwise(game.upcomingShapes[0]);
            break;
        case KB_DownArrow:
            if (checkRotation(game))
                rotateShapeCounterClockwise(game.upcomingShapes[0]);
            break;
        case KB_ESC:
            system("cls");
            cout << "Pause Menu";
            break;

        default:
            cout << RED_COLOR << "Invalid move!" << RESET_COLOR;
            Sleep(5000);
            break;
        }
    }
}

void moveLeft(Game &game)
{
    if (checkLeft(game))
    {
        removeShape(game);
        game.upcomingShapes[0].positionY--;
        insertShape(game);
    }
}

void moveRight(Game &game)
{
    if (checkRight(game))
    {
        removeShape(game);
        game.upcomingShapes[0].positionY++;
        insertShape(game);
    }
}

// remove bool
bool moveDown(Game &game)
{
    if (checkDown(game))
    {
        removeShape(game);
        game.upcomingShapes[0].positionX++;
        insertShape(game);
        return true;
    }

    return false;
}

void displayUpcomingShapes(Shape shapes[])
{
    system("cls");
    // setCursor();
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
    setCursor(0, 5);
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
                        cout << chooseColor(block) << "\u2588\u2588" << RESET_COLOR;
                    else
                        cout << "  ";
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

void insertShape(Game game)
{
    Shape shape = game.upcomingShapes[0];
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

void removeShape(Game game)
{
    Shape shape = game.upcomingShapes[0];
    for (int i = shape.positionX; i < shape.positionX + shape.size; i++)
    {
        for (int j = shape.positionY; j < shape.positionY + shape.size; j++)
        {
            if (game.board[i][j].isMoveable == true && game.board[i][j].number != 0)
                game.board[i][j].number = 0;
        }
    }
}

void fixBlocks(Game game)
{
    for (int i = 0; i < game.boardLength; i++)
    {
        for (int j = 0; j < game.boardWidth; j++)
        {
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

void popRow(Game game, int fullRow)
{
    for (int j = 0; j < game.boardWidth; j++)
    {
        game.board[fullRow][j].number = 0;
        game.board[fullRow][j].isMoveable = true;
    }
    setCursor(0, 5);
    displayBoardTable(game);
    Sleep(200);
    for (int i = fullRow; i > 0; i--)
    {
        for (int j = 0; j < game.boardWidth; j++)
        {
            swap(game.board[i][j], game.board[i - 1][j]);
        }
    }
}

/*CONTROLS*/
void checkIfRowIsFull(Game game)
{
    for (int i = game.boardLength - 1; i >= 0; i--)
    {
        bool isFull = true;
        for (int j = 0; j < game.boardWidth; j++)
        {
            if (game.board[i][j].number == 0)
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            popRow(game, i);
            i = game.boardLength - 1;
        }
    }
}

bool checkIfLost(Game game)
{
    for (int j = abs((game.boardWidth - 4) / 2); j < abs((game.boardWidth + 4) / 2); j++)
        if (game.board[0][j].number != 0)
            return true;

    return false;
}

bool checkDown(Game game)
{
    Shape shape = game.upcomingShapes[0];
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

bool checkLeft(Game game)
{
    Shape shape = game.upcomingShapes[0];

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

bool checkRight(Game game)
{
    Shape shape = game.upcomingShapes[0];

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

bool checkRotation(Game game)
{
    Shape shape = game.upcomingShapes[0];

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

    for (int i = 1; i < generateRandomNumber(4); i++)
        rotateShapeClockwise(shape);

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
        shape.block[0][j] = 1;

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
        shape.block[1][j] = 3;
    shape.block[0][2] = 3;

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
        shape.block[1][j] = 4;
    shape.block[0][0] = 4;

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

    shape.block[1][0] = 5;
    shape.block[1][1] = 5;
    shape.block[0][1] = 5;
    shape.block[0][2] = 5;

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

    shape.block[1][2] = 6;
    shape.block[1][1] = 6;
    shape.block[0][1] = 6;
    shape.block[0][0] = 6;

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
        shape.block[1][j] = 7;
    shape.block[0][1] = 7;

    return shape;
}

/*TERMINAL*/
void setCursor(int x, int y)
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);
}

void showConsoleCursor(bool flagStatus)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flagStatus;
    SetConsoleCursorInfo(out, &cursorInfo);
}
