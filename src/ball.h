#ifndef BALL_H
#define BALL_H

#include <iostream>

#include "player.h"
#include "properties.h"
#include "sfx.h"

// Inherits from player
class Ball : public Player
{
    private:
        bool gravity; // False if ball is on floor, true if ball is on ceiling
    public:
        Ball(): gravity(false) { icon = "O"; newPlatformPos = getPlatformPos(); }
        ~Ball() { gravity = false; }

        /**
         * @brief Makes the Ball jump (Different than the standard player)
         * @return True if jump is incomplete, false if jump is complete
         */
        bool jump(u32 y) override;

        /**
         * @brief Causes the ball to fall
         * @return Returns true if ball is still falling, false otherwise.
         */
        bool fall() override;

        bool getGravity() { return gravity; }
        void setGravity(bool g) { gravity = g; }
    
};

#endif // Ball_H