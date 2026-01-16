#include "screen.h"

Screen::Screen()
{
    // Clear the screen
    std::cout << "\033[2J\033[1;1H" << std::flush;
}
void Screen::refresh()
{
    // Clear the screen
    std::cout << "\033[2J\033[1;1H" << std::flush;
}
