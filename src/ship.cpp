#include "ship.h"

bool Ship::jump([[maybe_unused]] u32 y)
{
    delay = std::chrono::steady_clock::now();
    // As long as jump is held fly up, else fall
    if(posY < 13) posY++;
    return false;
}

bool Ship::fall()
{
    now = std::chrono::steady_clock::now();
    // Only let player fall if they are above platform and delay has passed
    if((posY > getPlatformPos()) && (now - delay > std::chrono::milliseconds(250))) posY--; 
    setPlatformPos(0); 
    return false;
}