#ifndef SFX_H
#define SFX_H

#include <iostream>
#include <SFML/Audio.hpp> // For in-game audio
#include <string>

#include "properties.h"

// Sound effects and audio using Simple and Fast Multimedia library
class Sfx
{
    private:
        sf::Music music; // Music object
    public:
        Sfx() {}
        ~Sfx() {}
        
        /**
         * @brief Plays a piece of audio.
         * @param filename The filename of the audio to play.
         * @param repeat Determines whether the given audio will repeat upon completion (false by default).
         */
        void playAudio(std::string filename, bool repeat = false);

        void stopAudio(std::string filename);
};

#endif // SFX_H