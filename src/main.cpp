#include "screen.h"

int main (int argc, char** argv)
{
    if(argc == 2 && std::string(argv[1]) == "--debug") std::cout << "Debug mode activated.\n";
    Screen s;
    
    return EXIT_SUCCESS;
}