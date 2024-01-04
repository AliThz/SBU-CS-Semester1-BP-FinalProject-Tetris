#include <iostream>
#include <string>

using namespace std;

int main()
{
    // cout << "\u2588\u2588" << endl;
    string a = "\u2588\u2588";

    cout << a << endl
         << endl;

    string square[2][2] = {{a, a}, {a, a}};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << square[i][j];
        }
        cout << endl;
    }

    cout << endl;

    string L[2][3] = {{a, "  ", "  "}, {a, a, a}};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << L[i][j];
        }
        cout << endl;
    }

    int length = 3,
        width = 5;

    // for (int i = 1; i < (width + 2); i++) // Remove First Line
    for (int i = 0; i < (width + 2); i++)
    {
        for (int j = 0; j < (length * 2) + 2; j++)
        {
            // First Tile
            if (i == 0)
            {
                if (j == 0)
                {
                    cout << "\u250F";
                    continue;
                }
                else if (j == (length * 2) + 2 - 1)
                {
                    cout << "\u2513";
                    continue;
                }

                cout << "\u2501";
                continue;
            }

            // Last Tile
            else if (i == (width + 2) - 1)
            {
                if (j == 0)
                {
                    cout << "\u2517";
                    continue;
                }
                else if (j == (length * 2) + 2 - 1)
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
                else if (j == (length * 2) + 2 - 1)
                    cout << "\u2503";
                else
                {
                    // cout << "\u2588";
                    cout << j;
                }
            }
        }
        cout << endl;
    }

    return 0;
}