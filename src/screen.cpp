#include "screen.h"

Screen::Screen()
{
    // Clear the screen
    std::cout << "\033[2J\033[1;1H" << std::flush;
}
void Screen::refresh(std::string content)
{
    // Clear the screen
    std::cout << "\033[2J\033[1;1H" << std::flush;
    // Print the new content
    std::cout << content << std::flush;

}
