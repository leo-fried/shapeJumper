#ifndef LEVEL_H
#define LEVEL_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include "ball.h"
#include "font.h"
#include "player.h"
#include "properties.h"
#include "screen.h"
#include "sfx.h"
#include "ship.h"

class Level : public Screen
{
    private:
        u32 levelNumber;
        u32 speed; // Level speed
        std::vector<std::string> levelData; // Vector to load level data from disk into memory
        std::vector<std::string> levelDataCpy; // Copy of level data for when restart is necessary

        std::unique_ptr<Player> p;
        std::unique_ptr<Player> pCpy; // Copy of player
        u32 attempts; // Number of attempts made by the player
    
        Font f; // Font object

        // Sounds
        Music lvlMusic;
        Sfx deathSfx;
        Sfx clearSfx;

        // Percentage data
        float totalLevel; // Total level time in seconds
        float percent; // Level Percentage 
        uSize levelPos; // Player's position in the level

        //Flags
        bool attemptFlag = true; // Flag for attempt counter
        bool levelComplete; // Flag for level completion
        bool fall = false; // flag for falling
        bool bounce = false; // flag for bounce pad

        /**
         * A map to store coins
         * Key: (size_t) the X-Position of the coin
         * Value: (bool) False if the coin has not been collected, true if it has
         */
        std::map<uSize, bool> coins; 
        
        char prevChar; // stores the previous character for proper rendering

        /**
         * @brief Loads level data from text file and puts it into vector.
         * @param filename The file to load the data from.
         */
        void loadFromFile(std::string filename);

        /**
         * @brief Reloads level data and shifts level 20 times/second.
         */
        void load() override;

        /**
         * @brief Identifies coin positions in the level and sorts them in the coins map by order of appearance.
         * @param line The line in the level where the coin appears.
         */
        void identifyCoins(const std::string& line);

    public:
        /**
         * @brief Default Level Constructor.
         * @param number The number associated with the level.
         * @param player The player object to be used in the level.
         */
        Level(u32 number, std::unique_ptr<Player> player) : levelNumber(number), speed(1), p(std::move(player)), attempts(1), lvlMusic("level" + std::to_string(levelNumber) + ".ogg"), deathSfx("death.wav"), clearSfx("clear.wav"), 
        totalLevel(lvlMusic.getLength()), levelPos(p->getPosX()), levelComplete(false) { loadFromFile("../assets/level" + std::to_string(number) + ".txt"); }
        
        /**
         * @brief Default Level Destructor
         */
        ~Level() {}

        /**
         * @brief Simulates the gameplay by refreshing the screen 20 times/second.
         * @return Returns the player to save progress
         */
        std::unique_ptr<Player> simulateGame() override;
};

#endif // LEVEL_H