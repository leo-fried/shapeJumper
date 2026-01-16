#include "level.h"

void Level::loadLevel(std::string filename)
{
    u32 lineCount = 0;
    u32 LINES = 13; // Number of lines that fit on screen
    std::ifstream levelFile(filename);
    if(!levelFile.is_open())
    {
        std::cerr << "Error: Could not open level file " << filename << "\n";
        return;
    }
    std::string line;
    while(std::getline(levelFile, line))
    {
        if(lineCount != LINES) std::cout << line << "\n";
        else 
        {
            char icon = p.getIcon();
            // Print icon at the start of the line
            line[10] = icon; // Place the icon in the level
            std::cout << line;
        }
        lineCount++;
    }
    levelFile.close();
}

void Level::refresh()
{
    // Main level loop
    loadLevel();
    while(1)
    {
        // If user presses enter, let player jump
        std::cin.get();
        p.jump(1, 100);
    }
}