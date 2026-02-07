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
        identifyCoins(line);
    }
    levelFile.close();
    levelDataCpy = levelData;
}

void Level::identifyCoins(const std::string& line)
{
    uSize idx = 0;
    for(const auto&c : line)
    {
        if(c == '*') 
        {
            coins.insert({idx, false});
        }
        idx++;
    }
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
            std::string at = "ATTEMPT "+std::to_string(attempts); // Attempt string
            u8 idx = 0;
            for(const auto& a: at)
            {
                levelData[lineCount][28 + idx] = a;
                idx++;
            }
            attemptFlag = false;
        }
        if (lineCount == (LINES - p->getPosY()))
        {
            if (line.size() < p->getPosX()) for(uSize i = 0; i < p->getPosX(); i++) levelData[lineCount].insert(line.back() ," ");
            char currPos = levelData[lineCount][p->getPosX()];
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
                    if(levelData[lineCount][p->getPosX() + 1] != '_') eop = true;// If next platform is not a platform, prepare to fall on next frame
                    break;
                }
                // Bounce pad
                case 'B':
                {
                    bounce = true;
                    p->setHeight(6); // Adjust height for bounce pad
                    break;
                }
                // Coin
                case '*':
                {
                    // Erase coin from screen
                    levelData[lineCount][p->getPosX()] = ' ';
                    for(auto& c : coins)
                    {
                        if(c.first == levelPos) { c.second = true; }
                        
                    }
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
                               fall = true;
                               p->setFalling(true);
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
            prevChar = levelData[lineCount][p->getPosX()];
            levelData[lineCount][p->getPosX()] = p->getIcon()[0]; // Place player icon on screen
        }
        // Print the current line
        mvprintw(lineCount, 0, "%s", levelData[lineCount].c_str());
        lineCount++;
    }
    refresh(); // refresh the screen to show changes

    // Move level by speed space(s) at a time for next iteration
    for(auto& line : levelData)
    {
        if(line.size() < p->getPosX()) continue;
        
        line.erase(0,speed);
        if(line[p->getPosX() - 1] == p->getIcon()[0]) line[p->getPosX() - 1] = prevChar;        
    }
    levelPos+= speed; // Iterate position in level by speed
    
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
            clearSfx.playAudio(50.f);
            lvlMusic.stopAudio();
            p->setCompletedLevel(levelNumber - 1); // Mark level as complete
            clear();
            f.printText("LEVEL COMPLETE!!!");
            printw("\nAttempts: %s\n", std::to_string(attempts).c_str());
            std::string coinSummary = " ";
            for(const auto& c : coins)
            {
                if(c.second == true) coinSummary += '*';
                else coinSummary += '_';
                coinSummary += ' ';
            }
            printw("Coins collected:%s\n", coinSummary.c_str());
            f.printText("PRESS ESC...");
            while ((ch = getch()) != 27) {} // wait for escape key
            clear();
            return std::move(p);
        }
        // Check for Death
        if(!p->aliveStatus())
        {
            deathSfx.playAudio(33.3f);
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
        if (ch == ' ' || bounce || fall)
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
                if(fall) fall = false;
                if(bounce) 
                {
                    bounce = false;
                    p->setHeight(p->getDefaultHeight()); // Reset height after bounce
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