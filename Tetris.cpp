#include <iostream>

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

int main()
{




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
    int** board = new int*[game.boardLength];
    for (int i = 0; i < game.boardWidth; i++)
    {
        int* board = new int[game.boardWidth];
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

