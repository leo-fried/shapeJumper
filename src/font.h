#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>


#include "properties.h"

class Font
{
    private:
        /**
         * @brief Prints a character's pixel art to the console.
         * @param c The character to be printed.
         * @param row The row position to start printing the character.
         */
        void printChar(char c, u16 row);
    public:
        /**
         * @brief Default Font Constructor.
         */
        Font(){}
        /**
         * @brief Default Font Destructor.
         */
        ~Font(){}
        /**
         * @brief Prints text to the console using pixel art for each character.
         * @param text The text to print.
         */
        void printText(const std::string& text);
        
};

#endif // FONT_H