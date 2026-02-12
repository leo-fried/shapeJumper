#include "ball.h"

bool Ball::jump([[maybe_unused]] u32 y)
{
    // Case 1: jump from normal gravity
    if(!gravity && posY < 13) // Clamp to max height
    {
        // Check if platform changed, if not increment Y-position and return true
        if(platformPos == newPlatformPos)
        {
            newPlatformPos = 0; // reset
            posY++;
            return true;
        }
        // Platform interaction, stop jump
        else newPlatformPos = platformPos;
    }

    // Case 2: Jump from anti gravity
    else if(gravity && posY > 0) // Clamp to min height
    {
        // Check if platform changed, if not de-increment Y-position and return true
        if(platformPos == newPlatformPos)
        {
            newPlatformPos = 13; // Reset platform
            posY--;
            return true;
        }
        // Platform interaction, stop jump
        else newPlatformPos = platformPos;
    }
    gravity = !gravity; // flip gravity
    return false; // Complete jump
}

bool Ball::fall()
{
    if(posY == platformPos) 
    {
            newPlatformPos = platformPos; // Reset
            return false;
    }
    // Fall down in normal gravity, fall up in anti gravity
    else if(posY < 14) gravity ? posY ++ : posY--;
    return true;
}