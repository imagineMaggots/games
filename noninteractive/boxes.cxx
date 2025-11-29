/**
 * Prints random boxes in terminal
 */
#include <iostream>
// for reducing framerate
#include <thread>
#include <chrono>
// rng
#include <random>
// operating system
#include <windows.h>

// some ansi colors
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
        void setHeight (int i) {
            this->size[0] = i;
        };
        void setWidth (int i) {
            this->size[1] = i;
        };
        int getHeight () {
            return this->size[0];
        };
        int getWidth () {
            return this->size[1];
        };
    private:
        // x y position of the object on screen
        int position[2] = {0,0};
        // height x width of the object
        int size[2] = {1,1};
        char figure = '~';
};

/**
 * @brief Main function, in this case, takes over the terminal!
 */
int main (void)// you could pass nothing OR you could tell the program, that you _are_ passing _nothing_
{
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
        
        
        // BOX SIZE // BOX SIZE // BOX SIZE
        // BOX SIZE // BOX SIZE
        // BOX SIZE
        int xr = rand() % 13;
        int yr = rand() % 7;
        obi.setHeight(xr+3);
        obi.setWidth(yr+3);


        // First logic here
        r = r % 4;
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


        int h = obi.getHeight();
        int w = obi.getWidth();
        std::string escapeSequence = "\x1B[";
        // moving the cursor down to the x-position of the object
        escapeSequence.append(std::to_string(obi.getX()));
        escapeSequence.append("B\x1B[");
        // moving the cursor right to the y-position of the object
        escapeSequence.append(std::to_string(obi.getY()));
        escapeSequence.append("C");
        // handled by os
        std::cout << escapeSequence;


        // gotta reset by the amount of printed characters in line
        std::string widthReset = "\x1B[";
        widthReset.append(std::to_string(w));
        widthReset.append("D");

        // fills the screen
        for(int x = 0; x < h; x++)
        {
            for(int y = 0; y < w; y++)
            {
                std::cout << obi.getFigure();
            }
            std::cout << "\x1B[1B";
            std::cout << widthReset; // see above
        }

        // to do: apply frame rate
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::system("cls");
    }
    return 0;
}