#ifndef SCREEN_H
#define SCREEN_H

#include <memory>

#include "player.h"
#include "properties.h"

// Basic screen interface class
class Screen
{
    protected:
        /**
         * @brief Loads data to the given screen
         */
        virtual void load() = 0;
    public:
        Screen() {}
        virtual ~Screen() {}

        /**
         * @brief Simulates the gameplay by refreshing the screen X times/second.
         * @return The player
         */
        virtual std::unique_ptr<Player> simulateGame() = 0;
};

#endif // SCREEN_H