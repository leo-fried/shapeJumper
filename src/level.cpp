#include "level.h"

void Level::load(std::string filename)
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
    while (std::getline(levelFile, line))
    {
        if (lineCount > LINES) break; // prevent drawing off-screen
        if (lineCount == 5) {
            for(const auto& c : "ATTEMPT: "+ std::to_string(attempts)) line.push_back(c); // Display attempt count
        }
        if (lineCount == (LINES - p.getPosY()))
        {
            if (line.empty()) line.push_back(' ');
            line[0] = p.getIcon();
        }
    mvprintw(lineCount, 0, "%s", line.c_str());
    lineCount++;
    }

    refresh(); // refresh the screen to show changes
    levelFile.close();
}

void Level::simulateGame()
{
    load("../assets/level1.txt");
    using clock = std::chrono::steady_clock;

    levelStartTime = clock::now();
    levelComplete = false;
    
    // Main level loop
    while (1)
    {
        s32 ch = getch();
        // only allow player to jump once per second
        if (ch == ' ' && !p.isFallingStatus()) // Jump if space key is pressed and player is not already falling
        {
            // loop for jump up and down
            for (u32 i = 0; i < (u32)(2.0 * ((double)p.getHeight() / (double)p.getDeltaY())); i++) // use a double cast to avoid integer division truncation then convert back to u32
            {
                p.jump();
                load("../assets/level1.txt");
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Control jump speed to 10 times/second
            }
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            break;
        }
    }
    
        
}