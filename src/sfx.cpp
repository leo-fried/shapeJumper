#include "sfx.h"

void Music::loadFromFile()
{
    if (!music.openFromFile("../assets/" + filename)) 
    {
        std::cerr << "Unable to load song: " << filename << "\n"; // music failed to load
    }
}

void Music::playAudio(bool repeat, float volume)
{
    music.setVolume(volume);
    music.setLoop(repeat);

    // play if music isn't already playing
    if (music.getStatus() != sf::Music::Playing) music.play();
}