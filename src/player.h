#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <iostream>
#include <iterator>


#include "properties.h"

const uSize LEVELCOUNT = 3; // Number of levels in-game

class Player
{
    private:
        u32 posX;
        std::string icons[8] = {"@", "!", "%", "&", "$", "M", "8", "+"}; // available icons
        const u32 ICONCOUNT = 8;
        
        bool completedLevels[LEVELCOUNT]; // tracks levels that the player has completed
        std::string coinsCollected[LEVELCOUNT];
        u32 totalAttempts[LEVELCOUNT];

        u32 platformPos;
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

    protected:
        u32 posY;
        u32 newPlatformPos; // For ball logic
        std::string icon; // Player icon
        bool gravity; // false for normal gravity, true for anti gravity
    public:
        Player() : posX(10), completedLevels{false, false, false}, coinsCollected{"_ _ _", "_ _ _", "_ _ _"}, totalAttempts{0,0,0}, platformPos(0), alive(true), deltaY(1), height(DEFAULT_HEIGHT), isJumping(false), posY(0), icon("@"), gravity(false) { loadData(); }

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

        
        std::string* getAvailableIcons() {return icons;}
        u32 getIconCount() {return ICONCOUNT;}

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

        u32 getDeltaY() {return deltaY;}
        void setDeltaY(u32 dy) {deltaY = dy;}

        u32 getHeight() {return height;}
        void setHeight(u32 h) {height = h;}

        u32 getDefaultHeight() { return DEFAULT_HEIGHT; }

        bool isJumpingStatus() {return isJumping;}
        void setJumping(bool jumping) { isJumping = jumping; }

        bool aliveStatus() { return alive; }
        void setAlive(bool a) {alive = a; }

        bool getCompletedLevel( u32 idx ) { return completedLevels[idx]; }
        void setCompletedLevel( u32 idx ) { completedLevels[idx] = true; }

        std::string getCoins( u32 idx ) { return coinsCollected[idx]; }
        void setCoins( u32 idx, std::string coin ) { coinsCollected[idx] = coin; }

        u32 getTotalAttempts( u32 idx ) { return totalAttempts[idx]; }
        void setTotalAttempts( u32 idx, u32 attempts ) { totalAttempts[idx] += attempts; }

        u32 getNewPlatformPos() { return newPlatformPos; }
        void setNewPlatformPos(u32 pos) { newPlatformPos = pos; }

        /**
         * @brief Makes the player jump.
         * @return True if jump is incomplete, false if jump is complete
         * @param y The Y position to jump from (default, 0). Used for calculating jump height when jumping from platforms.
         */
        virtual bool jump(u32 y = 0);

        /**
         * @brief Causes the player to fall
         * @return true if player is still falling, false if they have finished falling
         */
        virtual bool fall();

        /**
         * @brief Saves the player's data to a file in the ../data directory"
         * @param levelNum The level number to save to (Each level number corresponds to a levelN.txt data file).
         * @return 0 if successful, -1 if unsuccessful
         */
        s16 saveData(u32 levelNum);
};

#endif // PLAYER_H