#ifndef SCREEN_H
#define SCREEN_H

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
         */
        virtual void simulateGame() = 0;
};

#endif // SCREEN_H