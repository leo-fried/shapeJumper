#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <chrono>

#include "player.h"
#include "properties.h"

// Inherits from player
class Ship : public Player
{
    private:
        std::chrono::time_point<std::chrono::steady_clock> now; // Current time point
        std::chrono::time_point<std::chrono::steady_clock> delay; // Time point for controlling fall speed
    public:
        Ship() { icon = ">";}
        ~Ship() {}

        /**
         * @brief Makes the ship jump (Different than the standard player)
         * @return True if jump is incomplete, false if jump is complete
         */
        bool jump(u32 y) override;

        /**
         * @brief Causes the ship to fall
         * @return Returns true if ship is still falling, false otherwise.
         */
        bool fall() override;
};

#endif // SHIP_H