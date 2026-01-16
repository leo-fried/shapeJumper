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
    public:
        Player() : posY(0), alive(true), icon('@') {}

        ~Player() {}

        /**
         * @brief Gets the player's icon.
         * @return The character representing the player's icon.
         */
        char getIcon(){return icon;}

        /**
         * @brief Sets the player's icon.
         * @param c The character to set as the player's icon.
         */
        void setIcon(char c){icon = c;} 

        void jump(u32 deltaY, u32 height)
        {
            while(posY < height) {
                std::cout<< "Y: " << posY <<"\n";
                posY += deltaY;
            }
            while(posY > 0) {
                std::cout<< "Y: " << posY <<"\n";
                posY -= deltaY;
            }
        }
};

#endif // PLAYER_H