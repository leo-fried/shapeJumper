#include "font.h"
#include "level.h"
#include "properties.h"


int main (int argc, char** argv)
{
    initTerminal();
    if(argc == 2 && std::string(argv[1]) == "--debug") printw("Debug mode activated.\n");

    // Objects
    Font f;
    Player p;
    char* icons = p.getAvailableIcons();
    const u32 ICONCOUNT = p.getIconCount();

    // Game Start
    printw("Press \"C\" to select character\n");
    f.printText("WELCOME TO SHAPE JUMPER!");
    f.printText("PRESS ENTER TO START...");
    s32 ch = getch();
    while ((ch = getch()) != '\n' && ch != 'c' && ch != 'C') {} // wait for enter key or c key
    clear();
    if (ch == 'c' || ch == 'C') {
        
        char tempIcon = icons[0];
        while(1)
        {
            f.printText("SELECT YOUR CHARACTER WITH ARROW KEYS:");
            printw("\nCurrent Character: "); printw("%c", tempIcon);printw("\n");
            f.printText("PRESS ENTER TO CONFIRM ");
            ch = getch();
            while ((ch = getch()) != '\n' && ch != KEY_LEFT && ch != KEY_RIGHT) {} // wait for enter key or arrow keys
            if(ch == KEY_LEFT)
            {
                // Move selection left
                for (u32 i = 0; i < ICONCOUNT; i++)
                {
                    if (icons[i] == tempIcon)
                    {
                        tempIcon = icons[(i + ICONCOUNT - 1) % ICONCOUNT]; // wrap around using modulo
                        break;
                    }
                }
            }
            else if(ch == KEY_RIGHT)
            {
                // Move selection right
                for (u32 i = 0; i < ICONCOUNT; i++)
                {
                    if (icons[i] == tempIcon)
                    {
                        tempIcon = icons[(i + 1) % ICONCOUNT]; // wrap around using modulo
                        break;
                    }
                }
            }
            else if(ch == '\n')
            {
                // Confirm selection
                p.setIcon(tempIcon);
                break;
            }
            clear();
        }
        clear();
    }
    ch = getch();
    f.printText("LEVEL 1: EASY");
    f.printText("PRESS ENTER TO CONTINUE...");
    ch = getch();
    while ((ch = getch()) != '\n') {} // wait for enter key
    clear();

    Level level1(1, p);
    level1.simulateGame();
    
    shutdownTerminal();
    return EXIT_SUCCESS;
}