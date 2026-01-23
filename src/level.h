#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>

#include "screen.h"
#include "font.h"
#include "player.h"
#include "properties.h"

class Level : public Screen
{
    private:
        u32 levelNumber;
        std::vector<std::string> levelData; // Vector to load level data from disk into memory
        std::vector<std::string> levelDataCpy; // Copy of level data for when restart is necessary

        Player& p;
        u32 attempts; // Number of attempts made by the player
        bool attemptFlag = true; // Flag for attempt counter
        bool levelComplete;
        Font f; // Font for level complete message

        std::chrono::time_point<std::chrono::steady_clock> now;
        std::chrono::time_point<std::chrono::steady_clock> jumpDelay;

        /**
         * @brief Loads level data from text file and puts it into vector.
         * @param filename The file to load the data from.
         */
        void loadFromFile(std::string filename);
        /**
         * @brief Reloads level data and shifts level 20 times/second.
         */
        void load() override;

    public:
        Level(u32 number, Player* player) : levelNumber(number), p(*player), attempts(1), levelComplete(false) { loadFromFile("../assets/level" + std::to_string(number) + ".txt"); }
        ~Level() {}

        /**
         * @brief Simulates the gameplay by refreshing the screen 20 times/second.
         */
        void simulateGame() override;
        
};

#endif // LEVEL_H