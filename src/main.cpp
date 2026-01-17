#include <cstdlib>

#include "font.h"
#include "level.h"
#include "properties.h"


int main (int argc, char** argv)
{
    initTerminal();
    if(argc == 2 && std::string(argv[1]) == "--debug") printw("Debug mode activated.\n");

    // Objects
    Font f;
    // Game Start
    f.printText("WELCOME TO SHAPE JUMPER!");
    f.printText("PRESS ENTER TO START...");
    u32 ch = getch();
    while ((ch = getch()) != '\n') {} // wait for enter key
    clear();
    f.printText("LEVEL 1: EASY");
    f.printText("PRESS ENTER TO CONTINUE...");
    ch = getch();
    while ((ch = getch()) != '\n') {} // wait for enter key
    clear();

    Level level1(1);
    level1.refresh();
    
    shutdownTerminal();
    return EXIT_SUCCESS;
}