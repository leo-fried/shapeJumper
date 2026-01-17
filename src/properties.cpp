#include "properties.h"

void initTerminal()
{
    initscr();
    cbreak();              // Disable line buffering
    noecho();              // Don't echo typed characters
    keypad(stdscr, TRUE);  // Enable special keys
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(0);           // Hide cursor
}

void shutdownTerminal()
{
    endwin();              // Restore terminal
}
