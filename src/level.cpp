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
        // Coin found, insert into map
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
        // Player's position per frame
        if (lineCount == (LINES - p->getPosY()))
        {
            if (line.size() < p->getPosX()) for(uSize i = 0; i < p->getPosX(); i++) levelData[lineCount].insert(line.back() ," ");
            char currPos = levelData[lineCount][p->getPosX()]; // store current position
            bool gTemp = p->getGravity();
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
                    p->setGravity(gTemp);
                    p->setPlatformPos(LINES-lineCount);
                    p->setPosY(LINES-lineCount);
                    break;
                }
                // Ball Portal
                case ';':
                {
                    if(!pCpy) pCpy = std::move(p);
                    p = std::make_unique<Ball>();
                    p->setGravity(gTemp);
                    p->setPlatformPos(LINES-lineCount);
                    p->setPosY(LINES-lineCount);
                    break;
                }
                // Player Portal
                case '0':
                {
                    if(pCpy) p = std::move(pCpy);
                    p->setGravity(gTemp);
                    p->setPlatformPos(LINES-lineCount);
                    p->setPosY(LINES-lineCount);
                    break;
                }
                // Anti-grav portal
                {
                    case '^':
                    p->setGravity(true);
                    p->setPlatformPos(13);
                    break;
                }
                // Regular-grav portal
                {
                    case 'v':
                    p->setGravity(false);
                    p->setPlatformPos(0);
                    break;
                }
                // Platform
                case '_':
                {
                    // Set current platform position
                    p->setPlatformPos(LINES-lineCount);
                    break;
                }
                // Bounce pad
                case 'B':
                {
                    bounce = true;
                    p->setHeight(6); // Adjust height for bounce pad
                    break;
                }
                // Small bounce pad
                case 'b':
                {
                    bounce = true;
                    p->setHeight(2); // Adjust height for small bounce pad
                    break;
                }
                // Anti Grav bounce pad
                case 'a':
                {
                    p->setGravity(!p->getGravity()); // Reverse grav
                    break;
                }
                // 2x Speed boost
                case '2':
                {
                    speed = 2;
                    break;
                }
                case '1':
                {
                    speed = 1;
                    break;
                }
                // Coin
                case '*':
                {
                    // Erase coin from screen
                    levelData[lineCount][p->getPosX()] = ' ';
                    // Mark coin as collected in map
                    for(auto& c : coins)
                    {
                        if(c.first == levelPos) { c.second = true; }
                        
                    }
                    // Treat as platform if platform is next
                    if(levelData[lineCount][p->getPosX() + 1] == '_') p->setPlatformPos(LINES-lineCount);
                    break;
                }
                // empty space, reset platform
                case ' ':
                {
                    p->setPlatformPos(p->getGravity() ? 13 : 0); // Set platform depending on gravity
                    break;
                }
                // Death collision (Not in debug mode)
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
            // Rendering
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
        if(line[p->getPosX() - 2] == p->getIcon()[0]) line[p->getPosX() - 2] = prevChar;        
    }
    levelPos+= speed; // Iterate position in level by speed
    // Update percent 
    percent = (float)levelPos * 100.0f / (totalLevel * 20.0f);
    
}

std::unique_ptr<Player> Level::simulateGame()
{
    load();
    levelComplete = false;
    lvlMusic.playAudio(false, 10);
    
    // Main level loop
    while (1)
    {
        // Get user input
        s32 ch = getch();
        // Check if level is complete
        if(levelComplete)
        {
            clearSfx.playAudio(50.f);
            lvlMusic.stopAudio();
            clear();
            f.printText("LEVEL COMPLETE!!!");
            printw("\nAttempts: %s\n", std::to_string(attempts).c_str());
            std::string coinSummary = " ";
            u32 idx = 0;
            for(const auto& c : coins)
            {
                if(c.second) 
                {
                    coinSummary += '*';
                    p->setCoin(levelNumber -1, idx); // Set coins
                }
                else coinSummary += '_';
                coinSummary += ' ';
                idx++;
            }
            // Print coins collected on this attempt
            printw("Coins collected:%s\n", coinSummary.c_str());
            f.printText("PRESS ESC...");

            p->setCompletedLevel(levelNumber - 1); // Mark level as complete
            p->setTotalAttempts(levelNumber - 1, 1); // Add to attempt total
            p->setlevelPct(levelNumber - 1, 100); // Set percentage as 100%
            p->saveData(levelNumber); // Save data

            while ((ch = getch()) != 27) {} // wait for escape key
            clear();
            if(pCpy) p = std::move(pCpy);
            p = std::make_unique<Player>();
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

            // Update attempts and percent as needed
            p->setTotalAttempts(levelNumber -1, 1);
            if((u16)percent > p->getlevelPct(levelNumber -1)) p->setlevelPct(levelNumber - 1, (u16)percent);
            p->saveData(levelNumber); // Save data

            // Reset Game State
            for(auto& c : coins) c.second = false;
            levelPos = p->getPosX();
            if(pCpy) p = std::move(pCpy);
            p->setAlive(true);
            attemptFlag = true;
        }
        // Player jump/Bounce pad
        if (ch == ' ' || bounce)
        {
            if(!p->isJumpingStatus()) // Jump if space key is pressed and player is not already jumping
            {
                p->setJumping(true); // allow for jump key to be held
                u32 currY = p->getPosY(); // Get current Y pos before jump commences
                

                while (bounce ? p->Player::jump(currY): p->jump(currY) == true) // jump/bounce logic (If bounce is true just do a normal player jump)
                {
                    load();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control jump speed to 20 times/second
                }
                if(bounce) 
                {
                    bounce = false;
                    p->setHeight(p->getDefaultHeight()); // Reset height after bounce
                }
            }
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            p->setTotalAttempts(levelNumber - 1, 1); // Add to attempt total
            p->saveData(levelNumber); // Save data
            clear();
            lvlMusic.stopAudio();
            if(pCpy) p = std::move(pCpy);
            p = std::make_unique<Player>();
            return std::move(p);
        }
        else 
        {
            p->setJumping(false); // allow for jump key to be held
            // Ensure screen refreshes at least once, but continue to refresh as player falls
            do
            {
                load();
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control reload speed to 20 times/second
            } while(p->fall() == true);
        }
    }     
}