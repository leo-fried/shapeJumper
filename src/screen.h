#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>

#include "properties.cpp"

typedef unsigned int uint;

// The basic screen class in which title screen, menus, etc will build upon
class Screen
{
    private:

    public:
        /**
         * @brief Default screen constructor that clears the screen.
         */
        Screen();
        ~Screen(){}
        /**
         * @brief Refreshes the screen content by clearing and redrawing it.
         * @param content The content to be displayed on the screen after refresh.
         */
        void refresh(std::string content = "");
};

#endif // SCREEN_H