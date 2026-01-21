#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "properties.h"

class Player
{
    private:
        u32 posY;
        bool alive;
        char icon; // player icon
        char icons[8] = {'@', '!', '%', '&', 'O', 'M', 'Q', '+'}; // available icons
        const u32 ICONCOUNT = 8;
        
        // Jump data
        u32 deltaY; // change in Y position per jump
        u32 height; // max jump height
        bool isFalling; // whether the player is falling or rising
    public:
        Player() : posY(0), alive(true), icon('@'), deltaY(1), height(3), isFalling(false) {}

        ~Player() {}

        /**
         * @brief Gets the player's icon.
         * @return The character representing the player's icon.
         */
        char getIcon() {return icon;}
 
        /**
         * @brief Sets the player's icon.
         * @param c The character to set as the player's icon.
         */
        void setIcon(char c) {icon = c;} 

        char* getAvailableIcons() {return icons;}
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

        /**
         * @brief Makes the player jump.
         */
        void jump();
};

#endif // PLAYER_H