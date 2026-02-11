#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>


#include "properties.h"

const uSize LEVELCOUNT = 3; // Number of levels in-game

class Player
{
    private:
        u32 posX;
        std::string icons[8] = {"@", "!", "%", "&", "$", "M", "8", "+"}; // available icons
        const u32 ICONCOUNT = 8;
        
        bool completedLevels[LEVELCOUNT]; // tracks levels that the player has completed
        std::vector<u16> coinsCollected[LEVELCOUNT]; // Tracks coins collected
        u32 totalAttempts[LEVELCOUNT]; // Tracks total attempts in the level
        u16 levelPct[LEVELCOUNT]; // Tracks best percent achieved in the level

        bool alive;
        u32 deltaY; // Change in Y pos per jump
        // Jump data
        const u32 DEFAULT_HEIGHT = 4;
        u32 height; // max jump height
        bool isJumping; // whether the player is currently jumping

        /**
         * @brief Loads the player's data for each level
         */
        void loadData();

        /**
         * @brief converts coin data to readable string (0 -> _, 1 -> *).
         * @param idx The level index for what coin data to convert.
         * @return The coin data in the readable string.
         */
        std::string printCoins(u32 idx);

    protected:
        u32 posY;
        u32 platformPos = 0;
        std::string icon; // Player icon
        bool gravity = false; // false for normal gravity, true for anti gravity

    public:
        Player() : posX(10), completedLevels{false, false, false}, coinsCollected{{0,0,0}, {0,0,0}, {0,0,0}}, totalAttempts{0,0,0}, levelPct{0,0,0}, alive(true), deltaY(1), height(DEFAULT_HEIGHT), isJumping(false), posY(0), icon("@") { loadData(); }

        virtual ~Player() {}

        /**
         * @brief Gets the player's icon.
         * @return The character representing the player's icon.
         */
        std::string getIcon() {return icon;}
 
        /**
         * @brief Sets the player's icon.
         * @param c The character to set as the player's icon.
         */
        void setIcon(std::string c) {icon = c;} 

        /**
         * @brief Gets all available player icons.
         * @return The strings that contain the icons.
         */
        std::string* getAvailableIcons() {return icons;}
        /**
         * @brief Returns the number of icons available.
         * @return The number of icons.
         */
        u32 getIconCount() {return ICONCOUNT;}

        /**
         * @brief Gets the player's gravity
         * @return False if in normal gravity, true in anti-gravity
         */
        bool getGravity() { return gravity; }

        /**
         * @brief Sets the player's gravity
         * @param g The gravity to set (false = normal, true = anti)
         */
        void setGravity(bool g) { gravity = g; }

        /**
         * @brief Gets the player's X position.
         * @return The X position of the player.
         */
        u32 getPosX() {return posX;}

        /**
         * @brief Sets the player's X position.
         * @param x The X position to set.
         */
        void setPosX(u32 x) {posX = x;}


        /**
         * @brief Gets the player's Y position.
         * @return The Y position of the player.
         */
        u32 getPosY() {return posY;}

        /**
         * @brief Sets the player's Y position.
         * @param y The Y position to set.
         */
        void setPosY(u32 y) {posY = y;}

        /**
         * @brief Gets the current platform position.
         * @return The current platform position.
         */
        u32 getPlatformPos() {return platformPos;}

        /**
         * @brief Sets the current platform position.
         * @param y The Y position to set.
         */
        void setPlatformPos(u32 y) {platformPos = y;}

        /**
         * @brief Gets the player's current jump height.
         * @return The player's current jump height.
         */
        u32 getDeltaY() {return deltaY;}
        /**
         * @brief Sets the player's jump height.
         * @param dy The jump height to set.
         */
        void setDeltaY(u32 dy) {deltaY = dy;}

        /**
         * @brief Gets the player's current max jump height.
         * @return The player's current max jump height.
         */
        u32 getHeight() {return height;}
        /**
         * @brief Sets the player's max jump height.
         * @param h The max jump height to set.
         */
        void setHeight(u32 h) {height = h;}

