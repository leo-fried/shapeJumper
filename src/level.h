#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

#include "player.h"
#include "properties.h"

class Level
{
    private:
        u32 levelNumber;
        Player p;
        std::chrono::time_point<std::chrono::steady_clock> levelStartTime;
        bool levelComplete;
        std::chrono::time_point<std::chrono::steady_clock> now;
        /**
         * @brief Loads level data from text file.
         * @param filename The leveldata to load. Default: Level 1
         */
        void loadLevel(std::string filename = "../assets/level1.txt");
    public:
        Level(u32 number) : levelNumber(number) {}
        ~Level() {}

        /**
         * @brief Simulates the gameplay by refreshing the screen X times/second.
         */
        void refresh();
        
};

#endif // LEVEL_H