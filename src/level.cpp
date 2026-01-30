#include "level.h"

void Level::loadFromFile(std::string filename)
{
    std::ifstream levelFile(filename);
    if(!levelFile.is_open())
    {
        printw("Error: Could not open level file %s\n", filename.c_str());
        exit(-1); // quit the program with an error
    }
    std::string line;
    // Load data into memory
    while (std::getline(levelFile, line))
    {
        levelData.push_back(line);
    }
    levelFile.close();
    levelDataCpy = levelData;
}

void Level::load()
{
    clear(); // Clear current display before reloading level
    u32 lineCount = 0;
    u32 LINES = levelData.size()-1; // Number of lines that fit on screen
    for(const auto& line : levelData)
    {
        if (lineCount > LINES) break; // prevent drawing off-screen
        if (lineCount == 5 && attemptFlag) 
        {
            levelData[lineCount].insert(0, "                            ATTEMPT " + std::to_string(attempts));// Display attempt count
            attemptFlag = false;
        }
        if (lineCount == (LINES - p->getPosY()))
        {
            if (line.empty()) levelData[lineCount].insert(0 ," ");
            char currPos = levelData[lineCount][0];
            // Collision Logic
            switch (currPos)
            {
                // Player has reached end of level
                case '[': 
                {
                    levelComplete = true;
                    return;
                }
                // Ship Portal
                case '?':
                {
                    if(!pCpy) pCpy = std::move(p);
                    p = std::make_unique<Ship>();
                    break;
                }
                // Ball Portal
                case ';':
                {
                    if(!pCpy) pCpy = std::move(p);
                    p = std::make_unique<Ball>();
                    break;
                }
                // Player Portal
                case '0':
                {
                    if(pCpy) p = std::move(pCpy);
                    break;
                }
                // Other
                default:
                {
                    if (g_debug || currPos == ' ') break; // Not a death
                    else // Death 
                    {
                        p->setAlive(false);
                        return;
                    }
                }
            }

            levelData[lineCount].insert(0, p->getIcon());
        }
        mvprintw(lineCount, 0, "%s", levelData[lineCount].c_str());
        lineCount++;
    }
    refresh(); // refresh the screen to show changes

    // Move level by 1 space at a time for next iteration
    for(auto& line : levelData)
    {
        if(line.empty()) continue;
        if(line[0] != p->getIcon()[0]) line.erase(0,1); // remove first character of each line if available besides bottom line
        else line.erase(0,2); // remove first two characters if player is present
        
    }
    
}

std::unique_ptr<Player> Level::simulateGame()
{
    load();
    levelComplete = false;
    delay = std::chrono::steady_clock::now();
    
    // Main level loop
    while (1)
    {
        now = std::chrono::steady_clock::now();
        s32 ch = getch();
        // Check if level is complete
        if(levelComplete)
        {
            p->setCompletedLevel(levelNumber - 1); // Mark level as complete
            clear();
            f.printText("LEVEL COMPLETE!!!");
            printw("\nAttempts: %s\n", std::to_string(attempts).c_str());
            f.printText("PRESS ESC...");
            while ((ch = getch()) != 27) {} // wait for escape key
            clear();
            return std::move(p);
        }
        // Check for Death
        if(!p->aliveStatus())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // wait before restarting level
            attempts++;
            levelData = levelDataCpy; // Copy Original data back to indicate new attempt
            // Reset Game State
            p->setAlive(true);
            attemptFlag = true;
        }
        if (ch == ' ')
        {
            if(!p->isJumpingStatus()) // Jump if space key is pressed and player is not already jumping
            {
                delay = std::chrono::steady_clock::now();
                p->setJumping(true); // allow for jump key to be held
                while (p->jump() == true) // jump
                {
                    load();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control jump speed to 20 times/second
                }
            }
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            clear();
            return std::move(p);
        }
        else 
        {
            p->setJumping(false); // allow for jump key to be held
            if(now - delay > std::chrono::milliseconds(250)) p->fall();
            load(); // Simply reload the level
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control reload speed to 20 times/second
        }
    }
    
        
}