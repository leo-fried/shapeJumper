#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "properties.h"

class Player
{
    private:
        u32 posY;
        bool alive;
        std::string icon; // player icon
        std::string icons[8] = {"@", "!", "%", "&", "O", "M", "Q", "+"}; // available icons
        const u32 ICONCOUNT = 8;

        bool completedLevels[3]; // tracks levels that the player has completed
        
        // Jump data
        u32 deltaY; // change in Y position per jump
        u32 height; // max jump height
        bool isJumping; // whether the player is currently jumping
        bool isFalling; // whether the player is falling or rising
    public:
        Player() : posY(0), alive(true), icon("@"), completedLevels{false, false, false}, deltaY(1), height(5), isJumping(false), isFalling(false) {}

        ~Player() {}

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

        u32 getDeltaY() {return deltaY;}
        void setDeltaY(u32 dy) {deltaY = dy;}

        u32 getHeight() {return height;}
        void setHeight(u32 h) {height = h;}

        bool isFallingStatus() {return isFalling;}
        void setFalling(bool falling) {isFalling = falling;}

        bool isJumpingStatus() {return isJumping;}
        void setJumping(bool jumping) {isJumping = jumping;}

        bool aliveStatus() { return alive; }
        void setAlive(bool a) {alive = a; }

        bool getCompletedLevel( u32 idx ) { return completedLevels[idx]; }
        void setCompletedLevel( u32 idx ) { completedLevels[idx] = true; }

        /**
         * @brief Makes the player jump.
         */
        void jump();
};

#endif // PLAYER_H