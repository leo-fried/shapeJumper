#ifndef BALL_H
#define BALL_H

#include <iostream>

#include "player.h"
#include "properties.h"

// Inherits from player
class Ball : public Player
{
    private:
        bool gravity; // False if ball is on floor, true if ball is on ceiling
    public:
        Ball(): gravity(false) { icon = "O";}
        ~Ball() {}

        /**
         * @brief Makes the Ball jump (Different than the standard player)
         * @return True if jump is incomplete, false if jump is complete
         */
        bool jump() override;
};

#endif // Ball_H