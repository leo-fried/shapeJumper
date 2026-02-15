#include "font.h"
#include "level.h"
#include "properties.h"
#include "sfx.h"

s32 main (s32 argc, char** argv)
{
    // program args
    if(argc == 2)
    {
            // Debug mode (Unlocks all levels and disables collision)
            if(std::string(argv[1]) == "--debug")
            {
                g_debug = true;
                std::cout << "Debug mode activated.\n";
            }
            else if(std::string(argv[1]) == "--version") 
            {
                std::cout <<"Shape Jumper version 1.0.0 Copyright (c) 2026 Leo Friedman\n";
                return EXIT_SUCCESS;
            }
            else if(std::string(argv[1]) == "--help")
            {
                std::cout << "Use the arrow keys to scroll through the levels.\nPress space to jump or esc to exit the current level.\nYour goal is to complete each level in as few attempts as possible (BONUS: try to collect all 3 secret coins '*' in each level).\n The '?' turns you into a ship which falls down unless you hit space and the ';' turns you into a ball which changes gravity when you hit space. '0' turns you back into your normal player.\n'^' enables anti-gravity and 'v' re-enables normal gravity. 'B' is a large bounce pad and 'b' is a small bounce pad, whereas 'a' will flip your current gravity.\n '2' doubles your speed and '1' sets it back to normal.\n";
                return EXIT_SUCCESS;
            }
    }

    initTerminal();

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
            switch(currLevel)
            {
                case 0:
                {
                    f.printText("SWING RABBIT");
                    f.printText("PRESS ENTER TO CONTINUE...");
                    p->printStats(0);
                    break;
                }
                case 1:
                {
                    f.printText("DRAGON CASTLE");
                    if(p->getCompletedLevel(0) || g_debug) 
                    {
                        f.printText("PRESS ENTER TO CONTINUE...");
                        p->printStats(1);
                    }
                    else f.printText("LOCKED...");
                    break;
                }
                case 2:
                {
                    f.printText("SAMURAI");
                    if((p->getCompletedLevel(0) && p->getCompletedLevel(1)) || g_debug)
                    {
                        f.printText("PRESS ENTER TO CONTINUE...");
                        p->printStats(2);
                    }
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
                switch(currLevel)
                {
                    case 0:
                    {
                        Level level1(1, std::move(p));
                        menuMusic.stopAudio();
                        p = level1.simulateGame(); // Return player after level is finished
                        menuMusic.playAudio(true); // Restart music
                        break;
                    }
                    case 1:
                    {
                        if(p->getCompletedLevel(0) || g_debug)
                        {
                            Level level2(2, std::move(p));
                            menuMusic.stopAudio();
                            p = level2.simulateGame();
                            menuMusic.playAudio(true); // Restart music
                        }
                        break;
                    }
                    case 2:
                    {
                        if((p->getCompletedLevel(0) && p->getCompletedLevel(1)) || g_debug)
                        {
                            Level level3(3, std::move(p));
                            menuMusic.stopAudio();
                            p = level3.simulateGame();
                            menuMusic.playAudio(true); // Restart music
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

