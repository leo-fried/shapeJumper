#include <cstdlib>

#include "screen.h"
#include "font.h"


int main (int argc, char** argv)
{
    if(argc == 2 && std::string(argv[1]) == "--debug") std::cout << "Debug mode activated.\n";

    // Objects
    Screen s;
    Font f;

    f.printChar('A');

    /*
    s.refresh("Shape Jumper\nPress enter to start...\nPress Ctrl+C to quit.");
    std::cin.get();
    for(int i = 0; i>=0; i++)
    {
        s.refresh(std::to_string(i));

    }
    */
    return EXIT_SUCCESS;
}