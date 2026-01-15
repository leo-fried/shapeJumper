#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>

typedef unsigned int uint;

// The basic screen class in which title screen, menus, etc will build upon
class Screen
{
    private:

    public:
        Screen(){std::cout << "test\n";}
        ~Screen(){}
};

#endif // SCREEN_H