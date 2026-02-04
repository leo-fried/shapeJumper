#include "properties.h"

bool g_debug = false;

// For sound effects
std::vector<sf::SoundBuffer> soundBuffers;
std::vector<sf::Sound> activeSounds;

void playSfx(const std::string& path)
{
    // Load buffer if not already loaded
    soundBuffers.emplace_back();
    if (!soundBuffers.back().loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << "\n";
        soundBuffers.pop_back();
        return;
    }

    // Create sound using the buffer
    activeSounds.emplace_back();
    activeSounds.back().setBuffer(soundBuffers.back());
    activeSounds.back().play();

    // Remove finished sounds (buffers stay)
    activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(),
                       [](sf::Sound& s){ return s.getStatus() == sf::Sound::Stopped; }),
        activeSounds.end()
    );
}

void initTerminal()
{
    initscr();
    cbreak();              // Disable line buffering
    noecho();              // Don't echo typed characters
    keypad(stdscr, TRUE);  // Enable special keys
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(0);           // Hide cursor
}

void shutdownTerminal()
{
    endwin();              // Restore terminal
}
