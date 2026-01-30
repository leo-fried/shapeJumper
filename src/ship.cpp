#include "ship.h"

bool Ship::jump()
{
    // As long as jump is held fly up, else fall
    if(posY < 13) posY++;
    return false;
}