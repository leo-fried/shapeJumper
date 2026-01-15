#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <string>
#include <cstring> // For std::memcpy

#include "properties.cpp"

class Font
{
    public:
        Font(){}
        ~Font(){}
        /**
         * @brief Prints a character's pixel art to the console.
         * @param c The 2D array of characters representing the character's pixel art.
         */
        void printChar(char c);
        
};

#endif // FONT_H