/**
 * THANKS TO https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
 * 
 * THIS GETS THE CURRENT HEIGHT/WIDTH OF THE TERMINAL
 * 
 * THIS IS C, NOT C++
 * USING C++ FOR COMFORT THOUGH
 * WINDOWS SUCKS; BUT I LOVE IT
 */
#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]) 
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  
    printf("columns: %d\n", columns);
    printf("rows: %d\n", rows);
    return 0;
}