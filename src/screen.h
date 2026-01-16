#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>

#include "font.h"
#include "properties.h"

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
         */
        virtual void refresh();
};

#endif // SCREEN_H