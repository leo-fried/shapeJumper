#ifndef SCREEN_H
#define SCREEN_H

#include <string>

#include "properties.h"

// Basic screen interface class
class Screen
{
    protected:
        /**
         * @brief Loads data to the given screen
         * @param filename The data to load from a file.
         */
        virtual void load(std::string filename) = 0;
    public:
        Screen() {}
        virtual ~Screen() {}

        /**
         * @brief Simulates the gameplay by refreshing the screen X times/second.
         */
        virtual void simulateGame() = 0;
};

#endif // SCREEN_H