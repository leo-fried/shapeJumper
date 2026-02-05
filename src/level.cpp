#include "level.h"

void Level::loadFromFile(std::string filename)
{
    std::ifstream levelFile(filename);
    if(!levelFile.is_open())
    {
        printw("Error: Could not open level file %s\n", filename.c_str());
        shutdownTerminal();
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
                // Platform
                case '_':
                {
                    // Set current platform position
                    p->setPlatformPos(LINES-lineCount);
                    if(p->getPlatformPos() == p->getPosY()) eop = false; // If player is currently falling, stop
                    if(levelData[lineCount][1] != '_') eop = true;// If next platform is not a platform, prepare to fall on next frame
                    break;
                }
                // Other
                case ' ':
                {
                    if(p->isJumpingStatus()) eop = true;
                    // End of platform, fall 
                        if(eop) 
                        {
                            p->setPlatformPos(0); // reset platform
                            if(p->isJumpingStatus()) eop = false;
                            else
                            {
                                p->setPosY(p->getPosY()-1);
                            }
                        }
                    break;
                }
                default:
                {
                    if(!g_debug) // Death 
                    {
                        p->setAlive(false);
                        return;
                    }
                    break;
                }
            }

            levelData[lineCount][0] = p->getIcon()[0]; // Place player icon on screen
        }
        // Print the current line
        mvprintw(lineCount, 0, "%s", levelData[lineCount].c_str());
        lineCount++;
    }
    refresh(); // refresh the screen to show changes

    // Move level by 1 space at a time for next iteration
    for(auto& line : levelData)
    {
        if(line.empty()) continue;
        line.erase(0,1);        
    }
    
}

std::unique_ptr<Player> Level::simulateGame()
{
    load();
    levelComplete = false;
    delay = std::chrono::steady_clock::now();
    lvlMusic.playAudio(false, 10);
    
    // Main level loop
    while (1)
    {
        now = std::chrono::steady_clock::now();
        s32 ch = getch();
        // Check if level is complete
        if(levelComplete)
        {
            clearSfx.playAudio();
            lvlMusic.stopAudio();
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
            deathSfx.playAudio();
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // wait before restarting level
            // Restart audio
            lvlMusic.restartAudio();
            lvlMusic.playAudio(false, 10);

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
                u32 currY = p->getPosY(); // Get current Y pos before jump commences

                while (p->jump(currY) == true) // jump
                {
                    load();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control jump speed to 20 times/second
                }
            }
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            clear();
            lvlMusic.stopAudio();
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