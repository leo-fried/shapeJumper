#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

#include "screen.h"
#include "player.h"
#include "properties.h"

class Level : public Screen
{
    private:
        u32 levelNumber;
        Player p;
        u32 attempts; // Number of attempts made by the player
        std::chrono::time_point<std::chrono::steady_clock> levelStartTime;
        bool levelComplete;
        std::chrono::time_point<std::chrono::steady_clock> now;
        /**
         * @brief Loads level data from text file.
         * @param filename The leveldata to load. Default: Level 1
         */
        void load(std::string filename);
    public:
        Level(u32 number, Player player) : levelNumber(number), p(player), attempts(0) {}
        ~Level() {}

        /**
         * @brief Simulates the gameplay by refreshing the screen X times/second.
         */
        void simulateGame();
        
};

#endif // LEVEL_H