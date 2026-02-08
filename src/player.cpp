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

s16 Player::saveData(std::string filename)
{
    std::ofstream saveData("../data/" + filename);
    if(!saveData.is_open()) return -1; // Failure
    // Write data to file
    for(const auto& l: completedLevels) saveData << l << "\n";
    saveData.close();
    return 0;
}

void Player::loadData(std::string filename)
{
    std::ifstream saveData("../data/" + filename);
    if(!saveData.is_open()) return; // Failure/No save data
    std::string line;
    // Load data into completedLevels
    uSize idx = 0;
    while (std::getline(saveData, line))
    {
        line == "0" ? completedLevels[idx] = false : completedLevels[idx] = true;
        idx++;
    }
    saveData.close();
}