        /**
         * @brief Gets the player's default max jump height.
         * @return The player's default max jump height.
         */
        u32 getDefaultHeight() { return DEFAULT_HEIGHT; }

        /**
         * @brief Gets the player's current jumping status.
         * @return True if the player is currently jumping, false otherwise.
         */
        bool isJumpingStatus() {return isJumping;}
        /**
         * @brief Sets the player's jumping status.
         * @param jumping The jumping status to set (true = player is jumping, false = player is not jumping).
         */
        void setJumping(bool jumping) { isJumping = jumping; }

        /**
         * @brief Gets the player's alive status.
         * @return True if the player is alive, false if they are dead.
         */
        bool aliveStatus() { return alive; }
        /**
         * @brief Sets the player's alive status.
         * @param a The alive status to set (true = player is alive, false = player is dead).
         */
        void setAlive(bool a) {alive = a; }

        /**
         * @brief Gets whether the player has completed a level.
         * @param idx The index of the level to check.
         * @return True if the player has completed the level, false otherwise.
         */
        bool getCompletedLevel( u32 idx ) { return completedLevels[idx]; }
        /**
         * @brief Sets a level as completed for the player.
         * @param idx The index of the level to set as completed.
         */
        void setCompletedLevel( u32 idx ) { completedLevels[idx] = true; }

        /**
         * @brief Gets whether the player has collected a coin.
         * @param idx The index of the level to check.
         * @param idx2 The index of the coin to check.
         * @return True if the player has collected the coin, false otherwise.
         */
        u16 getCoin( u32 idx, u32 idx2 ) { return coinsCollected[idx][idx2]; }
        /**
         * @brief Sets a coin as collected for the player.
         * @param idx The index of the level to set the coin in.
         * @param idx2 The index of the coin to set as collected.
         */
        void setCoin( u32 idx, u32 idx2 ) { coinsCollected[idx][idx2] = 1; }

        /**
         * @brief Gets the total attempts the player has made in a level.
         * @param idx The index of the level to check.
         * @return The total attempts the player has made in the level.
         */
        u32 getTotalAttempts( u32 idx ) { return totalAttempts[idx]; }
        /**
         * @brief Sets the total attempts the player has made in a level.
         * @param idx The index of the level to set attempts in.
         * @param attempts The number of attempts to set (This is added to the total attempts).
         */
        void setTotalAttempts( u32 idx, u32 attempts ) { totalAttempts[idx] += attempts; }

        /**
         * @brief Gets the best percentage the player has achieved in a level.
         * @param idx The index of the level to check.
         * @return The best percentage the player has achieved in the level.
         */
        u16 getlevelPct( u16 idx ) { return levelPct[idx]; }
        /**
         * @brief Sets the best percentage the player has achieved in a level.
         * @param idx The index of the level to set percentage in.
         * @param pct The percentage to set as the best percentage.
         */
        void setlevelPct( u16 idx, u16 pct ) { levelPct[idx] = pct; }

        /**
         * @brief Makes the player jump.
         * @return True if jump is incomplete, false if jump is complete
         * @param y The Y position to jump from (default, 0). Used for calculating jump height when jumping from platforms.
         */
        virtual bool jump(u32 y = 0);

        /**
         * @brief Causes the player to fall
         * @return True if player is still falling, false if they have finished falling
         */
        virtual bool fall();

        /**
         * @brief Saves the player's data to a file in the ../data directory".
         * @param levelNum The level number to save to (Each level number corresponds to a levelN.txt data file).
         * @return 0 if successful, -1 if unsuccessful
         */
        void saveData(u32 levelNum);

        /**
         * @brief Prints a level's stats including best percent, coins collected and total attempts.
         * @param levelNum The levelNumber pertaining to the stats that should print.
         */
        void printStats(u32 levelNum) { printw("Best: %i%% Coins collected: %s Total Attempts: %d\n", getlevelPct(levelNum), printCoins(levelNum).c_str(), getTotalAttempts(levelNum)); }
};

#endif // PLAYER_H