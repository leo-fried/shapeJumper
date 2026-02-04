#include "player.h"

bool Player::jump(u32 y)
{
    if(!isFalling) posY += deltaY;
    else posY -= deltaY;
    if (posY >= height + y) 
    {
        posY = height + y; // Clamp height
        isFalling = true;
    }
    if(posY <= platformPos) 
    { 
        posY = platformPos;
        isFalling = false; 
        return false; 
    } // Reset bool for next jump
    return true;
}