#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <iostream>
#include <iterator>


#include "properties.h"

class Player
{
    private:
        std::string icons[8] = {"@", "!", "%", "&", "$", "M", "Q", "+"}; // available icons
        const u32 ICONCOUNT = 8;
        bool completedLevels[3]; // tracks levels that the player has completed

        /**
         * @brief Loads the player's completed levels from a file.
         * @param filename The file to load the data from (default, playerSave.txt).
         */
        void loadData(std::string filename = "playerSave.txt");

    protected:
        u32 posY;
        u32 platformPos;
        bool alive;
        std::string icon; // Player icon
        u32 deltaY; // Change in Y pos per jump
        // Jump data
        u32 height; // max jump height
        bool isJumping; // whether the player is currently jumping
        bool isFalling; // whether the player is falling or rising
    public:
        Player() : completedLevels{false, false, false}, posY(0), platformPos(0), alive(true), icon("@"), deltaY(1), height(4), isJumping(false), isFalling(false) { loadData(); }

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

        bool isFallingStatus() {return isFalling;}
        void setFalling(bool falling) {isFalling = falling;}

        bool isJumpingStatus() {return isJumping;}
        void setJumping(bool jumping) { isJumping = jumping; }

        bool aliveStatus() { return alive; }
        void setAlive(bool a) {alive = a; }

        bool getCompletedLevel( u32 idx ) { return completedLevels[idx]; }
        void setCompletedLevel( u32 idx ) { completedLevels[idx] = true; }

        /**
         * @brief Makes the player jump.
         * @return True if jump is incomplete, false if jump is complete
         */
        virtual bool jump(u32 y = 0);

        /**
         * @brief Causes the player to fall
         */
        virtual void fall() { return; }

        /**
         * @brief Saves the player's completed levels to a file.
         * @param filename The file to save the data to (default, playerSave.txt).
         * @return 0 if successful, -1 if unsuccessful
         */
        s16 saveData(std::string filename = "playerSave.txt");
};

#endif // PLAYER_H