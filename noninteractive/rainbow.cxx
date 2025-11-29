/**
 * Fills the terminal with a somewhat pretty rainbow.
 */
#include <iostream>
#include <random>
#include <windows.h>
#define red "\033[31m"
#define yellow "\033[32m"
#define green "\033[33m"
#define cyan "\033[34m"
#define blue "\033[35m"
#define magenta "\033[36m"
#define white "\033[37m"

/**
 * @brief Main function, in this case, takes over the terminal!
 */
int main (void)// you could pass nothing OR you could tell the program, that you _are_ passing _nothing_
{
    // so the terminal is wiped clean at the start
    std::system("cls");
    fputs("\e[?25l", stdout); /* hide the cursor */
    
    // haiiii :3
    std::cout << "hello\n";
    // this runs until ctrl+c (terminate) is called from the user
    while(true)
    {
        // moves cursor to the top again???
        std::cout << "\x1b[H";

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;
    
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top;

        int r = rand() % 7;
        switch(r)
        {
            case 0:
                std::cout << red;
                break;
            case 1:
                std::cout << yellow;
                break;
            case 2:
                std::cout << green;
                break;
            case 3:
                std::cout << cyan;
                break;
            case 4:
                std::cout << blue;
                break;
            case 5:
                std::cout << magenta;
                break;
            case 6:
                std::cout << white;
        }

        // fills the screen
        for(int x = 0; x < rows; x++)
        {
            for(int y = 0; y < columns; y++)
            {
                std::cout << "~";
            }
            std::cout << "\n";
        }
    }
    return 0;
}