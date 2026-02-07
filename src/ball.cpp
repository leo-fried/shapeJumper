#include "ball.h"

bool Ball::jump([[maybe_unused]] u32 y)
{
    // Case 1: jump from normal gravity
    if(!gravity && posY < 13) // Clamp to max height
    {
        // Fall behavior
        if(isFallingStatus())
        {
            if(posY == getPlatformPos()) 
            {
                newPlatformPos = 0; // Reset
                setFalling(false);
                return false;
            }
            posY--;
            return true;
        }
        // Check if platform changed, if not increment Y-position and return true
        if(getPlatformPos() == newPlatformPos)
        {
            newPlatformPos = 0; // reset
            posY++;
            return true;
        }
        // Platform interaction, stop jump
        else 
        {
            newPlatformPos = getPlatformPos();
            setPlatformPos(0); // Reset Platform
        }
    }

    // Case 2: Jump from anti gravity
    else if(gravity && posY > 0) // Clamp to min height
    {
        
        // Fall behavior (anti grav)
        if(isFallingStatus())
        {
            if(posY == getPlatformPos() || posY == 13) 
            {
                newPlatformPos = getPlatformPos(); // Reset
                setFalling(false);
                return false;
            }
            posY++;
            return true;
        }
        // Check if platform changed, if not de-increment Y-position and return true
        if(getPlatformPos() == newPlatformPos)
        {
            newPlatformPos = 0; // Reset platform
            posY--;
            return true;
        }
        // Platform interaction, stop jump
        else
        {
            newPlatformPos = getPlatformPos();
            setPlatformPos(0); // Reset Platform
        }
    }
    gravity = !gravity; // flip gravity
    return false; // Complete jump
}