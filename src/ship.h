#ifndef SHIP_H
#define SHIP_H

#include <iostream>

#include "player.h"
#include "properties.h"

// Inherits from player
class Ship : public Player
{
    public:
        Ship() { icon = ">";}
        ~Ship() {}

        /**
         * @brief Makes the ship jump (Different than the standard player)
         * @return True if jump is incomplete, false if jump is complete
         */
        bool jump() override;

        /**
         * @brief Causes the ship to fall
         */
        void fall() override { if(posY > 0) posY--; }
};

#endif // SHIP_H