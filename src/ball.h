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
        u32 newPlatformPos;
    public:
        /**
         * @brief Default Ball constructor.
         */
        Ball(): newPlatformPos(getPlatformPos()) { icon = "O"; }
        /**
         * @brief Default Ball destructor.
         */
        ~Ball() { gravity = false; }


        /**
         * @brief Gets the player's new platform position (For ball logic).
         * @return The player's new platform position.
         */
        u32 getNewPlatformPos() { return newPlatformPos; }
        /**
         * @brief Sets the player's new platform position (For ball logic).
         * @param pos The platform position to set.
         */
        void setNewPlatformPos(u32 pos) { newPlatformPos = pos; }

        /**
         * @brief Makes the Ball jump (Different than the standard player)
         * @return True if jump is incomplete, false if jump is complete
         */
        bool jump(u32 y) override;

        /**
         * @brief Causes the ball to fall
         * @return True if ball is still falling, false otherwise.
         */
        bool fall() override;    
};

#endif // Ball_H