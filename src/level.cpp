#include "level.h"

void Level::loadLevel(std::string filename)
{
    clear(); // Clear current display before reloading level

    u32 lineCount = 0;
    u32 LINES = 13; // Number of lines that fit on screen
    std::ifstream levelFile(filename);
    if(!levelFile.is_open())
    {
        printw("Error: Could not open level file %s\n", filename.c_str());
        return;
    }
    std::string line;
    while(std::getline(levelFile, line))
    {
        if(lineCount != (LINES - p.getPosY())) printw("%s\n", line.c_str()); // draw the level normally except for the player line
        else 
        {
            char icon = p.getIcon();
            // Print icon at the start of the line
            if(line.length() > 0) line[0] = icon; // Place the icon in the level
            else line.push_back(icon);
            printw("%s\n", line.c_str());
        }
        lineCount++;
    }
    refresh(); // refresh the screen to show changes
    levelFile.close();
}

void Level::simulateGame()
{
    loadLevel();
    using clock = std::chrono::steady_clock;

    levelStartTime = clock::now();
    levelComplete = false;
    
    // Main level loop
    while (1)
    {
        int ch = getch();
        // only allow player to jump once per second
        if (ch == ' ' && !p.isFallingStatus()) // Jump if space key is pressed and player is not already falling
        {
            // loop for jump up and down
            for (u32 i = 0; i < (u32)(2.0 * ((double)p.getHeight() / (double)p.getDeltaY())); i++) // use a double cast to avoid integer division truncation then convert back to u32
            {
                p.jump();
                loadLevel();
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Control jump speed to 10 times/second
            }
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            break;
        }
        /*
        loadLevel(); // Refresh level display
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); // Control refresh rate to 30 times/second
        now = clock::now();
        if (!levelComplete && std::chrono::duration_cast<std::chrono::seconds>(now - levelStartTime).count() >= 20)
        {
            printw("Level Complete!\n");
            //break;
        }
        */
    }
    
        
}