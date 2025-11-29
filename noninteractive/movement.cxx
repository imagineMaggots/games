/**
 * Those random cli bars everyone likes i guess
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

enum direction {
    left,
    right,
    up,
    down,
};

// virtual object representation
class object {
    public:
        void setPosition (int x, int y) {
            this->position[0] = x;
            this->position[1] = y;
        };
        int* getPosition () {
            return this->position;
        };
        int getX () {
            return this->position[0];
        };
        int getY () {
            return this->position[1];
        };
        void setX (int i) {
            this->position[0] = i;
        };
        void setY (int i) {
            this->position[1] = i;
        };
        // move the object by one unit in (a certain band)
        void move (direction dir) {
            switch (dir)
            {
                // to avoid confusion: we count columns from left to right. that means, a move "left" requires access to the prev col
                case left:
                    setPosition(getX()-1,getY());
                    break;
                case right:
                    setPosition(getX()+1,getY());
                    break;
                // to avoid confusion: we count lines from top to bottom. that means, a move "up" requires access to the prev line
                case up:
                    setPosition(getX(),getY()-1);
                    break;
                case down:
                    setPosition(getX(),getY()+1);
                    break;
                default:
                    setPosition(0,0);
                    break;
            }
        };
        char getFigure () {
            return this->figure;
        };
        void setFigure (char c) {
            this->figure = c;
        };
    private:
        int position[2] = {0,0};
        char figure = '~';
};

/**
 * @brief Main function, in this case, takes over the terminal!
 */
int main (void)// you could pass nothing OR you could tell the program, that you _are_ passing _nothing_
{
    std::system("cls");
    fputs("\e[?25l", stdout); /* hide the cursor */

    object obi;
    obi.setPosition(0,0);

    while(true)
    {
        // moves cursor to the top again???
        std::cout << "\x1b[H";
        // BETTER THAN "std::system("cls")"!!!!!

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
        // makes sure the object stays inside the terminal
        if(obi.getX() < 0) obi.setX(rows-1); 
        if(obi.getY() < 0) obi.setY(columns-1); 
        // to handle resizes
        obi.setPosition(obi.getX() % rows,obi.getY() % columns);
        
        
        // First logic here
        r = r % 4;
        int xr = rand() % 13;
        switch(r)
        {
            case 0:
                for(int d = 0; d < xr; d++) obi.move(left);
                break;
            case 1:
                for(int d = 0; d < xr; d++) obi.move(up);
                break;
            case 2:
                for(int d = 0; d < xr; d++) obi.move(right);
                break;
            case 3:
                for(int d = 0; d < xr; d++) obi.move(down);
                break;
        }



        /* NOTE:    doing it like this will reset the whole screen everytime, 
                    which is unnecessary due to ANSI Cursor Controls and Erase Functions! */
        // fills the screen
        for(int x = 0; x < rows; x++)
        {
            for(int y = 0; y < columns; y++)
            {
                if(x == obi.getX() && y == obi.getY()) {
                    obi.setFigure('~');
                }
                else {
                    obi.setFigure(' ');
                }
                std::cout << obi.getFigure();
            }
            std::cout << "\n";
        }
    }
    return 0;
}