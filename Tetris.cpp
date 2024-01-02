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

int main()
{
    ShowConsoleCursor(bool showFlag);
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
