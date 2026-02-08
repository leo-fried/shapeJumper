#include "player.h"

bool Player::jump(u32 y)
{
    posY += deltaY;
    if (posY >= height + y) 
    {
        posY = height + y; // Clamp height
        return false;
    }
    return true;
}

bool Player::fall()
{
    if(posY > platformPos)  { posY-= deltaY; return true; }
    posY = platformPos;
    return false;
}

s16 Player::saveData(u32 levelNum)
{
    std::ofstream saveData("../data/level" + std::to_string(levelNum) + ".txt");
    if(!saveData.is_open()) return -1; // Failure
        
    // Save if level has been completed
    saveData << completedLevels[levelNum - 1];
    // Save coins
    saveData << "\n" << coinsCollected[levelNum -1];
    // Save attempts
    saveData << "\n" << totalAttempts[levelNum - 1];
    //TODO: Implement percentage

    saveData.close();
    return 0;
}

void Player::loadData()
{
    for(uSize i = 0; i < LEVELCOUNT; i++)
    {
        std::ifstream data("../data/level" + std::to_string(i+1) + ".txt");
        if(!data.is_open()) continue; // Failure/No save data (move onto next level)
        std::string line;
        // Load data into completedLevels
        uSize lineCount = 0;
        while (std::getline(data, line))
        {
            switch (lineCount)
            {
                // Is level complete?
                case 0:
                {
                    completedLevels[i] = line == "0" ? false : true;
                    break; 
                }
                // What coins have been collected?
                case 1:
                {
                    coinsCollected[i] = line;
                    break; 
                }
                // How many total attempts have there been?
                case 2:
                {
                    totalAttempts[i] = stoi(line);
                    break; 
                }
                /* TODO: Implement Percentage
                case 0:
                {
                break; 
                }
                */
            }
            lineCount++;
        }
        data.close();
    }
}