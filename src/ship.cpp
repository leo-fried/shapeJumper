#include "ship.h"

bool Ship::jump([[maybe_unused]] u32 y)
{
    delay = std::chrono::steady_clock::now();
    // As long as jump is held fly up
    if(!gravity && posY < 13) posY++; // Regular grav
    else if(gravity && posY > 0) posY--; // Anti-grav
    return false;
}

bool Ship::fall()
{
    now = std::chrono::steady_clock::now();
    // Only let player fall if they are above platform and delay has passed
    if((!gravity && (posY > platformPos)) && (now - delay > std::chrono::milliseconds(250))) posY--; // Regular grav
    else if((gravity) && (posY < platformPos) && (now - delay > std::chrono::milliseconds(250))) posY++; // Anti-grav
    return false;
}