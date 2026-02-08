#ifndef LEVEL_H
#define LEVEL_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map> // Coin identifying
#include <thread>
#include <vector>

#include "ball.h"
#include "font.h"
#include "player.h"
#include "properties.h"
#include "screen.h"
#include "sfx.h"
#include "ship.h"

// Data for coins

class Level : public Screen
{
    private:
        u32 levelNumber;
        std::vector<std::string> levelData; // Vector to load level data from disk into memory
        std::vector<std::string> levelDataCpy; // Copy of level data for when restart is necessary

        std::unique_ptr<Player> p;
        std::unique_ptr<Player> pCpy; // Copy of player
        //Ship* s; // Object for ship mode
        //Ball* b; // Object for ball mode
        u32 attempts; // Number of attempts made by the player
        bool attemptFlag = true; // Flag for attempt counter
        bool eop = false; // Flag for end of platform behavior
        bool levelComplete;
        Font f; // Font for level complete message

        // Sounds
        Music lvlMusic;
        Sfx deathSfx;
        Sfx clearSfx;

        bool fall = false; // flag for falling
        bool bounce = false; // flag for bounce pad


        /**
         * A map to store coins
         * Key: (size_t) the X-Position of the coin
         * Value: (bool) False if the coin has not been collected, true if it has
         */
        std::map<uSize, bool> coins; 
        uSize levelPos; // Player's position in the level

        u32 speed; // Level speed
        
        char prevChar; // stores the previous character for frame advancement

        /**
         * @brief Loads level data from text file and puts it into vector.
         * @param filename The file to load the data from.
         */
        void loadFromFile(std::string filename);
        /**
         * @brief Reloads level data and shifts level 20 times/second.
         */
        void load() override;

        void identifyCoins(const std::string& line);

    public:
        Level(u32 number, std::unique_ptr<Player> player) : levelNumber(number), p(std::move(player)), attempts(1), levelComplete(false), 
        lvlMusic("level" + std::to_string(levelNumber) + ".ogg"), deathSfx("death.wav"), clearSfx("clear.wav"), levelPos(p->getPosX()), speed(1) { loadFromFile("../assets/level" + std::to_string(number) + ".txt"); }
        ~Level() {} 


        /**
         * @brief Simulates the gameplay by refreshing the screen 20 times/second.
         * @return Returns the player to save progress
         */
        std::unique_ptr<Player> simulateGame() override;
        
};

#endif // LEVEL_H