#include "font.h"
#include "level.h"
#include "properties.h"
#include "sfx.h"

int main (int argc, char** argv)
{
    initTerminal();

    // Debug mode (Unlocks all levels and disables collision)
    if(argc == 2)
    {
        if(std::string(argv[1]) != "--debug") { shutdownTerminal(); std::cerr << "Usage: " << argv[0] << " [--debug]" << std::endl; return EXIT_FAILURE; }
        g_debug = true;
        printw("Debug mode activated.\n");
    }

    // Objects
    Font f;
    Music menuMusic("title.ogg");
    std::unique_ptr<Player> p = std::make_unique<Player>();
    std::string* icons = p->getAvailableIcons();
    const u32 ICONCOUNT = p->getIconCount();
    const u32 LEVELCOUNT = 3;
    u32 currLevel = 0;
    menuMusic.playAudio(true);
    // Game Start
    while(1)
        {
        printw("Press \"C\" to select character\n");
        f.printText("WELCOME TO SHAPE JUMPER!");
        f.printText("PRESS ENTER TO START...");
        s32 ch = getch();
        while ((ch = getch()) != '\n' && ch != 'c' && ch != 'C') {} // wait for enter key or c key
        clear();
        if (ch == 'c' || ch == 'C') {
            
            std::string tempIcon = icons[0];
            while(1)
            {
                f.printText("SELECT CHARACTER W ARROWS:");
                printw("\nCurrent Character: %s\n", tempIcon.c_str());
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
                    p->setIcon(tempIcon);
                    break;
                }
                clear();
            }
            clear();
        }
        // level select
        while(1)
        {
            clear();
            menuMusic.playAudio(true); // If title music not playing, play it
            switch(currLevel)
            {
                case 0:
                {
                    f.printText("LEVEL 1: EASY");
                    f.printText("PRESS ENTER TO CONTINUE...");
                    break;
                }
                case 1:
                {
                    f.printText("LEVEL 2: MEDIUM");
                    if(p->getCompletedLevel(0) || g_debug) f.printText("PRESS ENTER TO CONTINUE...");
                    else f.printText("LOCKED...");
                    break;
                }
                case 2:
                {
                    f.printText("LEVEL 3: HARD");
                    if((p->getCompletedLevel(0) && p->getCompletedLevel(1)) || g_debug) f.printText("PRESS ENTER TO CONTINUE...");
                    else f.printText("LOCKED...");
                    break;
                }
                default:
                {
                    printw("Unknown error. Closing program...");
                    return EXIT_FAILURE;
                    break;
                }
            }
            ch = getch();
            while ((ch = getch()) != '\n' && ch != KEY_LEFT && ch != KEY_RIGHT && ch != 27) {} // wait for enter/esc key or arrow keys
            if(ch == KEY_LEFT && currLevel > 0) currLevel--;
            else if(ch == KEY_RIGHT && currLevel < LEVELCOUNT - 1) currLevel++;
            else if(ch == 27) 
            {
                clear();
                break;
            }
            else if(ch == '\n')
            {
                // Confirm selection
                clear();
                // Stop title screen audio
                menuMusic.stopAudio();
                switch(currLevel)
                {
                    case 0:
                    {
                        Level level1(1, std::move(p));
                        p = level1.simulateGame(); // Return player after level is finished
                        break;
                    }
                    case 1:
                    {
                        if(p->getCompletedLevel(0) || g_debug)
                        {
                            Level level2(2, std::move(p));
                            p = level2.simulateGame();
                        }
                        break;
                    }
                    case 2:
                    {
                        if((p->getCompletedLevel(0) && p->getCompletedLevel(1)) || g_debug)
                        {
                            Level level3(3, std::move(p));
                            p = level3.simulateGame();
                        }
                        break;
                    }
                    default:
                    {
                        printw("Unknown error. Closing program...");
                        return EXIT_FAILURE;
                    }
                }
                
            }
            clear();
        }
        
    }
    menuMusic.stopAudio(); // Stop Menu music if it hasn't already
    shutdownTerminal();
    return EXIT_SUCCESS;
}

