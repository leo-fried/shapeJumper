#include "player.h"

bool Player::jump()
{
    
    if(!isFalling) posY += deltaY;
    else posY -= deltaY;
    if (posY >= height) 
    {
        posY = height; // Clamp height
        isFalling = true;
    }
    if(posY == 0) { isFalling = false; return false; }// Reset bool for next jump
    return true;
}