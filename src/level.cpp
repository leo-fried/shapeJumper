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
        if (lineCount == (LINES - p.getPosY()))
        {
            if (line.empty()) levelData[lineCount].insert(0 ," ");
            // Player has reached end of level
            if(levelData[lineCount][0] == '[') 
            {
                levelComplete = true;
                return;
            }
            // Collision = Death
            if(levelData[lineCount][0]!= ' ' && !g_debug) 
            {
                p.setAlive(false);
                return;
            }

            levelData[lineCount].insert(0, p.getIcon());
        }
        mvprintw(lineCount, 0, "%s", levelData[lineCount].c_str());
        lineCount++;
    }
    refresh(); // refresh the screen to show changes

    // Move level by 1 space at a time for next iteration
    for(auto& line : levelData)
    {
        if(line[0] != p.getIcon()[0]) line.erase(0,1); // remove first character of each line if available besides bottom line
        else line.erase(0,2); // remove first two characters if player is present
        
    }
    
}

void Level::simulateGame()
{
    using clock = std::chrono::steady_clock;
    jumpDelay = clock::now();
    load();
    levelComplete = false;
    
    // Main level loop
    while (1)
    {
        s32 ch = getch();
        // Check if level is complete
        if(levelComplete)
        {
            p.setCompletedLevel(levelNumber - 1); // Mark level as complete
            clear();
            f.printText("LEVEL COMPLETE!!!");
            printw("\nAttempts: %s\n", std::to_string(attempts).c_str());
            f.printText("PRESS ESC...");
            while ((ch = getch()) != 27) {} // wait for escape key
            clear();
            return;
        }
        // Check for Death
        if(!p.aliveStatus())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // wait before restarting level
            attempts++;
            levelData = levelDataCpy; // Copy Original data back to indicate new attempt
            // Reset Game State
            p.setAlive(true);
            attemptFlag = true;
        }
        now = clock::now();
        if (ch == ' ')
        {
            if(!p.isJumpingStatus() && std::chrono::duration_cast<std::chrono::milliseconds>(now - jumpDelay).count() >= 500) // Jump if space key is pressed, player is not already falling and 1s have passed since last jump)
            {
                p.setJumping(true); // allow for jump key to be held
            
                jumpDelay = clock::now();
                // loop for jump up and down
                for (u32 i = 0; i < (u32)(2.0 * ((double)p.getHeight() / (double)p.getDeltaY())); i++) // use a double cast to avoid integer division truncation then convert back to u32
                {
                    p.jump();
                    load();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control jump speed to 20 times/second
                }
            }
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            clear();
            return;
        }
        else 
        {
            p.setJumping(false); // allow for jump key to be held
            load(); // Simply reload the level
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control reload speed to 20 times/second
        }
    }
    
        
}