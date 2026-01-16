#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>

#include "screen.h"
#include "player.h"
#include "properties.h"

class Level : public Screen
{
    private:
        u32 levelNumber;
        Player p;
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
         * @overload Overloads the refresh method from Screen
         */
        void refresh() override;
        
};

#endif // LEVEL_H