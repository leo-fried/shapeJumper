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

        u32 newPlatformPos; // For hitting platforms from bottom
    public:
        Ball(): gravity(false), newPlatformPos(getPlatformPos()) { icon = "O";}
        ~Ball() {}

        /**
         * @brief Makes the Ball jump (Different than the standard player)
         * @return True if jump is incomplete, false if jump is complete
         */
        bool jump(u32 y) override;
};

#endif // Ball_H