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

void Player::saveData(u32 levelNum)
{
    std::ofstream saveData("../data/level" + std::to_string(levelNum) + ".txt");
    if(!saveData.is_open()) return; // Failure
        
    // Save if level has been completed
    saveData << completedLevels[levelNum - 1];
    // Save coins
    saveData << "\n";
    for(const auto& c: coinsCollected[levelNum -1]) saveData << std::to_string(c);
    // Save attempts
    saveData << "\n" << totalAttempts[levelNum - 1];
    // Save Percentage
    saveData << "\n" << levelPct[levelNum - 1];
    saveData.close();
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
                    std::vector<u16> temp;
                    for(const auto& c: line) temp.push_back(c == '1' ? 1 : 0);
                    coinsCollected[i] = temp;
                    break; 
                }
                // How many total attempts have there been?
                case 2:
                {
                    totalAttempts[i] = stoi(line);
                    break; 
                }
                // What is the best percentage?
                case 3:
                {
                    levelPct[i] = stoi(line);
                    break; 
                }
            }
            lineCount++;
        }
        data.close();
    }
}

std::string Player::printCoins(u32 idx)
{
    std::string temp; 
    for(const auto& c: coinsCollected[idx]) 
    {
        char ch = c == 1 ? '*' : '_'; 
        temp.push_back(ch);
        temp.push_back(' ');
    }
    return temp;
}