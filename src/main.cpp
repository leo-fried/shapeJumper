#include <cstdlib>

#include "screen.h"
#include "font.h"
#include "level.h"
#include "properties.h"


int main (int argc, char** argv)
{
    if(argc == 2 && std::string(argv[1]) == "--debug") std::cout << "Debug mode activated.\n";

    // Objects
    Screen s;
    Font f;
    // Game Start
    f.printText("WELCOME TO SHAPE JUMPER!");
    f.printText("PRESS ENTER TO START...");
    std::cin.get();
    s.refresh();
    f.printText("LEVEL 1: EASY");
    f.printText("PRESS ENTER TO CONTINUE...");
    std::cin.get();
    Level level1(1);
    level1.refresh();
    
    return EXIT_SUCCESS;
}