#include "sfx.h"

void Sfx::playAudio(std::string filename, bool repeat)
{
    // Return if music is already playing (ENUM Status : 0 = Stopped, 1 = Paused, 2 = Playing) and music is meant to repeat(menus)
    if(music.getStatus() == 2 && repeat) return;

    if (!music.openFromFile("../assets/" + filename)) 
    {
        std::cerr << "Unable to load sfx: " << filename << "\n"; // sfx failed to load
        exit(-1);
    }

    music.setLoop(repeat);

    music.play();
}

void Sfx::stopAudio(std::string filename)
{
    if (!music.openFromFile("../assets/" + filename)) 
    {
        std::cerr << "Unable to load sfx: " << filename << "\n"; // sfx failed to load
        exit(-1);
    }

     music.stop();
}