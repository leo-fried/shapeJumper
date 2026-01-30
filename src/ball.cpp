#include "ball.h"

bool Ball::jump()
{
    // As long as jump is held fly up, else fall
    if(!gravity && posY < 13) 
    {
        posY++;
        return true;
    }
    else if(gravity && posY > 0)
    {
        posY--;
        return true;
    }
    gravity = !gravity; // flip gravity
    return false; // Complete jump
}