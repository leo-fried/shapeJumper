#include "level.h"

void Level::loadLevel(std::string filename)
{
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
        if(lineCount != LINES) printw("%s\n", line.c_str());
        else 
        {
            char icon = p.getIcon();
            // Print icon at the start of the line
            line[10] = icon; // Place the icon in the level
            printw("%s\n", line.c_str());
        }
        lineCount++;
    }
    levelFile.close();
}

void Level::refresh()
{
    // Main level loop
    loadLevel();
    using clock = std::chrono::steady_clock;

    levelStartTime = clock::now();
    levelComplete = false;
    
    while (1)
    {
        int ch = getch();

        if (ch == ' ')
        {
            printw("Jump!\n");
        }
        else if (ch == 27) // Quit if escape key is pressed
        {
            break;
        }
        now = clock::now();
        if (!levelComplete &&
            std::chrono::duration_cast<std::chrono::seconds>(now - levelStartTime).count() >= 5)
        {
            printw("Level Complete!\n");
            break;
        }
    }
        
}