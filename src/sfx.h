#ifndef SFX_H
#define SFX_H

#include <iostream>
#include <SFML/Audio.hpp> // For in-game audio
#include <string>

#include "properties.h"

// Sound effects using Simple and Fast Multimedia library
class Sfx
{
    private:
        sf::SoundBuffer buffer; // Buffer object
        sf::Sound sound; // Sound object
        
    public:
        /**
         * @brief Default Constructor
         * @param filename The filename for the audio
         */
        Sfx(const std::string& filename) { if (!buffer.loadFromFile("../assets/" + filename)) { std::cerr << "Unable to load SFX: " << filename << "\n"; } else sound.setBuffer(buffer); }
        ~Sfx() {}
        
        /**
         * @brief Plays a piece of audio.
         * @param volume the sound volume (Max by default)
         */
        void playAudio(float volume = 100.f) { sound.setVolume(volume); sound.play(); }

};


// Music tracks using Simple and Fast Multimedia library
class Music
{
    private:
        sf::Music music; // Music object
        std::string filename; // Filename for audio
        /**
         * @brief Loads the song into memory
         */
        void loadFromFile();
        
    public:
        /**
         * @brief Default Constructor
         * @param f The filename for the audio
         */
        Music(const std::string& f): filename(f) { loadFromFile();  }
        ~Music() {}
        
        /**
         * @brief Plays a piece of audio.
         * @param repeat Determines whether the given audio will repeat upon completion (false by default).
         * @param volume The volume to set the music to between 0 & 100 (100 by default)
         */
        void playAudio(bool repeat = false, float volume = 100.f);

        /**
         * @brief Stops the audio currently playing.
         */
        void stopAudio() { if (music.getStatus() != sf::Music::Stopped) music.stop(); }

        /**
         * @brief Restarts the music track
         */
        void restartAudio() { music.setPlayingOffset(sf::Time::Zero); }
};

#endif // SFX_H